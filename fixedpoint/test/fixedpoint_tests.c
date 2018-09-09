/*
 * Test Main for Fixed Point Integer Representation
 * Method to handle fixed point integers in an embedded system
 */

#include <stdint.h>
#include <stdio.h>
#include "fixedpoint.h"
#include "CuTest.h"

void testFixedpoint(CuTest* tc)
{
    fixedPoint_t a;
    a.all = 3160; // I = 3160 >> 8, Q = (3160 && 0xFF)/2^Q => I = 12, Q = 88/(2^Q) = 0.34375 => I + Q = 12.375
    fixedPoint_t b;
    b.all = 888; // I = 888 >> 8 = 3, Q = (888 && 0xFF)/2^Q = 0.46875 => I + Q = 3.46875
    fixedPoint_t aneg = a;
    aneg.all = -aneg.all;
    fixedPoint_t bneg = b;
    bneg.all = -bneg.all;

    fixedPoint_t result;

    // add / subtract
    result = fixedPointAdd(a, b); // target value = 12.375 + 3.46875 = 15.84375 (4048)
    CuAssertIntEquals(tc, result.all, 4048);
    printf("a + b sum: %i\n", result.all);

    result = fixedPointSubt(a, b); // target value = 12.375 - 3.46875 = 8.90625 (2272)
    CuAssertIntEquals(tc, result.all, 2272);
    printf("a - b diff: %i\n", result.all);

    result = fixedPointSubt(b, a); // target value = 3.46875 - 12.375 = -8.90625 (-2272)
    CuAssertIntEquals(tc, result.all, -2272);
    printf("b - a diff: %i\n", result.all);

    result = fixedPointAdd(aneg, bneg); // target value = -12.375 + -3.46875 = -15.84375 (-4048)
    CuAssertIntEquals(tc, result.all, -4048);
    printf("-a + -b diff: %i\n", result.all);

    // multiply / divide
    result = fixedPointMult(a, b); // target value = 12.375 * 3.46875 = 42.82171875 (10962)
    CuAssertIntEquals_Msg(tc, "Multiply failure!", result.all, 10961); // rounding error
    printf("a * b product: %i\n", result.all);

    result = fixedPointDiv(a, b); // target value = 12.375 / 3.46875 = 3.558918919 (911)
    CuAssertIntEquals_Msg(tc, "Divide failure!", result.all, 910); // rounding error
    printf("a / b divide: %i\n", result.all);

    printf("UINT32_MAX: %u\n", UINT32_MAX);
    printf("INT32_MAX: %i\n", INT32_MAX);
    printf("INT32_MIN: %i\n", INT32_MIN);
}

CuSuite* CuGetSuite(void)
{
    CuSuite* suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, testFixedpoint);

    return suite;
}
