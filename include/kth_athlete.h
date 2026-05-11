#ifndef KTH_ATHLETE_H
#define KTH_ATHLETE_H

#include <time.h>
#include "deportista.h"
#include "selection.h"
#include "sorting.h"
#include "csv.h"
#include "errors.h"
#include "print_format.h"


/**
 * @brief Corre y muestra el k-ésimo deportista según su puntaje
 * 
 * @param k kth a mostrar (1 para el mejor, 2 para el segundo mejor, etc.)
 */
void show_kth_athlete(int k);

/**
 * @brief Obtiene el k-ésimo deportista según su puntaje de un arreglo de deportistas.
 * 
 * @param deportistas Arreglo de deportistas.
 * @param count Cantidad de deportistas en el arreglo.
 * @param k Posición del deportista a obtener (1 para el mejor, 2 para el segundo mejor, etc.)
 * @return Deportista* Puntero al k-ésimo deportista o NULL si k es inválido o no se pudo obtener.
 */
Deportista get_kth_athlete(Deportista *deportistas, int count, int k);







#endif