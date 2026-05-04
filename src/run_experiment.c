/**
 * @file run_experiment.c
 * @brief Flujos interactivos de ordenamiento, busqueda y ranking.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "base.h"
#include "csv.h"
#include "errors.h"
#include "print_format.h"
#include "searching.h"
#include "sorting.h"

/**
 * @brief Carga el CSV actual en un arreglo.
 *
 * @param deportistas Direccion donde se entrega el arreglo creado.
 * @param count Direccion donde se entrega la cantidad de elementos.
 * @return int 1 si la carga fue exitosa, 0 en caso contrario.
 */
static int load_data(Deportista **deportistas, int *count)
{
    if(deportistas == NULL) {
        return 0;
    }
    if(count == NULL) {
        return 0;
    }

    *deportistas = load_deportistas_array(count);
    if(*deportistas == NULL) {
        print_error(ERROR_NO_DATA_LOADED, NULL);
        return 0;
    }

    if(*count == 0) {
        free_deportistas_array(*deportistas, *count);
        print_error(ERROR_NO_DATA_LOADED, NULL);
        return 0;
    }

    return 1;
}

/**
 * @brief Pregunta que ordenamiento usar.
 *
 * @return SortAlgorithm Opcion seleccionada.
 */
static SortAlgorithm ask_sort_algorithm(void)
{
    char option[16];
    int selected;

    do {
        system("clear");

        printf(BOLD BLUE "=== Algoritmo de ordenamiento ===\n" NORMAL);
        printf("\t1) Insertion sort\n");
        printf("\t2) Bubble sort\n");
        printf("\t3) Selection sort\n");
        printf("\t4) Cocktail shaker sort\n\n");
        printf(BOLD "Opcion: " NORMAL);

        if(fgets(option, sizeof(option), stdin) == NULL) {
            return 0;
        }

        selected = atoi(option);
    }
    while(selected < INSERTION_SORT || selected > COCKTAIL_SHAKER_SORT);

    return (SortAlgorithm)selected;
}

/**
 * @brief Pregunta que busqueda usar.
 *
 * @return SearchAlgorithm Opcion seleccionada.
 */
static SearchAlgorithm ask_search_algorithm(void)
{
    char option[16];
    int selected;

    do {
        system("clear");

        printf(BOLD BLUE "=== Algoritmo de busqueda ===\n" RESET);
        printf(DIM GRAY "(Algunas busquedas requieren arreglo ordenado)\n\n" RESET);

        printf("  1) Busqueda secuencial            " DIM GRAY "[ID]" RESET "\n");
        printf("  2) Busqueda binaria               " DIM GRAY "[ID]" RESET "\n");
        printf(DIM GRAY "  3) Busqueda binaria recursiva     [pendiente]\n" RESET);
        printf("  4) Busqueda binaria por rango     " DIM GRAY "[PUNTAJE]" RESET "\n");
        printf("  5) Busqueda exponencial           " DIM GRAY "[ID]" RESET "\n");
        printf(DIM GRAY "  6) Busqueda por interpolacion     [pendiente]\n\n" RESET);

        printf(BOLD "Opcion: " RESET);

        if(fgets(option, sizeof(option), stdin) == NULL) {
            return 0;
        }

        selected = atoi(option);
    }
    while(selected < SEQUENTIAL_SEARCH || selected > INTERPOLATION_SEARCH);

    return selected;
}

/**
 * @brief Ejecuta una operacion de ordenamiento o ranking.
 *
 * @param criteria Campo por el cual se ordena.
 * @param rankingAmount Cantidad de elementos a mostrar.
 * @param order Sentido de ordenamiento.
 */
