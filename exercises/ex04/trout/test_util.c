#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "util.h"
#include "minunit.h"

int tests_run = 0;

static char * test1()
{
	char *resp = icmpcode_v4(1);
	char *message = "test1 failed: icmpcode_v4(1) should return \"host unreachable\"";
	mu_assert(message, resp == "host unreachable");
	return NULL;	
}

static char * all_tests()
{
	mu_run_test(test1);
	return NULL;
}

int main(int argc, char argv[])
{
	char *result = all_tests();
	if (result != NULL) {
		printf("%s", result);
	} else {
		printf("ALL TESTS PASSED");
	}
	printf("Tests run: %d", tests_run);
	return result != 0;
}
