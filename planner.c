#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "timelib.h"

#define zero 0
#define one 1
#define two 2
#define three 3
#define four 4
#define five 5
#define six 6
#define seven 7
#define eight 8
#define nine 9
#define thirtyone 31
#define fifteen 15
#define ten 10
#define eleven 11
#define twelve 12
#define startyear 1970
#define hour_in_sec 3600
#define tenthousand 10000
typedef struct {
    unsigned int start;
    unsigned int final;
}interval;

typedef struct {
    char *nume;
    int index;
    unsigned int *start;
    unsigned int *final;
    int numar;
}persoana;



int main() {
    // alocare dinamica
    interval *ore_disponibile = malloc(tenthousand * sizeof(interval));
    persoana *pers = malloc(ten * sizeof(persoana));
    for (int i = zero; i < ten; ++i) {
        pers[i].start = calloc(ten, sizeof(unsigned int));
        pers[i].final = calloc(ten, sizeof(unsigned int));
        pers[i].nume = calloc(ten, sizeof(char));
    }
    TTimezone *zone = malloc(eight * sizeof(TTimezone));
    int numar_zone = zero;
    // citire zone
    scanf("%d", &numar_zone);
    for (int i = zero; i <  numar_zone; ++i) {
        char s[five] = "";
        int dif = zero;
        scanf("%s%d", s, &dif);
        strncpy(zone[i].name, s, five);
        zone[i].utc_hour_difference = (signed char)dif;
    }
    // citire persoane si intervale posibile
    int numar_pers = zero;
    scanf("%d", &numar_pers);
    for (int i = zero; i < numar_pers; ++i) {
        char nume[ten] = "", s[five] = "";
        TDateTimeTZ aux;
        scanf("%s%s", nume, s);
        for (int j = zero; j < numar_zone; ++j) {
            if (strcmp(zone[j].name, s) == zero) {
                aux.tz = &zone[j];
                pers[i].index = j;
            }
        }
        strncpy(pers[i].nume, nume, ten);
        int n_date = zero;
        scanf("%d", &n_date);
        pers[i].numar = n_date;
        for (int j = zero; j <  n_date; ++j) {
            int day = zero, month = zero, year = zero, hour = zero, x = zero;
            scanf("%d%d%d%d%d", &year, &month, &day, &hour, &x);
            aux.date.year = year;
            aux.date.month = month;
            aux.date.day = day;
            aux.time.hour = hour;
            aux.time.min = zero;
            aux.time.sec = zero;
            // printDateTimeTZ(aux);
            pers[i].start[j] = convertDateTimeTZToUnixTimestamp(aux);
            // printf("%u", pers[i].start[j]);
            // printDateTimeTZ(convertUnixTimestampToDateTimeTZ(pers[i].start[j],zone, pers[i].index));
            pers[i].final[j] = pers[i].start[j] + hour_in_sec * x;
        }
    }
    // transformam intervalele in intervalele maxime
    int result = zero, numar_ore = zero, n_pers = zero;
    scanf("%d%d", &n_pers, &numar_ore);
    for (int i = 0; i < numar_pers; ++i) {
        for (int j = 1; j < pers[i].numar; ++j) {
            if (pers[i].start[j] == pers[i].final[j-1]) {
                pers[i].final[j-1] = pers[i].final[j];
                for (int l = j; l < pers[i].numar - 1; ++l) {
                    pers[i].start[l] = pers[i].start[l + 1];
                    pers[i].final[l] = pers[i].final[l + 1];
                }
                j--;
                pers[i].numar--;
            }
        }
    }
    // eliminam intervalele mai mici decat numarul de ore necesar
    for (int i = zero; i < numar_pers; ++i) {
        for (int j = zero; j < pers[i].numar; ++j) {
            if ((pers[i].final[j] - pers[i].start[j]) / hour_in_sec < numar_ore) {
                for (int l = j; l < pers[i].numar - one; ++l) {
                    pers[i].start[l] = pers[i].start[l + one];
                    pers[i].final[l] = pers[i].final[l + one];
                }
                j--;
                pers[i].numar--;
            }
        }
    }
    // creere lista cu toare intervalele
    int numar_intervale = zero;
    for (int i = zero; i < numar_pers; ++i) {
        for (int j = zero; j < pers[i].numar; ++j) {
            for (unsigned int k = pers[i].start[j]; k < pers[i].final[j]; k += numar_ore * hour_in_sec) {
                ore_disponibile[numar_intervale].start = k;
                ore_disponibile[numar_intervale++].final = k + numar_ore * hour_in_sec;
            }
        }
    }
    // sortam crescator persoanele
    for (int i = 0; i < numar_pers; ++i) {
        for (int j = i + 1; j < numar_pers; ++j) {
            if (strcmp(pers[i].nume, pers[j].nume) > 0) {
                persoana aux = pers[i];
                pers[i] = pers[j];
                pers[j] = aux;
            }
        }
    }
    // sortam crescator toare intervalele
    for (int i = 0; i < numar_intervale; ++i) {
        for (int j = i + 1; j < numar_intervale; ++j) {
            if (ore_disponibile[i].start > ore_disponibile[j].start) {
                interval aux = ore_disponibile[i];
                ore_disponibile[i] = ore_disponibile[j];
                ore_disponibile[j] = aux;
            } else if (ore_disponibile[i].start == ore_disponibile[j].start
            && ore_disponibile[i].final > ore_disponibile[j].final) {
                interval aux = ore_disponibile[i];
                ore_disponibile[i] = ore_disponibile[j];
                ore_disponibile[j] = aux;
            }
        }
    }
    // eliminam intervalele care se repera
    for (int i = one; i < numar_intervale; ++i) {
        if (ore_disponibile[i].start == ore_disponibile[i - one].start
        && ore_disponibile[i].final == ore_disponibile[i - one].final) {
            for (int j = i; j < numar_intervale - one; ++j) {
                ore_disponibile[j] = ore_disponibile[j + one];
            }
            i--;
            numar_intervale--;
        }
    }
    result = zero;
    int *val = calloc(ten, sizeof(int));
    for (int i = 0; i < numar_intervale && !result; ++i) {
        int pot = 0;
        for (int l = 0; l < numar_pers; ++l) {
            val[l] = 0;
            for (int ll = 0; ll < pers[l].numar && !val[l]; ++ll) {
                if (pers[l].start[ll] <= ore_disponibile[i].start
                && pers[l].final[ll] >= ore_disponibile[i].final) {
                    pot++;
                    val[l] = ll + 1;
                }
            }
        }
        if (pot >= n_pers) {
            result++;
            for (int l = 0; l < numar_pers; ++l) {
                if (val[l]) {
                    printf("%s: ", pers[l].nume);
                    printDateTimeTZ(convertUnixTimestampToDateTimeTZ(ore_disponibile[i].start, zone, pers[l].index));
                } else {
                    printf("%s: invalid\n", pers[l].nume);
                }
            }
        }
    }
    if (!result)
        printf("imposibil");
    free(val);
    free(zone);
    free(ore_disponibile);
    for (int i = zero; i < ten; ++i) {
        free(pers[i].start);
        free(pers[i].final);
        free(pers[i].nume);
    }
    free(pers);
    return 0;
}
