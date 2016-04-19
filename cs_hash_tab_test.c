#include <CUnit/Basic.h>
#include <math.h>
#include "cs_hash_tab.h"

/**
 *  Test that the default create function dynamically allocates
 *    the cs_hash_tab struct, properly initializes
 *    8 buckets, and sets the min_load and max_load to
 *    .25 and .75 respectively
 *
 */

static void test_create_default(void) {

	cs_hash_tab *t = NULL;
	t = cs_hash_create();

	CU_ASSERT(t != NULL);
	CU_ASSERT(t->size == 8);
	CU_ASSERT(fabs(t->min_load - 0.25) < 1e-6);
	CU_ASSERT(fabs(t->max_load - 0.75) < 1e-6);

	cs_hash_destroy(t);
}

/**
 *  Test that the create function dynamically allocates
 *    the cs_hash_tab struct, and sets the specified options
 *
 */

static void test_create_opt(void) {

	cs_hash_tab *t = NULL;
	t = cs_hash_create_opt(128, 0.6, 0.2);

	CU_ASSERT(t != NULL);
	CU_ASSERT(t->size == 128);
	CU_ASSERT(fabs(t->min_load - 0.2) < 1e-6);
	CU_ASSERT(fabs(t->max_load - 0.6) < 1e-6);

	cs_hash_destroy(t);
}

/**
 *  Test that the create function dynamically allocates
 *    the cs_hash_tab struct, and initializes it with
 *    the specified key - value pairs
 */

static void test_create_kv(void) {

	cs_hash_tab *t = NULL;
	t = cs_hash_create_kv("Professor Name", "Laboon", "Student Name", "Stavish", NULL);

	CU_ASSERT(t != NULL);
	CU_ASSERT_STRING_EQUAL(cs_hash_get(t, "Professor Name"), "Laboon");
	CU_ASSERT_STRING_EQUAL(cs_hash_get(t, "Student Name"), "Stavish");

	cs_hash_destroy(t);
}

/**
 *  Test that the set function associates the speficied key
 *    with the specified value, when that key has not been used
 *    previously
 *
 *  Note: this also effectively tests cs_hash_get()
 */

static void test_set_new_key(void) {

	cs_hash_tab *t = NULL;
	t = cs_hash_create();

	cs_hash_set(t, "key", "value");

	CU_ASSERT_STRING_EQUAL(cs_hash_get(t, "key"), "value");

	cs_hash_destroy(t);
}

/**
 *  Test that the set function associates the speficied key
 *    with the specified value, when that key HAS been used
 *    previously
 */

static void test_set_old_key(void) {

	cs_hash_tab *t = NULL;
	t = cs_hash_create();

	cs_hash_set(t, "key", "value");
	cs_hash_set(t, "key", "new value");

	CU_ASSERT_STRING_EQUAL(cs_hash_get(t, "key"), "new value");

	cs_hash_destroy(t);
}

/**
 *  Test that the set function associates the speficied key
 *    with the specified value, when that key is very long
 *
 */

static void test_set_long_key(void) {

	cs_hash_tab *t = NULL;
	t = cs_hash_create();

	const char *key = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
					  "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
					  "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
					  "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
					  "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
					  "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
					  "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
					  "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
					  "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
					  "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
					  "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
					  "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
					  "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
					  "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
					  "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
					  "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";

	cs_hash_set(t, key, "value");

	CU_ASSERT_STRING_EQUAL(cs_hash_get(t, key), "value");

	cs_hash_destroy(t);
}

/**
 *  Test that the get function returns NULL when the specified
 *    key has not previously been associated with a value
 *
 */

static void test_get_undefined_key(void) {

	cs_hash_tab *t = NULL;
	t = cs_hash_create();

	CU_ASSERT(cs_hash_get(t, "key") == NULL);

	cs_hash_destroy(t);
}

/**
 *  Test that the delete function properly disassociates
 *    the specified key with its value
 *
 */

static void test_del(void) {

	cs_hash_tab *t = NULL;
	t = cs_hash_create();

	cs_hash_set(t, "key", "value");
	cs_hash_del(t, "key");

	CU_ASSERT(cs_hash_get(t, "key") == NULL);

	cs_hash_destroy(t);
}

