#include "libs/utils.h"
#include "libs/mechanics.h"

/*
stavy:
0 = zacatek
1 = modre dvere - hadanka


2 = cervene dvere - drak
    21 = win drak
    22 = utek

3 = zelene dvere - truhla

9 = vyhra
10 = konec hry
11 = neplatny stav

*/



int main() {
    srand(time(NULL));

    // Vytvoření hráče
    Player hrac;
    hrac.hasExitKey = 0;
    hrac.hasChestKey = 0;
    hrac.hasSword = 0;

    FILE* f1 = NULL;

    if ((f1 = fopen("game_log.txt", "w")) == 0){
        writeLog(f1, "Selhato otevreni logovaciho souboru!\n");
        return 1;
    }

    // Vytvoření proměnné pro uchování stavu hry
    int stavHry = 0;

    // Hlavní smyčka hry
    while (stavHry != 11) {
        switch (stavHry) {
        case 0:
            // Vstupní místnost
            writeLog(f1, "Nachazis se ve vstupni mistnosti\n");
            writeLog(f1, "Pred tebou jsou troje dvere. Kterymi pujdes?\n");
            writeLog(f1, "1. Modre dvere\n");
            writeLog(f1, "2. Cervene dvere\n");
            writeLog(f1, "3. Zelene dvere\n");
            writeLog(f1, "4. Prozkoumat mistnost\n");

            int volbaDveri;
            scanf("%d", &volbaDveri);

            switch (volbaDveri) {
            case 1:
                stavHry = 1;
                break;
            case 2:
                stavHry = 2;
                break;
            case 3:
                stavHry = 3;
                break;
            case 4:
                writeLog(f1, "Prozkoumal jsi mistnost a objevil jsi specialni klic!\n");
                hrac.hasChestKey = 1;
                break;
            default:
                writeLog(f1, "Neplatna volba. Zkuste to znovu.\n");
                break;
            }
            break;

        case 1:
            if (hrac.hasExitKey == 1){
                writeLog(f1, "Hadanku jsi jiz vyresil!\n");
                break;
            }
            // Místnost s hádankou a klíčem
            writeLog(f1, "Vesel jsi do slabe osvicene mistnosti a uprostred je stul\n");
            writeLog(f1, "Na stole lezi papir s hadankou:\n");
            writeLog(f1, "Bez klice a vika schranka pokladni, a preci je zlaty poklad v ni. Co to je?\n");
            writeLog(f1, "1. Kaktus\n");
            writeLog(f1, "2. Vajicko\n");
            writeLog(f1, "3. Mys\n");
            writeLog(f1, "4. Vratit se zpet\n");

            int volbaHadanky;
            scanf("%d", &volbaHadanky);

            switch (volbaHadanky) {
            case 1:writeLog(f1, "Tesne vedle, ozvalo se. Zkus to znovu\n");
                break;
            case 2:
                writeLog(f1, "Na papir jsi napsal spravnou odpoved. Pod stolem cvakl suplik a v nem byl klic. Vzal si jej a vracis se zpet\n");
                hrac.hasExitKey = 1;
                stavHry = 0; // Hráč se vrací zpět
                break;
            case 3:
                writeLog(f1, "Tesne vedle, ozvalo se. Zkus to znovu\n");
                break;
            case 4:
                writeLog(f1, "Vracis se zpet\n");
                stavHry = 0; // Hráč se vrací zpět
                break;
            default:
                writeLog(f1, "Neplatna volba. Zkuste to znovu.\n");
                break;
            }
            break;

        case 2:
            if (hrac.hasEgg = 1){
                writeLog(f1, "Draci poklad uz mas!\n");
                break;
            }

            // Místnost s drakem
            writeLog(f1, "Nachazis se ve velkem salu\n");
            writeLog(f1, "Pred tebou stoji obrovsky drak. Co udelas?\n");
            writeLog(f1, "1. Bojovat\n");
            writeLog(f1, "2. Vytasit mec\n");
            writeLog(f1, "3. Utect\n");

            int volbaDraka;
            scanf("%d", &volbaDraka);

            switch (volbaDraka) {
            case 1:
                if (hrac.hasSword) {
                    writeLog(f1, "Vytasil jsi mec a uz mas nadeji\n");
                    stavHry = bojSDrakem(f1, &hrac) ? 21 : 22 ;
                }
                else {
                    writeLog(f1, "Bez mece nemas sanci tu bestii porazit. Tak ho vytahni\n");
                }
                break;
            case 2:
                pouzijSpecialniDovednost(f1, &hrac);
                break;
            case 3:
                stavHry = 8;
                break;
            default:
                writeLog(f1, "Neplatna volba. Zkuste to znovu.\n");
                break;
            }
            break;

        case 3:
            // Místnost s pokladem
            writeLog(f1, "Nachazis se v mistnosti s pokladem\n");
            writeLog(f1, "Pred tebou lezi truhla. Co udelas?\n");
            writeLog(f1, "1. Zkusit otevrit truhlu\n");
            writeLog(f1, "2. Prozkoumat mistnost\n");
            writeLog(f1, "3. Vratit se zpet\n");

            int volbaPokladu;
            scanf("%d", &volbaPokladu);

            switch (volbaPokladu) {
            case 1:
                if (hrac.hasChestKey) {
                    writeLog(f1, "Vzal jsi z truhly spoustu drahokamu\n");
                    hrac.hasChestTreasure = 1;
                    hrac.hasChestKey = 0;
                        // Hráč má klíč, vrací se zpět
                }
                else if (hrac.hasChestTreasure == 1){
                    writeLog(f1, "Uz jsi to tady vykrad!\n");
                }
                else {
                    writeLog(f1, "Truhla je zamcena a bez specialniho klice ji nemuzes otevrit\n");
                    writeLog(f1, "Vracis se zpet\n");
                        // Hráč nemá klíč
                }
                break;
            case 2:
                writeLog(f1, "Prozkoumal jsi mistnost a objevil jsi tajne dvere. Mas klic z mistnosti 1?\n");
                writeLog(f1, "1. Ano\n");
                writeLog(f1, "2. Ne\n");

                int volbaKlice;
                scanf("%d", &volbaKlice);

                switch (volbaKlice) {
                case 1:
                    if (hrac.hasExitKey) {
                        writeLog(f1, "Odemkl jsi tajne dvere a pokracujes dal\n");
                        stavHry = 10; // Hráč odemkl tajné dveře, přechází do místnosti 10
                    }
                    else {
                        writeLog(f1, "Odemknout dvere ti nepovedlo. Zkus to znovu, tentokrat s klicem\n");
                    }
                    break;
                case 2:
                    writeLog(f1, "Rozhodl jsi se nenechat se zaskocit a vratil ses zpet\n");
                    break;
                default:
                    writeLog(f1, "Neplatna volba. Zkuste to znovu.\n");
                    break;
                }
                break;

            case 3:
                writeLog(f1, "Vracis se zpet\n");
                stavHry = 0; // Hráč se vrací zpět
                break;
            default:
                writeLog(f1, "Neplatna volba. Zkuste to znovu.\n");
                break;
            }
            break;

        case 21:
            // Místnost s trofejí a pokladem po úspěšném poražení draka
            writeLog(f1, "Nachazis se v mistnosti s dracim pokladem\n");
            writeLog(f1, "Pred tebou je draci vejce a hromada zlata\n");
            writeLog(f1, "1. Vzit si vejce a zlato\n");
            writeLog(f1, "2. Odejit\n");
            writeLog(f1, "3. Prozkoumat mistnost\n");

            int volbaTrofeje;
            scanf("%d", &volbaTrofeje);

            switch (volbaTrofeje) {
            case 1:
                writeLog(f1, "Vzal jsi draci vejce a zlato. Vracis se zpatky, abys prozkoumal zbytek\n");
                stavHry = 0; // Hráč vzal trofej a zlato, zpět na začátek
                hrac.hasEgg = 1;
                break;
            case 2:
                stavHry = 0; // Odejít bez pokladu, zpět na začátek
            default:
                writeLog(f1, "Neplatna volba. Zkuste to znovu.\n");
                break;
            case 3:
                writeLog(f1, "Co sis myslel? Ze tady jeste neco bude?\n");

            }
            break;

        case 22:
            // Utek z místnosti s drakem
            writeLog(f1, "Utek se ti podaril\n");
            stavHry = 0; // Vrací hráče zpět do vstupní místnosti
            break;

        case 10:
            //Nejlepší možná výhra - zabití draka, nalezení klíčů a všech pokladů
            if (hrac.hasEgg == 1 && hrac.hasChestTreasure == 1){
                writeLog(f1, "Gratuluji ti, ziskal jsi vsechny poklady a dokonce i kralovstvi\n");
            }
            writeLog(f1, "Konec hry\n");
            writeLog(f1, "A nebo ne?\n");
            stavHry = 11; // Ukončení smyčky a programu
            fclose(f1);
            break;

        case 9:
            // Hráč odemkl tajné dveře, hra konci
            writeLog(f1, "Prisel jsi do mistnosti, kde stoji osoba a rika ti:\n");
            writeLog(f1, "Mistre bojovniku, uhodl jsi moji hadanku a za to ti predavam svoje kralovstvi\n");
            writeLog(f1, "Sundal si korunu a nasadil ti ji na hlavu\n");
            writeLog(f1, "\n");
            stavHry = 10; // Hra končí a hráč vyhrává
            break;

        default:
            writeLog(f1, "Neplatny stav hry. Konec programu.\n");
            stavHry = 11; // Ukončení smyčky a programu
            break;
        }
    }

    return 0;
}
