#include "selection.h"

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
int partition(Deportista *arr, int left, int right, SortCriteria criteria, SortOrder order) {
    Deportista pivot = arr[right];
    int i = left;

    for (int j = left; j < right; j++) {

        int cmp = compare_by_criteria(arr[j], pivot, criteria);
        int shouldSwap = (order == ASCENDING) ? (cmp <= 0) : (cmp >= 0);

        if (shouldSwap) {
            swap_deportistas(&arr[i], &arr[j]);
            i++;
        }
    }
    swap_deportistas(&arr[i], &arr[right]);
    return i;
}

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
Deportista quick_select_recursive(Deportista *arr, int left, int right, int k, SortCriteria criteria, SortOrder order) {
    if (left == right) {
        return arr[left];
    }

    int pivotIndex = partition(arr, left, right, criteria, order);

    if (k == pivotIndex) {
        return arr[k];
    } else if (k < pivotIndex) {
        return quick_select_recursive(arr, left, pivotIndex - 1, k, criteria, order);
    } else {
        return quick_select_recursive(arr, pivotIndex + 1, right, k, criteria, order);
    }
}

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
Deportista get_kth_element(Deportista *arr, int length, int k, SortCriteria criteria, SortOrder order) {
    if (arr == NULL || k < 0 || k >= length) {
        return NULL;
    }
    return quick_select_recursive(arr, 0, length - 1, k, criteria, order);
}