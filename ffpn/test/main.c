/*
 * Fake Floating Point Numbers
 * Implementation and test
 *
 */

#include <stdio.h>
#include "ffpn.h"

int main(void)
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
    printf("product: %i.%i = %f\n", result.num, result.shift, ((float)result.num/(1<<result.shift)));
    result = ffpn_div(four, oneFourth); // target value = 16
    printf("divide: %i.%i = %f\n", result.num, result.shift, ((float)result.num/(1<<result.shift)));

    return 0; // Ctest uses return 0 for pass
}
