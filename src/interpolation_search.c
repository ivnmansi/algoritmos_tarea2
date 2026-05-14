#include"searching.h"

/**
 * Función auxiliar recursiva que implementa divide y vencerás.
 * Divide el rango usando interpolación lineal en lugar de binaria.
 */
static int interpolation_search_recursive(Deportista *deportistas, int low, int high, SearchCriteria criteria, int targetValue)
{
    // Caso base: rango agotado sin encontrar el elemento
    if (low > high) {
        return -1;
    }

    int lowValue, highValue;

    // División: obtener valores en los extremos según el criterio
    if (criteria == SEARCH_BY_ID) {
        lowValue = deportistas[low]->id;
        highValue = deportistas[high]->id;
    } else if (criteria == SEARCH_BY_PUNTAJE) {
        lowValue = (int)deportistas[low]->puntaje;
        highValue = (int)deportistas[high]->puntaje;
    } else if (criteria == SEARCH_BY_COMPETENCIAS) {
        lowValue = deportistas[low]->competencias;
        highValue = deportistas[high]->competencias;
    } else {
        return -1;
    }

    // Si los valores extremos son iguales, hay un solo valor en el rango
    if (lowValue == highValue) {
        if (lowValue == targetValue) {
            return low;
        }
        return -1;
    }

    // Si el objetivo está fuera del rango ordenado, no puede existir
    if (targetValue < lowValue || targetValue > highValue) {
        return -1;
    }

    // Estimar la posición usando interpolación lineal (división inteligente)
    int pos = low + (((double)(high - low) / (highValue - lowValue)) * (targetValue - lowValue));

    // Validar que la posición esté dentro de los límites válidos
    if (pos < low || pos > high) {
        return -1;
    }

    int midValue;
    if (criteria == SEARCH_BY_ID) {
        midValue = deportistas[pos]->id;
    } else if (criteria == SEARCH_BY_PUNTAJE) {
        midValue = (int)deportistas[pos]->puntaje;
    } else {
        midValue = deportistas[pos]->competencias;
    }

    // Conquista: tres casos de recursión
    if (midValue == targetValue) {
        return pos;
    }

    if (midValue < targetValue) {
        // El objetivo está en la mitad derecha
        return interpolation_search_recursive(deportistas, pos + 1, high, criteria, targetValue);
    } else {
        // El objetivo está en la mitad izquierda
        return interpolation_search_recursive(deportistas, low, pos - 1, criteria, targetValue);
    }
}

int interpolation_search(Deportista *deportistas, int length, SearchCriteria criteria, int targetValue)
{
    if (deportistas == NULL || length <= 0) {
        return -1;
    }

    return interpolation_search_recursive(deportistas, 0, length - 1, criteria, targetValue);
}