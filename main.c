#include "functions.h"

int main() {
    int ptc[PELATES][2], ctp[PELATES][2]; // Δύο πίνακες για pipes (γονέας -> παιδί, παιδί -> γονέας)
    pid_t pids[PELATES]; // Πίνακας για τα process IDs των παιδιών

    arxikopoiisi_katalogou(); // Κλήση της συνάρτησης που αρχικοποιεί τα προϊόντα

    for (int i = 0; i < PELATES; i++) {
        pipe(ptc[i]); // Δημιουργία pipe για επικοινωνία γονέα -> παιδί
        pipe(ctp[i]); // Δημιουργία pipe για επικοινωνία παιδιού -> γονέα

        if ((pids[i] = fork()) == 0) { // Δημιουργία νέου process για κάθε πελάτη (παιδί)
            close(ptc[i][1]); // Κλείνουμε την εγγραφή στο pipe γονέα -> παιδί στο παιδί
            close(ctp[i][0]); // Κλείνουμε την ανάγνωση στο pipe παιδιού -> γονέα στο παιδί

            for (int j = 0; j < PARAGGELIES_PELATON; j++) { // Κάθε πελάτης εκτελεί τις παραγγελίες του
               
                int kodikos_proiontos = rand() % PROIONTA; // Επιλέγει τυχαία έναν κωδικό προϊόντος
                write(ctp[i][1], &kodikos_proiontos, sizeof(int)); // Στέλνει τον κωδικό στον γονέα

                char apanthsh[100];
                read(ptc[i][0], apanthsh, sizeof(apanthsh)); // Διαβάζει την απάντηση του γονέα
                printf("Πελάτης %d: %s\n", i + 1, apanthsh); // Εκτυπώνει την απάντηση

                sleep(1); // Αναμονή 1 δευτερολέπτου πριν την επόμενη παραγγελία
            }

            close(ptc[i][0]); 
            close(ctp[i][1]); 
            exit(0); // Το παιδί τερματίζει
        } else {
            close(ptc[i][0]);
            close(ctp[i][1]);
        }
    }

    for (int i = 0; i < PELATES * PARAGGELIES_PELATON; i++) { // Όλες οι παραγγελίες από όλους τους πελάτες
        int kodikos_proiontos;
        read(ctp[i % PELATES][0], &kodikos_proiontos, sizeof(int)); // Διαβάζει τον κωδικό από το pipe του πελάτη
        paraggelia(kodikos_proiontos, "Όνομα Πελάτη", ptc[i % PELATES]); // Επεξεργάζεται την παραγγελία
    }

    for (int i = 0; i < PELATES; i++) {
        wait(NULL); // Ο γονέας περιμένει να τερματίσει κάθε παιδί
    }

    sinopsi(); // Καλείται η συνάρτηση `sinopsi()` για συνολικά αποτελέσματα

    return 0; // Το πρόγραμμα τερματίζει κανονικά
}
