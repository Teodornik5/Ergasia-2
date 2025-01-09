#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define PELATES 5
#define PARAGGELIES_PELATON 10
#define PROIONTA 20

typedef struct Proion {
    char description[50];
    float price;
    int item_count;
    int aitimata;
    int disarestimenoi;
    char disarestimenoi_pelates[100][50];
    int poulithikan;
} Proion;

extern Proion katalogos[PROIONTA];

void initialize_katalogos();
void paraggelia(int kodikos_proiontos, char client_name[50], int client_pipe[2]);
void sinopsi();

#endif // FUNCTIONS_H
