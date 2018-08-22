/*
 * Fixed Point Integer Representation
 * Method to handle fixed point integers in an embedded system
 */

#ifndef __FIXEDPOINT_H__
#define __FIXEDPOINT_H__

#include <stdint.h>

// Q<integer>.<fractional>
// where integer = 32-fractional
// integer resolution is 2^<integer>-1 or 2^(integer-1)-1 for signed
// fractional resolution is 1/(2^<fractional>)
// i.e. signed Q8.8 has an integer range of +/-2^(8-1) or +/-127
// and a fractional resolution of 1/2^(8) or 0.00390625

// stored as one 32-bit number
#define FIXEDPOINT_I    8
#define FIXEDPOINT_Q    8
typedef struct _fixedPoint_t_
{
    union
    {
        int32_t integer     :FIXEDPOINT_I;
        int32_t fraction    :FIXEDPOINT_Q;
#if (FIXEDPOINT_I + FIXEDPOINT_Q != 32)
        int32_t rsvd        :(32-FIXEDPOINT_I-FIXEDPOINT_Q);
#endif
    };
    uint32_t all;
} fixedPoint_t;

// extended temporary variable must be twice size of fixedPoint_t base for multplication and divide
typedef int64_t fixedPointExtended_t;

fixedPoint_t fixedPointAdd(fixedPoint_t a, fixedPoint_t b);
fixedPoint_t fixedPointSubt(fixedPoint_t a, fixedPoint_t b);
fixedPoint_t fixedPointMult(fixedPoint_t a, fixedPoint_t b);
fixedPoint_t fixedPointDiv(fixedPoint_t dividend, fixedPoint_t divisor);

#endif // __FIXEDPOINT_H__