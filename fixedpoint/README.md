# Fixed-point Math Library
## Desciption
Library of fixed-point math handlers. Fixed-point math is a method to represent decimal numbers without floating-point (but with some loss of resolution).
## Defines
```C
#define FIXEDPOINT_SIZE 32
#define FIXEDPOINT_Q    8
#define FIXEDPOINT_I    (FIXEDPOINT_SIZE - FIXEDPOINT_Q)
```
## Types
```C
typedef union _fixedPoint_t_
{
    struct
    {
        uint32_t fraction   : FIXEDPOINT_Q;
        int32_t integer     : FIXEDPOINT_I;
    };
    uint32_t all;
} fixedPoint_t;
```
## APIs
```C
fixedPoint_t fixedPointAdd(fixedPoint_t a, fixedPoint_t b);
fixedPoint_t fixedPointSubt(fixedPoint_t a, fixedPoint_t b);
fixedPoint_t fixedPointMult(fixedPoint_t a, fixedPoint_t b);
fixedPoint_t fixedPointDiv(fixedPoint_t dividend, fixedPoint_t divisor);
```
## Required Libraries
None
## Tested Target
- x86
## Usage
```C
int someCall(int * alpha)
{
    ASSERT(alpha != NULL);
    return *alpha;
}
```
## Details
### How to convert
Conversion is fairly simple. The I bits represent the integer portion of the number. The Q bits represent the fractional portion.

The resolution depends on the number of Q bits. In the above case, Q = 8, so the resolution is:

1 / (2^Q) = 1 / (2^8) = 1 / 256 = 0.00390625

A spreadsheet may be used to calculate conversions in a simple manner. Some examples:

target Number | I | Q | Actual | Error | %Error | .all
----- | ----- | ----- | ----- | ----- | ----- | -- | ---
12.345 | 12 | 88 | 12.34375 | 0.00125 | 0.010 | 3160
0.5 | 0 | 128 | 0.5 | 0 | 0 | 128
0.25 | 0 | 64 | 0.25 | 0 | 0 | 64
3.46875 | 3 | 120 | 3.46875 | 0 | 0 | 888
15.81375 | 15 | 208 | 15.8125 | 0.00125 | 0.008 | 4048
8.87625 | 8 | 224 | 8.875 | 0.00125 | 0.014 | 2272
-8.87625 | -9 | 32 | -8.875 | -0.00125 | 0.014 | -2272