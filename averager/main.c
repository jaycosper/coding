/*
 * Main function for Lamda Averager
 *
 */

#include <stdint.h>
#include <stdio.h>
#include "lamda_ave.h"
#include "fixedpoint.h"
#include "assert.h"

void main(void)
{
    lamda_average_t ave;
    lamda_average_t input;

    ave.all = 0;
    input.all = 0x8000;

    printf("previous average 0x%X\n", ave.all);
    ave = calcAverage(ave, input);

    printf("new average 0x%X\n", ave.all);

    return;
}