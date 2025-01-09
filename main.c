#include "functions.h"

int main() {
    int ptc[PELATES][2], ctp[PELATES][2];
    pid_t pids[PELATES];

    arxikopoiisi_katalogou();

    for (int i = 0; i < PELATES; i++) {
        pipe(ptc[i]); //ptc = parent to child
        pipe(ctp[i]); //ctp = child to parent

        if ((pids[i] = fork()) == 0) {
            close(ptc[i][1]);
            close(ctp[i][0]);

            for (int j = 0; j < PARAGGELIES_PELATON; j++) {
               
                int kodikos_proiontos = rand() % PROIONTA;
                write(ctp[i][1], &kodikos_proiontos, sizeof(int));

                char apanthsh[100];
                read(ptc[i][0], apanthsh, sizeof(apanthsh));
                printf("Πελάτης %d: %s\n", i + 1, apanthsh);

                sleep(1);
            }

            close(ptc[i][0]); 
            close(ctp[i][1]); 
            exit(0);
        } else {
            close(ptc[i][0]);
            close(ctp[i][1]);
        }
    }

    for (int i = 0; i < PELATES * PARAGGELIES_PELATON; i++) {
        int kodikos_proiontos;
        read(ctp[i % PELATES][0], &kodikos_proiontos, sizeof(int));
        paraggelia(kodikos_proiontos, "Όνομα Πελάτη", ptc[i % PELATES]);
    }

    for (int i = 0; i < PELATES; i++) {
        wait(NULL);
    }

    sinopsi(); //kalo ti sunartisi sinopsi

    return 0;
}
