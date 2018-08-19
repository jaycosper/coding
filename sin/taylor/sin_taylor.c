#include <stdint.h>
#include <stdio.h>

/*
 * Basic algorithm to calculate SIN using Taylor series expansion (3 coefficients)
 * to avoid using floating-point libraries on embedded designs.
 * Based on algorithms in "Making Embedded Systems" by Elecia White
 * 
 * Algorithm:
 * sin(x) ~ x + x^3/3! - x^5/5! + x^7/7! = x*(1 - x^2*(A + x^2*(B - C*x^2)))
 * sin(x) ~ x*(1 - x^2*(FACT3 + x^2*(FACT5 - FACT7*x^2)))
 * 
 * NOTE: Taylor series expansions, especially Horner's scheme, are only accurate around 0.
 * This algorithm should be used for calculations between -PI/2 < x < PI/2.
 */

// Factorials calculated by multiplication and then shifting by power of 2
// 1/(3!) ~ 171/(2^10) = 171/1024 = 0.166992
#define DIVIDE_BY_THREE_FACT_MULT   171
#define DIVIDE_BY_THREE_FACT_SHIFT  10
// 1/(5!) = 0.008333 ~ 17/(2^11) = 17/2048 = 0.00830
#define DIVIDE_BY_FIVE_FACT_MULT    17
#define DIVIDE_BY_FIVE_FACT_SHIFT   11
// 1/(7!) = 1984127e-6 ~ 13/(2^16) = 13/65536 = 198e-6
#define DIVIDE_BY_SEVEN_FACT_MULT   17
#define DIVIDE_BY_SEVEN_FACT_SHIFT  16

// scale all input to remove floating point numbers
// i.e. for PI/2 = 1.571 <=> PI/2*2^SCALED_INPUT_FACTOR
#define SCALED_INPUT_SHIFT 11

#define PI 6434 // 3.141592654 scaled by 2^11 manually

// can pre-calculate 3! and 5! since they are added to other terms
// Scaling factor should be equal to or greater than factorial shift factor so as not to loose resolution
#define SCALED_INVERSE_FACT_THREE ((DIVIDE_BY_THREE_FACT_MULT<<SCALED_INPUT_SHIFT)>>DIVIDE_BY_THREE_FACT_SHIFT)
#define SCALED_INVERSE_FACT_FIVE ((DIVIDE_BY_FIVE_FACT_MULT<<SCALED_INPUT_SHIFT)>>DIVIDE_BY_FIVE_FACT_SHIFT)
#define SCALED_INVERSE_FACT_SEVEN ((DIVIDE_BY_FIVE_FACT_MULT<<SCALED_INPUT_SHIFT)>>DIVIDE_BY_FIVE_FACT_SHIFT)

int32_t divideByThreeFact(int32_t input)
{
    int32_t temp;
    temp = input * DIVIDE_BY_THREE_FACT_MULT;
    temp = temp >> DIVIDE_BY_THREE_FACT_SHIFT;
    return temp;
}

int32_t divideByFiveFact(int32_t input)
{
    int32_t temp;
    temp = input * DIVIDE_BY_FIVE_FACT_MULT;
    temp = temp >> DIVIDE_BY_FIVE_FACT_SHIFT;
    return temp;
}

int32_t divideBySevenFact(int32_t input)
{
    int32_t temp;
    temp = input * DIVIDE_BY_SEVEN_FACT_MULT;
    temp = temp >> DIVIDE_BY_SEVEN_FACT_SHIFT;
    return temp;
}

int32_t sin_taylor(int32_t theta)
{
    // sin(x) = x * (1 - x^2*(1/3! + (x^2*(1/5! - x^2*(1/7!))))
    int32_t temp;
    int32_t x;
    int32_t xSq;
    int32_t sinX;

    x = theta;
    // need to shift by SCALED_INPUT_SHIFT in order to only scale input once
    // this needs to be done each time we multiply by the input
    xSq = (x * x) >> SCALED_INPUT_SHIFT;

    temp = - divideBySevenFact(xSq);
    temp = (xSq * (SCALED_INVERSE_FACT_FIVE + temp)) >> SCALED_INPUT_SHIFT;
    temp = (xSq * (-SCALED_INVERSE_FACT_THREE + temp)) >> SCALED_INPUT_SHIFT;
    sinX = x - ((x * temp)>>SCALED_INPUT_SHIFT);

    return sinX;
}

#define INDEX_RANGE 16
void main(void)
{
    int32_t idx;
    int32_t value;
    int32_t theta;

    for (idx=-INDEX_RANGE+1; idx<INDEX_RANGE; idx++)
    {
        theta = (idx*PI)/(2*(2*INDEX_RANGE));
        value = sin_taylor(theta);
        printf("%i: sin(%i) = %i\n", idx, theta, value);
    }
    return;
}