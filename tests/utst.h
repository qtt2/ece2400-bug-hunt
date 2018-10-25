#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#define UTST_BEGIN() \
  printf("------- Testing %s -------\n\n", __FILE__);

#define UTST_END() \
  printf("\n------- Finished testing %s -------\n", __FILE__);

#define UTST_TEST_LABEL( x ) \
  printf("\n>>> %s\n\n", (x));

#define UTST_ASSERT_TRUE( x ) \
  { \
    int x_value = (int) (x); \
    if ( !x_value ) { \
      printf("\tLine %d: [ \033[31m FAILED \033[0m ]\n", __LINE__); \
      return 1; \
    } else { \
      printf("\tLine %d: [ \033[32m passed \033[0m ]\n", __LINE__); \
    } \
  }

#define UTST_ASSERT_FALSE( x ) \
  { \
    int x_value = (int) (x); \
    if ( x_value ) { \
      printf("\tLine %d: [ \033[31m FAILED \033[0m ]\n", __LINE__); \
      return 1; \
    } else { \
      printf("\tLine %d: [ \033[32m passed \033[0m ]\n", __LINE__); \
    } \
  }

#define UTST_ASSERT_INT_EQ( x, y ) \
  { \
    int x_value = (int) (x); \
    int y_value = (int) (y); \
    if ( x_value != y_value ) { \
      printf("\tLine %d: [ \033[31m FAILED \033[0m ] %d != %d\n", __LINE__, x_value, y_value); \
      return 1; \
    } else { \
      printf("\tLine %d: [ \033[32m passed \033[0m ] %d == %d\n", __LINE__, x_value, y_value); \
    } \
  }

#define UTST_ASSERT_FLOAT_EQ( x, y, eps ) \
  { \
    float x_value = (float) (x); \
    float y_value = (float) (y); \
    float eps_value = (float) (eps); \
    if ( fabs( x_value - y_value ) > eps_value ) { \
      printf("\tLine %d: [ \033[31m FAILED \033[0m ] %f != %f\n", __LINE__, x_value, y_value); \
      return 1; \
    } else { \
      printf("\tLine %d: [ \033[32m passed \033[0m ] %f == %f\n", __LINE__, x_value, y_value); \
    } \
  }

#endif
