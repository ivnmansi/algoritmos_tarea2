/**
 * @file sorting.c
 * @brief Utilidades compartidas por los algoritmos de ordenamiento.
 */

#include "sorting.h"

/**
 * @brief Compara dos deportistas segun un criterio de ordenamiento.
 *
 * @param left Deportista izquierdo.
 * @param right Deportista derecho.
 * @param criteria Criterio a utilizar para la comparacion.
 * @return int Resultado de la comparacion: -1 si left < right, 1 si left > right, 0 si son iguales.
 */
int compare_by_criteria(Deportista left, Deportista right, SortCriteria criteria)
{
    if(left == NULL || right == NULL) {
        return 0;
    }

    switch(criteria){
        case SORT_BY_PUNTAJE:
            if(left->puntaje < right->puntaje) {
                return -1;
            }

            if(left->puntaje > right->puntaje) {
                return 1;
            }

            return 0;

        case SORT_BY_ID:
            if(left->id < right->id) {
                return -1;
            }

            if(left->id > right->id) {
                return 1;
            }

            return 0;

        case SORT_BY_COMPETENCIAS:
            if(left->competencias < right->competencias) {
                return -1;
            }

            if(left->competencias > right->competencias) {
                return 1;
            }

            return 0;

        case SORT_BY_NOMBRE:
            return strcmp(left->nombre, right->nombre);

        case SORT_BY_EQUIPO:
            return strcmp(left->equipo, right->equipo);

        default:
            return 0;
    }
}

/**
 * @brief Obtiene el nombre de un criterio de ordenamiento.
 * 
 * @param criteria 
 * @return const char* 
 */
const char *get_sort_criteria_name(SortCriteria criteria)
{
    switch(criteria) {
        case SORT_BY_ID:
            return "ID";
        case SORT_BY_PUNTAJE:
            return "Puntaje";
        case SORT_BY_COMPETENCIAS:
            return "Competencias";
        case SORT_BY_NOMBRE:
            return "Nombre";
        case SORT_BY_EQUIPO:
            return "Equipo";
        default:
            return "(desconocido)";
    }
}

/**
 * @brief Obtiene el nombre de un algoritmo de ordenamiento.
 * 
 * @param algorithm 
 * @return const char* 
 */
const char *get_sort_algorithm_name(SortAlgorithm algorithm)
{
    switch(algorithm) {
        case INSERTION_SORT:
            return "Insertion";
        case BUBBLE_SORT:
            return "Bubble";
        case SELECTION_SORT:
            return "Selection";
        case COCKTAIL_SHAKER_SORT:
            return "Cocktail shaker";
        case MERGE_SORT:
            return "MergeSort";
        case OPTIMIZED_MERGE_SORT:
            return "MergeSort optimizado";
        case QUICK_SORT_FIRST:
            return "QuickSort (pivote primero)";
        case QUICK_SORT_LAST:
            return "QuickSort (pivote ultimo)";
        case QUICK_SORT_RANDOM:
            return "QuickSort (pivote aleatorio)";
        case QUICK_SORT_MEDIAN:
            return "QuickSort (pivote mediana)";
        default:
            return "(desconocido)";
    }
}

/**
 * @brief Obtiene el nombre de un sentido de ordenamiento.
 * 
 * @param order 
 * @return const char* 
 */
const char *get_sort_order_name(SortOrder order)
{
    return (order == ASCENDING) ? "Ascendente" : "Descendente";
}