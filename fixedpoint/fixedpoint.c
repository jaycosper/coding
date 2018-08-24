
/*
 * Fixed Point Integer Representation
 * Method to handle fixed point integers in an embedded system
 */

#include <stdint.h>
#include "fixedpoint.h"

fixedPoint_t fixedPointAdd(fixedPoint_t a, fixedPoint_t b)
{
    fixedPoint_t sum;
    // simple addition of .all
    sum.all = a.all + b.all;
    return sum;
}

fixedPoint_t fixedPointSubt(fixedPoint_t a, fixedPoint_t b)
{
    fixedPoint_t diff;
    // simple subtraction of .all
    diff.all = a.all - b.all;
    return diff;
}

fixedPoint_t fixedPointMult(fixedPoint_t a, fixedPoint_t b)
{
    fixedPoint_t prod;
    fixedPointExtended_t temp;
    // simple multiplcation with shift of fractional size Q
    temp = (fixedPointExtended_t)a.all;
    temp *= (fixedPointExtended_t)b.all;
    prod.all = (temp >> FIXEDPOINT_Q);
    return prod;
}

fixedPoint_t fixedPointDiv(fixedPoint_t dividend, fixedPoint_t divisor)
{
    fixedPoint_t result;
    fixedPointExtended_t temp;
    // simple integer divide with shift of fractional size Q for dividend
    temp = (fixedPointExtended_t)dividend.all << FIXEDPOINT_Q;
    temp /= (fixedPointExtended_t)divisor.all;
    result.all = temp;
    return result;
}
