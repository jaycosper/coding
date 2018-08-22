
/*
 * Fake Floating Point Numbers
 * Method to handle floating point numbers in an embedded system without
 * floating point library.
 *
 * Based on algorithms in "Making Embedded Systems" by Elecia White
 *
 */

#include <stdint.h>
#include <stdio.h>
#include "ffpn.h"
#include "assert.h"

// need to define INT24_MAX for DW_STORAGE
#define INT24_MAX 8388607 // 2^23-1 because of sign bit
// other _MAX defines already exist

// a+b
fakeFloat_t ffpn_add(fakeFloat_t a, fakeFloat_t b)
{
    int32_t temp; // must be large enough to handle overflow of shifting
    fakeFloat_t sum;

    // start with a.num
    temp = a.num;
    // shift a.num by difference between shift (common denom with b)
    temp <<= (b.shift - a.shift);
    // now add in b.num
    temp += b.num;
    sum.shift = b.shift;
    while (temp > INT24_MAX || temp < -INT24_MAX)
    {
        temp >>= 1;
        sum.shift--;
    }
    sum.num = temp;
    return sum;
}

// a-b
fakeFloat_t ffpn_subt(fakeFloat_t a, fakeFloat_t b)
{
    int32_t temp; // must be large enough to handle overflow of shifting
    fakeFloat_t diff;

    // start with a.num
    temp = a.num;
    // shift a.num by difference between shift (common denom with b)
    temp <<= (b.shift - a.shift);
    // now subtract b.num
    temp -= b.num;
    diff.shift = b.shift;
    while (temp > INT24_MAX || temp < -INT24_MAX)
    {
        temp >>= 1;
        diff.shift--;
    }
    diff.num = temp;
    return diff;
}

// a*b
fakeFloat_t ffpn_mult(fakeFloat_t a, fakeFloat_t b)
{
    int64_t temp; // at least twice numerator size
    int64_t stemp;
    fakeFloat_t prod;

    // multiply numerators
    // This stage is performed in two steps to first upgrade the
    // storage variable and then multiply. Otherwise, a*b would
    // overflow in 32 bit field, and then be stored in 64 bit variable.
    temp = a.num;
    temp *= b.num;

    // add shift terms
    stemp = a.shift + b.shift;
    // check for overflow -- nothing can be done if in violation
    ASSERT(stemp < INT8_MAX);
    ASSERT(stemp > -INT8_MAX);
    prod.shift = stemp;

    while (temp > INT32_MAX || temp < -INT32_MAX)
    {
        temp >>= 1;
        prod.shift--;
    }
    prod.num = temp;

    return prod;
}

// dividend/divisor
fakeFloat_t ffpn_div(fakeFloat_t dividend, fakeFloat_t divisor)
{
    int64_t temp; // at least twice numerator size
    int64_t stemp;
    fakeFloat_t quot;

    // divide numerators
    // This stage is performed in two steps to first upgrade the
    // storage variable and then multiply. Otherwise, a*b would
    // overflow in 32 bit field, and then be stored in 64 bit variable.
    temp = dividend.num;
    // integer divide
    temp /= divisor.num;

    stemp = dividend.shift - divisor.shift;
    ASSERT(stemp < INT8_MAX);
    ASSERT(stemp > -INT8_MAX);
    quot.shift = stemp;

    while (temp > INT32_MAX || temp < -INT32_MAX)
    {
        temp >>= 1;
        quot.shift--;
    }
    quot.num = temp;

    return quot;
}

void main(void)
{
    fakeFloat_t oneFourth = {1, 2}; // 1 >> 2 = 1 / (2^2) = 1/4 = 0.25
    fakeFloat_t four = {1, -2}; // 1 << 2 = 1 / (2^-2) = 1*(2^2) = 4
    fakeFloat_t a = {99, 3}; // 99 >> 3 = 99 / (2^3) = 12.375
    fakeFloat_t b = {111, 5}; // 111 >> 5 = 11 / (2^5) = 3.46875
    fakeFloat_t bneg = b;
    bneg.num = -bneg.num;

    fakeFloat_t result;

    // add / subtract
    result = ffpn_add(a, b); // target value = 12.375 + 3.46875 = 15.84375
    printf("sum: %i.%i\n", result.num, result.shift);
    result = ffpn_add(a, bneg); // target value = 12.375 + (-3.46875) = 8.90625
    printf("sum neg: %i.%i\n", result.num, result.shift);
    result = ffpn_subt(a, b); // target value = 12.375 - 3.46875 = 8.90625
    printf("diff: %i.%i\n", result.num, result.shift);
    result = ffpn_subt(a, bneg); // target value = 12.375 - (-3.46875) = 15.84375
    printf("diff neg: %i.%i\n", result.num, result.shift);

    // multiply / divide
    a.num = 1656917852; a.shift = 27; // 1656917852/(2^27) = 12.345
    b.num = 128; b.shift = 8; // 128/(2^8) = 0.5
    result = ffpn_mult(a, b); // target value = 6.1725
    printf("product: %i.%i\n", result.num, result.shift);

    return;
}