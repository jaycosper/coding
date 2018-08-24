/*
 * Lamda Averager
 * Implementation of a rolling averager using shifts.
 * Used in conjunction with fixed point numbers.
 * 
 * Equation: y' = lamda*x + (1 - lamda)*y = lamda*x + y - lamda*y,
 *  where:
 *      x: input value
 *      y: previous average (0 at init, or seeded for faster settling)
 *      y': new average
 *      lamda: negative power of 2 for shifting, typically 3 or greater (i.e. lamda = x*2^-3 = x>>3)
 *
 */

#include <stdint.h>
#include "lamda_ave.h"
#include "fixedpoint.h"

lamda_average_t calcAverage(lamda_average_t prevAverage, lamda_average_t newValue)
{
    uint32_t status = 0;
    lamda_average_t temp;
    lamda_average_t y_shifted;
    lamda_average_t x_shifted;

    // y>>lamda
    y_shifted.all = (prevAverage.all >> LAMDA_SHIFT);
    // y - (y>>lamda)
    temp = fixedPointSubt(prevAverage, y_shifted);
    // x>>lamda
    x_shifted.all = (newValue.all >> LAMDA_SHIFT);
    // (x>>lamda) + [y - (y>>lamda)]
    temp = fixedPointAdd(x_shifted, temp);
    // update average
    return temp;
}