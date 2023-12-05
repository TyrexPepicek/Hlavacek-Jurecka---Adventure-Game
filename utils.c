#include "../libs/utils.h"

int generujNahodneCislo(int min, int max) {
    return rand() % (max - min + 1) + min;
}

void writeLog(FILE* f1, char* zprava){
    if (f1 == NULL){
        return ;
    }
    fprintf(f1, zprava);
    fflush(f1);
    printf(zprava);
}