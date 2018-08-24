/*
 * Lamda Averager
 * Implementation of a rolling averager using shifts.
 * Used in conjunction with fixed point numbers.
 * 
 */

// Lamda value used for shifting in average calculation. Typically at least 3.
// Higher values lead to less ripple but slower settling times.
#define LAMDA_SHIFT     3

// typdef lamda_average_t to whatever type you want to work with
typedef fixedPoint_t lamda_average_t;

// prototypes
lamda_average_t calcAverage(lamda_average_t prevAverage, lamda_average_t newValue);