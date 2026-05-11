/**
 * @file exponencial_search.c
 * @author Iván Mansilla
 * @brief Implementación de la función de búsqueda exponencial.
 */
#include "searching.h"

/**
 * @brief Busca un deportista por ID usando busqueda exponencial.
 *
 * @param deportistas Arreglo de deportistas ordenado por ID ascendente.
 * @param length Cantidad de elementos del arreglo.
 * @param criteria Criterio de busqueda (ID).
 * @param targetId ID que se desea encontrar.
 * @return int Indice del elemento encontrado o -1 si no existe.
 */
int exponencial_search(Deportista *deportistas, int length, SearchCriteria criteria, int targetId){
    (void)criteria;  // Parámetro no utilizado

    if(deportistas == NULL || length < 1) {
        return -1;
    }
    if(deportistas[0]->id == targetId) {
        return 0;
    }

    int bound = 1;
    while(bound < length) {
        if(deportistas[bound] == NULL) {
            return -1;
        }

        if(deportistas[bound]->id >= targetId) {
            break;
        }

        bound *= 2;
    }

    int left = bound / 2;
    int right = bound < length ? bound : (length - 1);

    while(left <= right) {
        int mid = left + (right - left) / 2;

        if(deportistas[mid] == NULL) {
            return -1;
        }

        if(deportistas[mid]->id == targetId) {
            return mid;
        }

        if(deportistas[mid]->id < targetId) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1;
}