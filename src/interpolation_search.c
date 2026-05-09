#include"searching.h"

int interpolation_search(Deportista *deportistas, int length, SearchCriteria criteria, int targetValue)
{
    if (deportistas == NULL || length <= 0) {
        return -1;
    }

    int low = 0;
    int high = length - 1;

    while (low <= high) {
        int lowValue, highValue;

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

        // Evitar division por cero y mantenernos dentro de los limites
        if (lowValue == highValue) {
            if (lowValue == targetValue) {
                return low;
            }
            return -1;
        }

        if (targetValue < lowValue || targetValue > highValue) {
            return -1;
        }

        //formula de interpolacion lineal
        int pos = low + (((double)(high - low) / (highValue - lowValue)) * (targetValue - lowValue));

        //asegurarse de que pos esta dentro de los limites
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

        if (midValue == targetValue) {
            return pos;
        }

        if (midValue < targetValue) {
            low = pos + 1;
        } else {
            high = pos - 1;
        }
    }

    return -1;
}