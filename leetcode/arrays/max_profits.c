// Best Time to Buy and Sell Stock II
//
// Say you have an array prices for which the ith element is the price of a given stock on day i.
//
// Design an algorithm to find the maximum profit. You may complete as many transactions as you like (i.e., buy one and sell one share of the stock multiple times).
//
// Note: You may not engage in multiple transactions at the same time (i.e., you must sell the stock before you buy again).
//
// Example 1:
//
// Input: [7,1,5,3,6,4]
// Output: 7
// Explanation: Buy on day 2 (price = 1) and sell on day 3 (price = 5), profit = 5-1 = 4.
//              Then buy on day 4 (price = 3) and sell on day 5 (price = 6), profit = 6-3 = 3.
//
// Example 2:
//
// Input: [1,2,3,4,5]
// Output: 4
// Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.
//              Note that you cannot buy on day 1, buy on day 2 and sell them later, as you are
//              engaging multiple transactions at the same time. You must sell before buying again.
//
// Example 3:
//
// Input: [7,6,4,3,1]
// Output: 0
// Explanation: In this case, no transaction is done, i.e. max profit = 0.
//
//
//
// Constraints:
//
//     1 <= prices.length <= 3 * 10 ^ 4
//     0 <= prices[i] <= 10 ^ 4

#include <stdbool.h>

int maxProfit(int* prices, int pricesSize){
    bool bSellFlag = false; // true = buy, false = sell
    int buyPrice;
    int pricePeak = 0;
    int priceValley = 10001;
    int profit = 0;

    for (int i=0; i< pricesSize; i++)
    {
        if (bSellFlag == false)
        {
            if (prices[i]<priceValley)
            {
                // looking to buy
                priceValley = prices[i];
            }
            else
            {
                // buy, buy, buy
                buyPrice = priceValley;
                pricePeak = prices[i];
                bSellFlag = true;
            }
        }
        else
        {
            // looking to sell...
            if (prices[i]>pricePeak)
            {
                // still going up...
                pricePeak = prices[i];
            }
            else
            {
                // price stagnated or dropped, sell at previous
                profit += pricePeak - buyPrice;
                bSellFlag = false;
                priceValley = prices[i];
            }
        }
    }
    if (bSellFlag == true)
    {
        // end of array... just sell
        if (pricePeak > buyPrice)
        {
            // sell if we have a profit
            profit += pricePeak - buyPrice;
        }
    }
    return profit;
}

#include <stdio.h>

int maxProfit(int* prices, int pricesSize);

#define NUM_TESTS 4
#define MAX_NUM_VALUES 10
int testcase[NUM_TESTS][MAX_NUM_VALUES] = {
    {7,3,1,5,3,6,4},
    {1,2,3,4,5},
    {5,4,3,2,1},
    {1,2,1,2,1,2,1,2,1,2},
};

int testnum[NUM_TESTS] = {
    7,
    5,
    5,
    10,
};

int testanswers[NUM_TESTS] = {
    7, // 1/5=4, 3/6=3 == 7
    4, // 1/5=4 == 4
    0, // none
    5, // 1/2=1 * 5 == 5
};

int main(void)
{
    int status = 0;

    int profit;

    for (int i=0; i<NUM_TESTS; i++)
    {
        profit = maxProfit(testcase[i], testnum[i]);
        printf("Test #%d Profit: %d\n", i, profit);
        if (profit != testanswers[i])
        {
            status = -1;
        }
    }
    printf("All Test Cases passed!!\n");
    return status;
}