static void run_sort_operation(SortCriteria criteria, int rankingAmount, SortOrder order)
{
    Deportista *deportistas = NULL;
    SortAlgorithm algorithmOption = ask_sort_algorithm();
    int count = 0;

    if(rankingAmount < 0) {
        rankingAmount = 0;
    }

    switch(algorithmOption) {
        case INSERTION_SORT:
            if(load_data(&deportistas, &count) == 0) {
                return;
            }

            insertion_sort_deportistas(deportistas, count, criteria, order);

            if(rankingAmount > count) {
                rankingAmount = count;
            }

            print_sort_result_header(
                get_sort_algorithm_name(algorithmOption),
                get_sort_criteria_name(criteria),
                get_sort_order_name(order),
                rankingAmount,
                count
            );
            print_deportistas_array(deportistas, rankingAmount);
            print_sort_result_footer();
            free_deportistas_array(deportistas, count);
            break;
        case BUBBLE_SORT:
            if(load_data(&deportistas, &count) == 0) {
                return;
            }

            optimized_bubble_sort(deportistas, count, criteria, order);

            if(rankingAmount > count) {
                rankingAmount = count;
            }

            print_sort_result_header(
                get_sort_algorithm_name(algorithmOption),
                get_sort_criteria_name(criteria),
                get_sort_order_name(order),
                rankingAmount,
                count
            );
            print_deportistas_array(deportistas, rankingAmount);
            print_sort_result_footer();
            free_deportistas_array(deportistas, count);
            break;
        case SELECTION_SORT:
            if(load_data(&deportistas, &count) == 0) {
                return;
            }

            optimized_selection_sort(deportistas, count, criteria, order);

            if(rankingAmount > count) {
                rankingAmount = count;
            }

            print_sort_result_header(
                get_sort_algorithm_name(algorithmOption),
                get_sort_criteria_name(criteria),
                get_sort_order_name(order),
                rankingAmount,
                count
            );
            print_deportistas_array(deportistas, rankingAmount);
            print_sort_result_footer();
            free_deportistas_array(deportistas, count);
            break;
        case COCKTAIL_SHAKER_SORT:
            if(load_data(&deportistas, &count) == 0) {
                return;
            }

            cocktail_shaker_sort(deportistas, count, criteria, order);

            if(rankingAmount > count) {
                rankingAmount = count;
            }

            print_sort_result_header(
                get_sort_algorithm_name(algorithmOption),
                get_sort_criteria_name(criteria),
                get_sort_order_name(order),
                rankingAmount,
                count
            );
            print_deportistas_array(deportistas, rankingAmount);
            print_sort_result_footer();
            free_deportistas_array(deportistas, count);
            break;
        default:
            print_error(ERROR_NOT_IMPLEMENTED, NULL);
            break;
    }
}

/**
 * @brief Busca un deportista e imprime el resultado.
 *
 * @param targetId ID buscado.
 */
