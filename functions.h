#ifndef FUNCTIONS_H //Ελέγχει αν η μακροεντολή FUNCTIONS_H δεν έχει ήδη οριστεί, προκείμενου να μην συμπεριληφθεί πολλαπλές φορές και μπερδέψει τον compiler.
#define FUNCTIONS_H //Ορίζει τη μακροεντολή FUNCTIONS_H, ώστε να θυμάται ότι το αρχείο αυτό έχει ήδη συμπεριληφθεί.

#include <unistd.h>   // Για pipe, fork, write, read, close
#include <string.h>   // Για λειτουργίες σε strings
#include <time.h>     // Για τη χρήση τυχαίων αριθμών (rand)
#include <stdio.h>    // Για είσοδο/έξοδο
#include <stdlib.h>   // Για malloc, free, exit

#define PELATES 5
#define PARAGGELIES_PELATON 10
#define PROIONTA 20

typedef struct Proion { // Δομή για ένα προϊόν
    char description[50];
    float price;
    int item_count;
    int aitimata;
    int disarestimenoi;
    char disarestimenoi_pelates[100][50];
    int poulithikan;
    char onoma_pelati[50];
} Proion;

extern Proion katalogos[PROIONTA]; // Εξωτερική δήλωση για χρήση του πίνακα σε πολλά αρχεία

void arxikopoiisi_katalogou();
void paraggelia(int kodikos_proiontos, char onoma_pelati[50], int client_pipe[2]);
void sinopsi();

#endif 
