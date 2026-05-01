/**
 * @file generator.c
 * @brief Implementacion de generadores aleatorios para deportistas.
 */

#include "generator.h"
#include "config.h"

#include <string.h>

/**
 * @brief Equipos disponibles para la generacion aleatoria.
 */
static const char *teamNames[] = {
    "T1",
    "Damwon Gaming",
    "Gen.G",
    "Hanwha Life Esports",
    "Fnatic",
    "G2 Esports",
    "MAD Lions",
    "Rogue",
    "Cloud9",
    "Immortals",
    "FlyQuest",
    "100 Thieves",
    "Sentinels"
};

/**
 * @brief Genera un nombre aleatorio usando solo letras ASCII.
 *
 * @return char* Cadena dinamica con el nombre generado.
 */
char *generate_random_name(void)
{
    const char letters[] = "abcdefghijklmnopqrstuvwxyz";
    int n = (int)strlen(letters);
    int nameLength = (rand() % (NAME_LENGTH_MAX - NAME_LENGTH_MIN + 1)) + NAME_LENGTH_MIN;
    char *name = malloc((size_t)nameLength + 1);

    if(name == NULL) {
        return NULL;
    }

    for(int i = 0; i < nameLength; i++) {
        name[i] = letters[rand() % n];
    }

    name[nameLength] = '\0';
    return name;
}

/**
 * @brief Genera un equipo aleatorio.
 *
 * @return char* Cadena dinamica con el nombre del equipo.
 */
char *generate_random_team(void)
{
    int n = (int)(sizeof(teamNames) / sizeof(teamNames[0]));
    const char *selected = teamNames[rand() % n];
    char *team = malloc(strlen(selected) + 1);

    if(team == NULL) {
        return NULL;
    }

    strcpy(team, selected);
    return team;
}

/**
 * @brief Genera un puntaje aleatorio dentro del rango permitido.
 *
 * @return int Puntaje aleatorio.
 */
int generate_random_score(void)
{
    int maxScore = (int)MAX_SCORE;
    int minScore = (int)MIN_SCORE;

    return (rand() % (maxScore - minScore + 1)) + minScore;
}

/**
 * @brief Genera una cantidad aleatoria de competencias.
 *
 * @return int Cantidad de competencias.
 */
int generate_random_competitions(void)
{
    return (rand() % (MAX_COMPETITIONS - MIN_COMPETITIONS + 1)) + MIN_COMPETITIONS;
}
