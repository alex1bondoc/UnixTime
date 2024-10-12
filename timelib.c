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
#define thirty 30
#define twentynine 29
#define twentyeight 28
#define daysec 86400
#define yearday 365
#define sixty 60
#define twentyfour 24
#define hundred 100
#define fourhundred 400
TTime convertUnixTimestampToTime(unsigned int timestamp) {
    TTime result;
    result.sec = timestamp % sixty;
    timestamp /= sixty;
    result.min = timestamp % sixty;
    timestamp /= sixty;
    result.hour = timestamp % twentyfour;
    return result;
}
TDate convertUnixTimestampToDateWithoutLeapYears(unsigned int timestamp) {
    TDate result;
    int luni_an[twelve] = {thirtyone, twentyeight, thirtyone, thirty, thirtyone,
    thirty, thirtyone, thirtyone, thirty, thirtyone, thirty, thirtyone};
    int day = (int)(timestamp / daysec);
    int i = zero;
    result.day = one;
    result.year = startyear;
    while (day >= luni_an[i]) {
        day -= luni_an[i];
        i++;
        if (i > eleven)
            i = zero, result.year += one;
    }
    result.day += day;
    result.month = i + one;
    return result;
}
TDate convertUnixTimestampToDate(unsigned int timestamp) {
    TDate result;
    int luni_an[twelve] = {thirtyone, twentyeight, thirtyone, thirty, thirtyone,
    thirty, thirtyone, thirtyone, thirty, thirtyone, thirty, thirtyone};
    int day = (int)(timestamp / daysec);
    int i = zero;
    result.day = one;
    result.year = startyear;
    if ((result.year % four == zero && result.year % hundred != zero) || result.year % fourhundred == zero)
        luni_an[one] = twentynine;
    else
        luni_an[one] = twentyeight;
    while (day >= luni_an[i]) {
        day -= luni_an[i];
        i++;
        if (i > eleven)
            i = zero, result.year += one;
        if ((result.year % four == zero && result.year % hundred != zero) || result.year % fourhundred == zero)
            luni_an[one] = twentynine;
        else
            luni_an[one] = twentyeight;
    }
    result.day += day;
    result.month = i + one;
    return result;
}
TDateTimeTZ convertUnixTimestampToDateTimeTZ(unsigned int timestamp, TTimezone *timezones, int timezone_index) {
    TDateTimeTZ result;
    result.tz = &timezones[timezone_index];
    int diferenta = (int)timezones[timezone_index].utc_hour_difference;
    timestamp +=  hour_in_sec * diferenta;
    result.time = convertUnixTimestampToTime(timestamp);
    result.date = convertUnixTimestampToDate(timestamp);
    return result;
}
unsigned int convertDateTimeTZToUnixTimestamp(TDateTimeTZ x) {
    unsigned int timestamp = zero;
    int luni_an[twelve] = {thirtyone, twentyeight, thirtyone, thirty,
    thirtyone, thirty, thirtyone, thirtyone, thirty, thirtyone, thirty, thirtyone};
    int year = zero, month = zero, day = zero, hour = zero, min = zero, sec = zero;
    year = (int)x.date.year;
    month = x.date.month;
    day = x.date.day;
    hour = x.time.hour;
    min = x.time.min;
    sec = x.time.sec;
    hour -= x.tz->utc_hour_difference;
    if ((year % four == zero && year % hundred != zero) || year % fourhundred == zero)
        luni_an[one] = twentynine;
    else
        luni_an[one] = twentyeight;
    while (year > startyear) {
        timestamp += yearday * daysec;
        if (((year % four == zero && year % hundred != zero) || year % fourhundred == zero)
        && year != x.date.year)
            timestamp += daysec;
        year--;
    }
    for (int i = one; i < month; ++i) {
        timestamp += luni_an[i - one] * daysec;
    }
    timestamp += (day - one) *  daysec;
    timestamp += hour * hour_in_sec + min * sixty +  sec;
    return timestamp;
}
void printDateTimeTZ(TDateTimeTZ datetimetz) {
    if (datetimetz.date.day > nine)
        printf("%d ", datetimetz.date.day);
    else
    printf("0%d ", datetimetz.date.day);
    switch (datetimetz.date.month) {
        case one:
            printf("ianuarie ");
            break;
        case two:
            printf("februarie ");
            break;
        case three:
            printf("martie ");
            break;
        case four:
            printf("aprilie ");
            break;
        case five:
            printf("mai ");
            break;
        case six:
            printf("iunie ");
            break;
        case seven:
            printf("iulie ");
            break;
        case eight:
            printf("august ");
            break;
        case nine:
            printf("septembrie ");
            break;
        case ten:
            printf("octombrie ");
            break;
        case eleven:
            printf("noiembrie ");
            break;
        case twelve:
            printf("decembrie ");
            break;
    }
    printf("%d, ", datetimetz.date.year);
    if (datetimetz.time.hour < ten)
        printf("0%d:", datetimetz.time.hour);
    else
        printf("%d:", datetimetz.time.hour);
    if (datetimetz.time.min < ten)
        printf("0%d:", datetimetz.time.min);
    else
        printf("%d:", datetimetz.time.min);
    if (datetimetz.time.sec < ten)
        printf("0%d ", datetimetz.time.sec);
    else
        printf("%d ", datetimetz.time.sec);
    printf("%s ", datetimetz.tz->name);
    if (datetimetz.tz->utc_hour_difference >= zero) {
        printf("(UTC+%d)\n", datetimetz.tz->utc_hour_difference);
    } else {
        printf("(UTC%d)\n", datetimetz.tz->utc_hour_difference);
    }
}
    /*int year, month, day, hour, min, sec;
    TDateTimeTZ test;
    TTimezone zona;
    int n;
    scanf("%d%d%d%d%d%d", &day, &month, &year, &hour, &min, &sec);
    test.date.year = year;
    test.date.month = month;
    test.date.day = day;
    test.time.hour = hour;
    test.time.min = min;
    test.time.sec = sec;
    char s[5];
    int dif;
    scanf("%s%d", s, &dif);
    strcpy(zona.name, s);
    zona.utc_hour_difference = dif;
    test.tz = &zona;
    printDateTimeTZ(test);
    */
