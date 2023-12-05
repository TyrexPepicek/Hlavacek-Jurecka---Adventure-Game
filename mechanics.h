#include "utils.h"

// Struktura pro hráče
typedef struct Player {
    int hasExitKey;
    int hasSword;
    int hasChestKey;
    int hasChestTreasure;
    int hasEgg;
} Player;


// Funkce pro boj s drakem
int bojSDrakem(FILE* f1, Player* hrac);

// Funkce pro vytasení meče v boji s drakem
void pouzijSpecialniDovednost(FILE* f1, Player* hrac);