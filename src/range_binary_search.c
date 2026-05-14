/**
 * @file range_binary_search.c
 * @author Iván Mansilla
 * @brief Implementación de la función de búsqueda binaria que devuelve el rango de índices donde se encuentra lo buscado.
 */
#include "searching.h"

/**
 * Función auxiliar recursiva que busca el primer elemento que coincide con el valor objetivo
 * (expansión izquierda de forma recursiva).
 */
static int find_leftmost_recursive(Deportista *deportistas, int low, int high, SearchCriteria criteria, int targetValue)
{
    if (low > high) {
        return -1;
    }

    int mid = low + (high - low) / 2;
    int midValue;

    if (criteria == SEARCH_BY_ID) {
        midValue = deportistas[mid]->id;
    } else if (criteria == SEARCH_BY_PUNTAJE) {
        midValue = (int)deportistas[mid]->puntaje;
    } else {
        midValue = deportistas[mid]->competencias;
    }

    if (midValue == targetValue) {
        // Encontramos un elemento coincidente, pero necesitamos buscar más a la izquierda
        int leftResult = find_leftmost_recursive(deportistas, low, mid - 1, criteria, targetValue);
        return leftResult == -1 ? mid : leftResult;
    } else if (midValue < targetValue) {
        return find_leftmost_recursive(deportistas, mid + 1, high, criteria, targetValue);
    } else {
        return find_leftmost_recursive(deportistas, low, mid - 1, criteria, targetValue);
    }
}

/**
 * Función auxiliar recursiva que busca el último elemento que coincide con el valor objetivo
 * (expansión derecha de forma recursiva).
 */
static int find_rightmost_recursive(Deportista *deportistas, int low, int high, SearchCriteria criteria, int targetValue)
{
    if (low > high) {
        return -1;
    }

    int mid = low + (high - low) / 2;
    int midValue;

    if (criteria == SEARCH_BY_ID) {
        midValue = deportistas[mid]->id;
    } else if (criteria == SEARCH_BY_PUNTAJE) {
        midValue = (int)deportistas[mid]->puntaje;
    } else {
        midValue = deportistas[mid]->competencias;
    }

    if (midValue == targetValue) {
        // Encontramos un elemento coincidente, pero necesitamos buscar más a la derecha
        int rightResult = find_rightmost_recursive(deportistas, mid + 1, high, criteria, targetValue);
        return rightResult == -1 ? mid : rightResult;
    } else if (midValue < targetValue) {
        return find_rightmost_recursive(deportistas, mid + 1, high, criteria, targetValue);
    } else {
        return find_rightmost_recursive(deportistas, low, mid - 1, criteria, targetValue);
    }
}

/**
 * Función auxiliar recursiva que localiza cualquier elemento con el valor objetivo
 * (fase inicial de divide y vencerás).
 */
static int find_any_recursive(Deportista *deportistas, int low, int high, SearchCriteria criteria, int targetValue)
{
    if (low > high) {
        return -1;
    }

    int mid = low + (high - low) / 2;
    int midValue;

    if (criteria == SEARCH_BY_ID) {
        midValue = deportistas[mid]->id;
    } else if (criteria == SEARCH_BY_PUNTAJE) {
        midValue = (int)deportistas[mid]->puntaje;
    } else {
        midValue = deportistas[mid]->competencias;
    }

    if (midValue == targetValue) {
        return mid;
    } else if (midValue < targetValue) {
        return find_any_recursive(deportistas, mid + 1, high, criteria, targetValue);
    } else {
        return find_any_recursive(deportistas, low, mid - 1, criteria, targetValue);
    }
}

/**
 * @brief Búsqueda binaria que devuelve el rango de índices donde se encuentra el puntaje buscado.
 * 
 * @param deportistas 
 * @param length 
 * @param criteria 
 * @param targetId 
 * @return Range 
 */
Range range_binary_search(Deportista *deportistas, int length, SearchCriteria criteria, int targetId)
{
    Range result = {-1, -1};

    if (deportistas == NULL || length <= 0) {
        return result;
    }

    if (criteria != SEARCH_BY_ID && criteria != SEARCH_BY_PUNTAJE && criteria != SEARCH_BY_COMPETENCIAS) {
        return result;
    }

    // Fase 1: Encontrar cualquier elemento con el valor objetivo (divide y vencerás)
    int anyIndex = find_any_recursive(deportistas, 0, length - 1, criteria, targetId);

    if (anyIndex == -1) {
        return result; // No encontrado
    }

    // Fase 2: Encontrar el límite izquierdo (primer elemento con ese valor)
    result.start = find_leftmost_recursive(deportistas, 0, length - 1, criteria, targetId);

    // Fase 3: Encontrar el límite derecho (último elemento con ese valor)
    result.end = find_rightmost_recursive(deportistas, 0, length - 1, criteria, targetId);

    return result;
}

int range_binary_search_first_at_least(Deportista *deportistas, int length, int targetScore)
{
    int left = 0;
    int right = length - 1;
    int result = -1;

    if(deportistas == NULL || length <= 0) {
        return -1;
    }

    while(left <= right) {
        int mid = left + (right - left) / 2;

        if(deportistas[mid] == NULL) {
            return -1;
        }

        if((int)deportistas[mid]->puntaje >= targetScore) {
            result = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    return result;
}

int range_binary_search_last_at_most(Deportista *deportistas, int length, int targetScore)
{
    int left = 0;
    int right = length - 1;
    int result = -1;

    if(deportistas == NULL || length <= 0) {
        return -1;
    }

    while(left <= right) {
        int mid = left + (right - left) / 2;

        if(deportistas[mid] == NULL) {
            return -1;
        }

        if((int)deportistas[mid]->puntaje <= targetScore) {
            result = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return result;
}