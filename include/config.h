/**
 * @file config.h
 * @brief Constantes globales y tipos compartidos del programa.
 */

#ifndef CONFIG_H
#define CONFIG_H

/**
 * @name Constantes de configuracion
 * @brief Limites y rutas usadas por el programa.
 *
 * Estas constantes centralizan limites de validacion y rutas a archivos usados
 * por el flujo interactivo y por los benchmarks.
 * @{
 */
#define NAME_LENGTH_MIN 3             /**< Largo minimo para nombres generados. */
#define NAME_LENGTH_MAX 8             /**< Largo maximo para nombres generados. */
#define MAX_DATA 2147483647           /**< Maximo de registros permitidos (int32). */
#define MIN_DATA 10                   /**< Minimo de registros permitidos. */
#define MAX_SCORE 100.0               /**< Puntaje maximo permitido. */
#define MIN_SCORE 0.0                 /**< Puntaje minimo permitido. */
#define MAX_COMPETITIONS 45           /**< Maximo de competencias generadas. */
#define MIN_COMPETITIONS 1            /**< Minimo de competencias generadas. */
#define INTERVAL_SIZE 50              /**< Tamano de intervalo usado en benchmarks. */
#define EXPERIMENT_REPEATS 5          /**< Repeticiones por escenario en benchmarks. */
#define CSV_ROUTE "./db/deportistas.csv"            /**< CSV principal de deportistas. */
#define SEARCH_BENCHMARK_ROUTE "./db/search_benchmark.csv"  /**< Salida de benchmark de busqueda. */
#define SORT_BENCHMARK_ROUTE "./db/sort_benchmark.csv"      /**< Salida de benchmark de ordenamiento. */
#define SELECTION_BENCHMARK_ROUTE "./db/selection_benchmark.csv" /**< Salida de benchmark de seleccion. */
#define THRESHOLD_BENCHMARK_ROUTE "./db/threshold_benchmark.csv" /**< Salida de benchmark de umbral. */
/** @} */

/**
 * @brief Caso experimental usado en benchmarks.
 */
typedef enum {
    BENCHMARK_CASE_BEST = 0,
    BENCHMARK_CASE_AVERAGE = 1,
    BENCHMARK_CASE_WORST = 2
} BenchmarkCase;

#endif
