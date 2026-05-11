#include "kth_athlete.h"

/**
 * @brief Corre y muestra el k-ésimo deportista según su puntaje
 * 
 * @param k kth a mostrar (1 para el mejor, 2 para el segundo mejor, etc.)
 */
void show_kth_athlete(int k){
    /* --- verificaciones --- */
    if(k <= 0){
        print_error(ERROR_INVALID_RANKING_AMOUNT, "El k-esimo deportista debe ser mayor que 0");
        return;
    }

    /* --- cargar csv ---*/
    int deportistas_count;
    Deportista* deportistas = load_deportistas_array(&deportistas_count);
    if(deportistas == NULL){
        print_error(ERROR_MEMORY_ALLOCATION_FAILED, "No se pudo cargar CSV");
        return;
    }
    else if(deportistas_count == 0){
        print_error(ERROR_NO_DATA_LOADED, NULL);
        free_deportistas_array(deportistas, deportistas_count);
        return;
    }

    /* --- ejecutar quick_select ---*/
    time_t init_time;
    time_t finish_time;

    init_time = clock();
    Deportista k_deportista = get_kth_athlete(deportistas, deportistas_count, k);
    finish_time = clock();

    if(k_deportista == NULL){
        print_error(ERROR_INVALID_RANKING_AMOUNT, "No existe un k-esimo deportista para el valor ingresado");
        free_deportistas_array(deportistas, deportistas_count);
        return;
    }

    /* --- mostrar deportista ---*/
    print_deportista(k_deportista);
    print_time(init_time, finish_time);
    free_deportistas_array(deportistas, deportistas_count);
}

/**
 * @brief Obtiene el k-ésimo deportista según su puntaje de un arreglo de deportistas.
 * 
 * @param deportistas Arreglo de deportistas.
 * @param count Cantidad de deportistas en el arreglo.
 * @param k Posición del deportista a obtener (1 para el mejor, 2 para el segundo mejor, etc.)
 * @return Deportista* Puntero al k-ésimo deportista o NULL si k es inválido o no se pudo obtener.
 */
Deportista get_kth_athlete(Deportista *deportistas, int count, int k){
    return get_kth_element(deportistas, count, k, SORT_BY_PUNTAJE, DESCENDING);
}