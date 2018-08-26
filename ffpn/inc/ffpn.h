/*
 * Fake Floating Point Numbers
 * Method to handle floating point numbers in an embedded system without
 * floating point library.
 */

#ifndef __FFPN_H__
#define __FFPN_H__

#include <stdint.h>

#define DW_STORAGE 0

// stored as one 32-bit number
typedef struct _fakeFloat_t_
{
#if DW_STORAGE
    int32_t num     :24;    // numerator
    int32_t shift   :8;     // right-shift values (use negative for left-shift)
#else
    int32_t num;    // numerator
    int8_t shift;   // right-shift values (use negative for left-shift)
#endif
} fakeFloat_t;

// prototypes
fakeFloat_t ffpn_add(fakeFloat_t a, fakeFloat_t b);
fakeFloat_t ffpn_subt(fakeFloat_t a, fakeFloat_t b);
fakeFloat_t ffpn_mult(fakeFloat_t a, fakeFloat_t b);
fakeFloat_t ffpn_div(fakeFloat_t dividend, fakeFloat_t divisor);

#endif // __FFPN_H__
