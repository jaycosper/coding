/*
 * Main function for Lamda Averager
 *
 */

#include <stdint.h>
#include <stdio.h>
#include "fixedpoint.h"
#include "lamda_ave.h"
#include "assert.h"

int main(void)
{
    lamda_average_t ave;
    lamda_average_t input;

    char const* const fileName = "./input.txt";
    FILE* fptr = fopen(fileName, "r"); /* should check the result */
    ASSERT(fptr != NULL);
    int inputValue;

    ave.all = 0;

    while (fscanf(fptr,"%d", &inputValue) != 0) {
        // loops until non-integer line scanned
        input.all = inputValue;
        ave = calcAverage(ave, input);
        printf("%d\n", ave.all);
    }

    fclose(fptr);

    return 0; // Ctest uses return 0 for pass
}
