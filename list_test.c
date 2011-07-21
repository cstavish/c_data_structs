#include <stdio.h>
#include "cs_linked_list.h"

static void print_sll(cs_sll *list) {
	for (int i = 0; i < list->size; i++)
		puts(cs_sll_get(list, i));
}

static void print_dll(cs_dll *list) {
	for (int i = 0; i < list->size; i++)
		puts(cs_dll_get(list, i));
}

int main() {
	
	{
		cs_dll *list = cs_dll_create(NULL, "lorem", "ipsum", "dolor", "sit", "amet", NULL);
		
		puts("Starting contents:\n\n");
		print_dll(list);
			
		puts("\n\nSwapping 0 with 2\n\n");
		cs_dll_swap(list, 0, 2);
		print_dll(list);
	
		
		puts("\n\nInserting 'pseudo-Latin' at index 3\n\n");
		cs_dll_ins(list, "psuedo-Latin", 3);
		print_dll(list);
	
			
		puts("\n\nRemoving element at index 2\n\n");
		cs_dll_del(list, 2);
		print_dll(list);
	
		puts("\n\nSetting 2 to 'Cicero?'\n\n");
		cs_dll_set(list, "Cicero?", 2);
		print_dll(list);
			
		cs_dll_destroy(list);
	}
	{
		cs_sll *list = cs_sll_create(NULL, "lorem", "ipsum", "dolor", "sit", "amet", NULL);
		
		puts("\n\nStarting contents:\n\n");
		print_sll(list);
			
		puts("\n\nSwapping 0 with 2\n\n");
		cs_sll_swap(list, 0, 2);
		print_sll(list);
	
		
		puts("\n\nInserting 'pseudo-Latin' at index 3\n\n");
		cs_sll_ins(list, "psuedo-Latin", 3);
		print_sll(list);
	
			
		puts("\n\nRemoving element at index 2\n\n");
		cs_sll_del(list, 2);
		print_sll(list);
	
		puts("\n\nSetting 2 to 'Cicero?'\n\n");
		cs_sll_set(list, "Cicero?", 2);
		print_sll(list);
			
		cs_sll_destroy(list);
	}
	
	return 0;
}