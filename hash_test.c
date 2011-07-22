#include <stdio.h>
#include <stdlib.h>
#include "cs_hash_tab.h"

static void clean_up(const char *key, void *val) {
	printf("cleaning up value for key \"%s\"\n", key);
	// nothing to clean up in this case (string constants)
}

static void for_each(const char *key, void *val) {
	printf("%s => %s\n", key, (const char *)val);
}	

int main() {
	cs_hash_tab *t = cs_hash_create_kv("Pink", "Floyd", "Jimi", "Hendrix", "Grateful", "Dead", "Titus", "Andronicus", NULL);
	t->cleanup = clean_up;
	cs_hash_set(t, "Steely", "Dan");
	cs_hash_del(t, "Titus");
	puts(cs_hash_get(t, "Pink"));
	puts(cs_hash_get(t, "Jimi"));
	puts(cs_hash_get(t, "Grateful"));
	puts(cs_hash_get(t, "Steely"));
	cs_hash_iterate(t, for_each);
	cs_hash_destroy(t);
}