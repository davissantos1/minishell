#include "setup.h"
#include <unistd.h>

int	main(void)
{
	ft_putstr_fd("I'm a fucking initial setup\n\n", 1);
	sleep(1);
	ft_putstr_fd("I have a simple Makefile with some color and a degug rule that adds -g to the compilation\n\n", 1);
	sleep(1);
	ft_putstr_fd("I also have libft from 42 with some extra cool functions and a GC\n\n", 1);
	sleep(1);
	ft_putstr_fd("I don't only exist to suffer, I'll explain the GC, mate: \n\n", 1);
	sleep(3);
	ft_putstr_fd("Currently, we have 15 functions that do the following: \n\n", 1);
	ft_putstr_fd("1- gc_init: I start the damn thing \n\n", 1);
	sleep(1);
	ft_putstr_fd("2- gc_malloc: I allocate memory, put it into the gc you gave me in the tag you provided \n\n", 1);
	sleep(1);
	ft_putstr_fd("3- gc_calloc: I allocate memory, clean it and put it into the gc you gave me in the tag you provided \n\n", 1);
	sleep(1);
	ft_putstr_fd("4- gc_addptr: I register a pointer into the gc you gave me in the tag you provided \n\n", 1);
	sleep(1);
	ft_putstr_fd("5- gc_addmtx: I register a matrix into the gc you gave me in the tag you provided \n\n", 1);
	sleep(1);
	ft_putstr_fd("6- gc_addlst: I register a list into the gc you gave me in the tag you provided \n\n", 1);
	sleep(1);
	ft_putstr_fd("7- gc_addbtree: I register a btree into the gc you gave me in the tag you provided \n\n", 1);
	sleep(1);
	ft_putstr_fd("8- gc_free_tag: I free everything into the gc you gave me in the tag you provided \n\n", 1);
	sleep(1);
	ft_putstr_fd("9- gc_free_tag: I free everything into the gc you gave me\n\n", 1);
	sleep(1);
	ft_putstr_fd("Observation 1: there are other functions, but you'll mostly not use them at all (internal GC shit and removing the pointer that was added to the GC) \n\n", 1);
	sleep(2);
	ft_putstr_fd("Observation 2: You should respect the signature of my GC functions, otherwise you get undefined behavior\n\n", 1);
	sleep(2);
	ft_putstr_fd("Observation 4: overall you must NOT send null to my functions, no NULL GC, no NULL ptrs, with the exception of free like functions\n\n", 1);
	sleep(2);
	ft_putstr_fd("Finally, I encourage you to check out the gc_example.c for an overall feel of how the gc works, good coding\n\n", 1);
	
	return (0);
}
	