void search(int targetId)
{
    Deportista *deportistas = NULL;
    SearchAlgorithm algorithmOption;
    int count = 0;
    int index;
    char detail[32];

    algorithmOption = ask_search_algorithm();

    if(load_data(&deportistas, &count) == 0) {
        return;
    }

    switch(algorithmOption) {
        case SEQUENTIAL_SEARCH:

            index = sequential_search(deportistas, count, SEARCH_BY_ID, targetId);

            if(index < 0) {
                snprintf(detail, sizeof(detail), "ID %d", targetId);
                free_deportistas_array(deportistas, count);
                print_error(ERROR_DEPORTISTA_NOT_FOUND, detail);
                return;
            }

            print_search_result_header("Secuencial", "ID", targetId, 1);
            print_deportista(deportistas[index]);
            print_search_result_footer();
            free_deportistas_array(deportistas, count);
            break;

        case BINARY_SEARCH:
            insertion_sort_deportistas(deportistas, count, SORT_BY_ID, ASCENDING);
            index = binary_search(deportistas, count, SEARCH_BY_ID, targetId);

            if(index < 0) {
                snprintf(detail, sizeof(detail), "ID %d", targetId);
                free_deportistas_array(deportistas, count);
                print_error(ERROR_DEPORTISTA_NOT_FOUND, detail);
                return;
            }

            print_search_result_header("Binaria", "ID", targetId, 1);
            print_deportista(deportistas[index]);
            print_search_result_footer();
            free_deportistas_array(deportistas, count);
            break;
        case RECURSIVE_BINARY_SEARCH:
            print_error(ERROR_NOT_IMPLEMENTED, NULL);
            free_deportistas_array(deportistas, count);
            break;
        case RANGE_BINARY_SEARCH:
            insertion_sort_deportistas(deportistas, count, SORT_BY_PUNTAJE, ASCENDING);
            Range range = range_binary_search(deportistas, count, SEARCH_BY_PUNTAJE, targetId);

            if(range.start < 0 || range.end < 0) {
                snprintf(detail, sizeof(detail), "Puntaje %d", targetId);
                free_deportistas_array(deportistas, count);
                print_error(ERROR_DEPORTISTA_NOT_FOUND, detail);
                return;
            }

            print_search_result_header(
                "Binaria por rango",
                "PUNTAJE",
                targetId,
                (range.end - range.start + 1)
            );
            for(int i = range.start; i <= range.end; i++) {
                print_deportista(deportistas[i]);
            }
            print_search_result_footer();
            free_deportistas_array(deportistas, count);
            break;

        case EXPONENCIAL_SEARCH:
            insertion_sort_deportistas(deportistas, count, SORT_BY_ID, ASCENDING);
            index = exponencial_search(deportistas, count, SEARCH_BY_ID, targetId);
            if(index < 0) {
                snprintf(detail, sizeof(detail), "ID %d", targetId);
                free_deportistas_array(deportistas, count);
                print_error(ERROR_DEPORTISTA_NOT_FOUND, detail);
                return;
            }
            print_search_result_header("Exponencial", "ID", targetId, 1);
            print_deportista(deportistas[index]);
            print_search_result_footer();
            free_deportistas_array(deportistas, count);
            break;
        case INTERPOLATION_SEARCH:
            print_error(ERROR_NOT_IMPLEMENTED, NULL);
            free_deportistas_array(deportistas, count);
            break;
        default:
            print_error(ERROR_NOT_IMPLEMENTED, NULL);
            break;
    }
}

/**
 * @brief Muestra el ranking de los mejores N deportistas segun puntaje.
 *
 * @param rankingAmount Cantidad de deportistas a mostrar.
 */
void show_ranking(int rankingAmount)
{
    run_sort_operation(SORT_BY_PUNTAJE, rankingAmount, DESCENDING);
}

/**
 * @brief Pregunta por el campo de ordenamiento.
 *
 * @return SortCriteria Opcion seleccionada.
 */
static SortCriteria ask_sort_criteria(void)
{
    char option[16];
    SortCriteria criteria;

    do {
        system("clear");

        printf(BOLD BLUE "=== Campo de ordenamiento ===\n" NORMAL);
        printf("  1) ID\n");
        printf("  2) Puntaje\n");
        printf("  3) Competencias\n");
        printf("  4) Nombre\n");
        printf("  5) Equipo\n\n");
        printf(BOLD "Opcion: " NORMAL);

        if(fgets(option, sizeof(option), stdin) == NULL) {
            return 0;
        }

        criteria = (SortCriteria)atoi(option);
    }
    while(criteria < SORT_BY_ID || criteria > SORT_BY_EQUIPO);

    return criteria;
}

/**
 * @brief Pregunta por el sentido del ordenamiento.
 *
 * @return SortOrder Opcion seleccionada.
 */
static SortOrder ask_sort_order(void)
{
    char option[16];
    int selected;

    do {
        system("clear");

        printf(BOLD BLUE "=== Orden ===\n" NORMAL);
        printf("  1) Descendente\n");
        printf("  2) Ascendente\n\n");
        printf(BOLD "Opcion: " NORMAL);

        if(fgets(option, sizeof(option), stdin) == NULL) {
            return 0;
        }

        selected = atoi(option);
    }
    while(selected < 1 || selected > 2);

    return (selected == 1) ? DESCENDING : ASCENDING;
}

/**
 * @brief Ejecuta el flujo interactivo de ordenamiento.
 */
void run_experiment(void)
{
    SortCriteria criteria = ask_sort_criteria();
    SortOrder order = ask_sort_order();

    run_sort_operation(criteria, MAX_DATA, order);
}
