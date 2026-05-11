/**
* @file selection.h
* @brief Prototipos de funciones para el algoritmo de ordenamiento por selección.
*/

#ifndef SELECTION_H
#define SELECTION_H

#include "deportista.h"
#include "sorting.h"

typedef enum {
    QUICK_SELECT = 1 /**< Quick select para encontrar el k-ésimo elemento más pequeño. */
} SelectionAlgorithm;

/**
 * @brief Particiona el arreglo de deportistas según un criterio y orden dados.
 * 
 * @param arr Arreglo de deportistas a particionar.
 * @param left Índice izquierdo del subarreglo a particionar.
 * @param right Índice derecho del subarreglo a particionar.
 * @param criteria Criterio de comparación para ordenar los deportistas.
 * @param order Orden de comparación (ASCENDING para menor a mayor, DESCENDING para mayor a menor).
 * @return int Índice del pivote después de la partición.
 */
int partition(Deportista *arr, int left, int right, SortCriteria criteria, SortOrder order);

/**
 * @brief Ejecuta el algoritmo de quick select de forma recursiva para encontrar el k-ésimo elemento según un criterio y orden dados.
 * 
 * @param arr Arreglo de deportistas.
 * @param left Índice izquierdo del subarreglo actual.
 * @param right Índice derecho del subarreglo actual.
 * @param k Posición del elemento a obtener (0 para el más pequeño, 1 para el segundo más pequeño, etc.)
 * @param criteria Criterio de comparación para ordenar los deportistas.
 * @param order Orden de comparación (ASCENDING para menor a mayor, DESCENDING para mayor a menor).
 * @return Deportista 
 */
Deportista quick_select_recursive(Deportista *arr, int left, int right, int k, SortCriteria criteria, SortOrder order);

/**
 * @brief Obtiene el k-ésimo elemento de un arreglo de deportistas según un criterio y orden dados utilizando el algoritmo de quick select.
 * 
 * @param arr Arreglo de deportistas.
 * @param length Longitud del arreglo.
 * @param k Posición del elemento a obtener (0 para el más pequeño, 1 para el segundo más pequeño, etc.)
 * @param criteria Criterio de comparación para ordenar los deportistas.
 * @param order Orden de comparación (ASCENDING para menor a mayor, DESCENDING para mayor a menor).
 * @return Deportista 
 */
Deportista get_kth_element(Deportista *arr, int length, int k, SortCriteria criteria, SortOrder order);


#endif