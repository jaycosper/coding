#include <stdint.h>
#include <stdio.h>

/*
 * Basic algorithm to calculate SIN using lookup table
 * to avoid using floating-point libraries on embedded designs.
 * Based on algorithms in "Making Embedded Systems" by Elecia White
 */
const int32_t sinLookup[] = {
    0,    // x = -3216
    -253,    // x = -2960
    -490,    // x = -2704
    -697,    // x = -2448
    -861,    // x = -2192
    -971,    // x = -1936
    -1021,    // x = -1680
    -1007,    // x = -1424
    -931,    // x = -1168
    -796,    // x = -912
    -612,    // x = -656
    -390,    // x = -400
    -144,    // x = -144
    110,    // x = 111
    359,    // x = 367
    585,    // x = 623
    774,    // x = 879
    916,    // x = 1135
    1000,    // x = 1391
    1023,    // x = 1647
    981,    // x = 1903
    879,    // x = 2159
    722,    // x = 2415
    520,    // x = 2671
    286,    // x = 2927
};

#define TABLE_INCREMENT 8
#define TABLE_MINIMUM -3141

int32_t sin_lkuptable(int32_t theta)
{
    int32_t index;
    int32_t sinX;

    // subtract a half step to center the index
    index = (theta - (TABLE_MINIMUM - (2^(TABLE_INCREMENT-1))))>>TABLE_INCREMENT;
    sinX = sinLookup[index];
    return sinX;
}

#define INDEX_RANGE 16
#define PI 3216
void main(void)
{
    int32_t idx;
    int32_t value;
    int32_t theta;
    FILE *fp;

    fp = fopen("test.txt", "w+");
    for (idx=-PI; idx<PI; idx+=(1<<TABLE_INCREMENT-1))
    //for (idx=-INDEX_RANGE+1; idx<INDEX_RANGE; idx++)
    {
        theta = idx;
        //theta = (idx*PI)/(8*(2*INDEX_RANGE));
        value = sin_lkuptable(theta);
        printf("%i\n", value);
        fprintf(fp, "%i\n", value);
        //printf("%i,%i\n", theta, value);
        //printf("%i: sin(%i) = %i\n", idx, theta, value);
    }
    fclose(fp);
    return;
}