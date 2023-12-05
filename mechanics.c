#include "../libs/utils.h"
#include "../libs/mechanics.h"

// Funkce pro boj s drakem
int bojSDrakem(FILE* f1, Player* hrac) {
    // Generování síly hráče a draka
    int silaHrace = generujNahodneCislo(5, 15);
    int silaDraka = generujNahodneCislo(8, 18);

    // Zpráva o síle
    char buffer[50] = {0};
    sprintf(buffer, "Level hrace: %d\n", silaHrace);
    writeLog(f1, buffer);
    memset(buffer, 0, 50);

    sprintf(buffer, "Level draka: %d\n", silaDraka);
    writeLog(f1, buffer);
    memset(buffer, 0, 50);

    // Porovnání sil
    if (silaHrace > silaDraka) {
        writeLog(f1, "Bylo to o fous, ale porazil jsi ho\n");
        return 1; // Hráč vyhrál boj
    }
    else {
        writeLog(f1, "Umrel jsi, zkus to znovu\n");
        return 0; // Hráč prohrál boj
    }
}

// Funkce pro vytasení meče v boji s drakem
void pouzijSpecialniDovednost(FILE* f1, Player* hrac) {
    // Generuj náhodné rozhodnutí pro vytasení meče (33% šance)
    int nahodneRozhodnuti = generujNahodneCislo(1, 3);

    if (nahodneRozhodnuti == 1) {
        writeLog(f1, "Vytasil jsi mec\n");
        hrac->hasSword = 1;
    }
    else {
        writeLog(f1, "Kruci! Mec se zasekl. Zkus to znovu\n");
    }
}