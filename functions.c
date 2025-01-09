#include "functions.h"

Proion katalogos[PROIONTA];

void initialize_katalogos() {
    for (int i = 0; i < PROIONTA; i++) {
        snprintf(katalogos[i].description, sizeof(katalogos[i].description), "Προϊόν %d", i + 1);
        katalogos[i].price = (float)((rand() % 1000) / 10.0); // anathetei tyxaia timh sto proion
        katalogos[i].item_count = 2; 
        katalogos[i].aitimata = 0;
        katalogos[i].poulithikan = 0;
        katalogos[i].disarestimenoi = 0;
    }
}

void paraggelia(int kodikos_proiontos, char client_name[50], int client_pipe[2]) {
    char apanthsh[100];
    katalogos[kodikos_proiontos].aitimata++;

    if (katalogos[kodikos_proiontos].item_count > 0) {
        katalogos[kodikos_proiontos].item_count--;
        katalogos[kodikos_proiontos].poulithikan++;
        snprintf(apanthsh, sizeof(apanthsh), "Επιτυχημένη Αγορά: %s (%.2f)", katalogos[kodikos_proiontos].description, katalogos[kodikos_proiontos].price);
    } else {
        strcpy(apanthsh, "Σφάλμα:Δεν υπάρχει το προιόν");
        strcpy(katalogos[kodikos_proiontos].disarestimenoi_pelates[katalogos[kodikos_proiontos].disarestimenoi++], client_name);
    }

    write(client_pipe[1], apanthsh, strlen(apanthsh) + 1);
    sleep(1); // perimenei 1 deuterolepto
}

void sinopsi() {
    int sunolikes_paraggelies = 0, epityximena_aitimata = 0, apotyximena_aitimata = 0;
    float tziros = 0;

    printf("\n***** Σύνοψη *****\n");
    for (int i = 0; i < PROIONTA; i++) {
        printf("%s:\n", katalogos[i].description);
        printf(">Αιτήματα: %d\n", katalogos[i].aitimata);
        printf(">Πωλήσεις: %d\n", katalogos[i].poulithikan);
        printf(">Έλλειψη: ");
        for (int j = 0; j < katalogos[i].disarestimenoi; j++) {
            printf("%s ", katalogos[i].disarestimenoi_pelates[j]);
        }
        printf("\n");

        sunolikes_paraggelies += katalogos[i].aitimata;
        epityximena_aitimata += katalogos[i].poulithikan;
        apotyximena_aitimata += katalogos[i].disarestimenoi;
        tziros += katalogos[i].poulithikan * katalogos[i].price;
    }

    printf("\n*Συνολικές Παραγγελίες: %d\n", sunolikes_paraggelies);
    printf("*Επιτυχημένες Παραγγελίες: %d\n", epityximena_aitimata);
    printf("*Αποτυχημένες Παραγγελίες: %d\n", apotyximena_aitimata);
    printf("*Τζίρος: %.2f\n", tziros);
}
