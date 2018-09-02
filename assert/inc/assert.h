/*
 * Simple Assert Library
 */

#ifndef __ASSERT_H__
#define __ASSERT_H__

#include <stdlib.h> // for exit

#if defined(EMBEDDED)
 #define ASSERT(x) {if(!(x)) {printf("ASSERT!!!\n"); while(1);}}
#else
 #define ASSERT(x) {if(!(x)) {fprintf(stderr, "ASSERT!!! %s:%d in %s\n", __FILE__, __LINE__, __FUNCTION__); exit(-1);}}
#endif

#endif // __ASSERT_H__