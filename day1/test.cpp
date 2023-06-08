#include <cstring>
#include <stdio.h>
#include "munit.h"
#include "d1.h"

/* This is just to disable an MSVC warning about conditional
 * expressions being constant, which you shouldn't have to do for your
 * code.  It's only here because we want to be able to do silly things
 * like assert that 0 != 1 for our demo. */
#if defined(_MSC_VER)
#pragma warning(disable: 4127)
#endif

/* Tests are functions that return void, and take a single void*
 * parameter.  We'll get to what that parameter is later. */
static MunitResult
test_decimal_to_snafu(const MunitParameter params[], void* data) {

  /* These are just to silence compiler warnings about the parameters
   * being unused. */
  (void) params;
  (void) data;

  char output[255];
  decimal_to_snafu(1, output);
  printf("outpout is : %s\n", output);
  munit_assert_true(!strcmp(output, "1")); //strcmp returns 0 if equal, so negate it

  decimal_to_snafu(9, output);
  printf("outpout is : %s\n", output);
  munit_assert_true(!strcmp(output, "2-")); //strcmp returns 0 if equal, so negate it

  decimal_to_snafu(10, output);
  printf("outpout is : %s\n", output);
  munit_assert_true(!strcmp(output, "20")); //strcmp returns 0 if equal, so negate it

  decimal_to_snafu(11, output);
  printf("outpout is : %s\n", output);
  munit_assert_true(!strcmp(output, "21")); //strcmp returns 0 if equal, so negate it

  decimal_to_snafu(12, output);
  printf("outpout is : %s\n", output);
  munit_assert_true(!strcmp(output, "22")); //strcmp returns 0 if equal, so negate it

  decimal_to_snafu(13, output);
  printf("outpout is : %s\n", output);
  munit_assert_true(!strcmp(output, "1==")); //strcmp returns 0 if equal, so negate it

  return MUNIT_OK;
}

static MunitResult
test_lower_bound(const MunitParameter params[], void* data) {
  long long input = 61;
  bool result = is_lower_bound_available(3, input);
  munit_assert_true(result);

  input = 10;
  int power = max_power(input);
  munit_assert_true(power==2);
  result = is_lower_bound_available(power, input);
  munit_assert_true(result);

  return MUNIT_OK;
}

/* Creating a test suite is pretty simple.  First, you'll need an
 * array of tests: */
static MunitTest test_suite_tests[] = {
  {
    /* The name is just a unique human-readable way to identify the
     * test. You can use it to run a specific test if you want, but
     * usually it's mostly decorative. */
    (char*) "decimal to snafu",
    /* You probably won't be surprised to learn that the tests are
     * functions. */
    test_decimal_to_snafu,
    /* If you want, you can supply a function to set up a fixture.  If
     * you supply NULL, the user_data parameter from munit_suite_main
     * will be used directly.  If, however, you provide a callback
     * here the user_data parameter will be passed to this callback,
     * and the return value from this callback will be passed to the
     * test function.
     *
     * For our example we don't really need a fixture, but lets
     * provide one anyways. */
    NULL,
    /* If you passed a callback for the fixture setup function, you
     * may want to pass a corresponding callback here to reverse the
     * operation. */
    NULL,
    /* Finally, there is a bitmask for options you can pass here.  You
     * can provide either MUNIT_TEST_OPTION_NONE or 0 here to use the
     * defaults. */
    MUNIT_TEST_OPTION_NONE,
    NULL
  },
  { (char*) "get_lower_bound", test_lower_bound, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

/* Now we'll actually declare the test suite.  You could do this in
 * the main function, or on the heap, or whatever you want. */
static const MunitSuite test_suite = {
  /* This string will be prepended to all test names in this suite;
   * for example, "/example/rand" will become "/µnit/example/rand".
   * Note that, while it doesn't really matter for the top-level
   * suite, NULL signal the end of an array of tests; you should use
   * an empty string ("") instead. */
  (char*) "",
  /* The first parameter is the array of test suites. */
  test_suite_tests,
  /* In addition to containing test cases, suites can contain other
   * test suites.  This isn't necessary in this example, but it can be
   * a great help to projects with lots of tests by making it easier
   * to spread the tests across many files.  This is where you would
   * put "other_suites" (which is commented out above). */
  NULL,
  /* An interesting feature of µnit is that it supports automatically
   * running multiple iterations of the tests.  This is usually only
   * interesting if you make use of the PRNG to randomize your tests
   * cases a bit, or if you are doing performance testing and want to
   * average multiple runs.  0 is an alias for 1. */
  1,
  /* Just like MUNIT_TEST_OPTION_NONE, you can provide
   * MUNIT_SUITE_OPTION_NONE or 0 to use the default settings. */
  MUNIT_SUITE_OPTION_NONE
};

/* This is only necessary for EXIT_SUCCESS and EXIT_FAILURE, which you
 * *should* be using but probably aren't (no, zero and non-zero don't
 * always mean success and failure).  I guess my point is that nothing
 * about µnit requires it. */
#include <stdlib.h>

int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  /* Finally, we'll actually run our test suite!  That second argument
   * is the user_data parameter which will be passed either to the
   * test or (if provided) the fixture setup function. */
  return munit_suite_main(&test_suite, (void*) "µnit", argc, argv);
}
