/*
 * Main test function for Template
 *
 */

/*
 * Headers
 */
#include <stdint.h>
#include <stdio.h>
#include "template.h"
#include "CuTest.h"

#define MAGIC_NUMBER    42

void testTemplate(CuTest* tc)
{
    int a;
    int *pa;

    // simple tests
    pa = &a;
    a = MAGIC_NUMBER;

    CuAssertIntEquals(tc, a, MAGIC_NUMBER);
    CuAssertPtrNotNull(tc, pa);
    CuAssertIntEquals_Msg(tc, "Dereferenced pointer value incorrect!", *pa, MAGIC_NUMBER);
}

CuSuite* CuGetSuite(void)
{
    CuSuite* suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, testTemplate);

    return suite;
}