/**
 *  Test that the iterate function calls the specified function
 *    for each key,value pair stored in the table
 */

static int counter = 0;

static void iterator(cs_hash_tab *t, const char *k, void *v, size_t count) {

	counter = count + 1;
}

static void test_iterate(void) {

	cs_hash_tab *t = NULL;
	t = cs_hash_create();

	cs_hash_set(t, "k1", "v1");
	cs_hash_set(t, "k2", "v2");
	cs_hash_set(t, "k3", "v3");
	cs_hash_set(t, "k4", "v4");
	cs_hash_set(t, "k5", "v5");
	cs_hash_set(t, "k6", "v6");
	cs_hash_set(t, "k7", "v7");
	cs_hash_set(t, "k8", "v8");

	cs_hash_iterate(t, iterator);

	CU_ASSERT(counter == 8);

	cs_hash_destroy(t);
}

/**
 *  Test that the table dynamically grows itself when it exceeds its max_load
 */

static void test_dynamic_growth(void) {

	cs_hash_tab *t = NULL;

	/**
	 *  With these parameters, the table should grow when more than
	 *    6 key,value pairs are stored
	 */
	t = cs_hash_create_opt(8, 0.75, 0.25);

	cs_hash_set(t, "k1", "v1");
	cs_hash_set(t, "k2", "v2");
	cs_hash_set(t, "k3", "v3");
	cs_hash_set(t, "k4", "v4");
	cs_hash_set(t, "k5", "v5");
	cs_hash_set(t, "k6", "v6");
	cs_hash_set(t, "k7", "v7");

	CU_ASSERT(t->size > 8);

	cs_hash_destroy(t);

 }

/**
 *  Test that the table dynamically shrinks itself when it 
 *	  dips below its min_load
 */

static void test_dynamic_shrinkage(void) {

	cs_hash_tab *t = NULL;
	size_t larger_size;

	/**
	 *  With these parameters, the table should grow when more than
	 *    6 key,value pairs are stored
	 */
	t = cs_hash_create_opt(8, 0.75, 0.25);

	cs_hash_set(t, "k1", "v1");
	cs_hash_set(t, "k2", "v2");
	cs_hash_set(t, "k3", "v3");
	cs_hash_set(t, "k4", "v4");
	cs_hash_set(t, "k5", "v5");
	cs_hash_set(t, "k6", "v6");
	cs_hash_set(t, "k7", "v7");

	larger_size = t->size;

	CU_ASSERT(larger_size > 8);

	cs_hash_del(t, "k1");
	cs_hash_del(t, "k2");
	cs_hash_del(t, "k3");
	cs_hash_del(t, "k4");
	cs_hash_del(t, "k5");
	cs_hash_del(t, "k6");

	CU_ASSERT(t->size < larger_size);

	cs_hash_destroy(t);

 }

int main(int argc, const char **argv) {

	CU_pSuite suite = NULL;

	/* init the CUnit test registry */
	if (CU_initialize_registry() != CUE_SUCCESS) {
		return CU_get_error();
	}

	/* add a suite to the registry */
	suite = CU_add_suite("S1", NULL, NULL);
	if (suite == NULL) {
	   CU_cleanup_registry();
	   return CU_get_error();
	}

	/* add the tests to the suite */
	CU_add_test(suite, "test of cs_hash_create()", test_create_default);
	CU_add_test(suite, "test of cs_hash_create_opt()", test_create_opt);
	CU_add_test(suite, "test of cs_hash_create_kv()", test_create_kv);
	CU_add_test(suite, "test of cs_hash_set() w/ new key", test_set_new_key);
	CU_add_test(suite, "test of cs_hash_set() w/ old key", test_set_old_key);
	CU_add_test(suite, "test of cs_hash_set() w/ long key", test_set_long_key);
	CU_add_test(suite, "test of cs_hash_get() w/ undefined key", test_get_undefined_key);
	CU_add_test(suite, "test of cs_hash_del()", test_del);
	CU_add_test(suite, "test of cs_hash_iterate()", test_iterate);
	CU_add_test(suite, "test of dynamic table growth", test_dynamic_growth);
	CU_add_test(suite, "test of dynamic table shrinkages", test_dynamic_shrinkage);


	/* Run all tests using the basic interface */
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();

}