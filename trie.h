/*
 ============================================================================
 Name        : trie.c trie.h
 Author      : Iain Hill
 Version     : 1
 Copyright   : GPL

 Description : trie data structure for C programming.

    Copyright (C) 2018 Iain Hill. 

 ============================================================================
 */
#ifndef trie_h
#define trie_h
typedef struct Trie {
	int c;
	struct Trie **next;
	int word_end;
} Trie;
#endif

/* Create a new trie list */
Trie **tTrie_init(Trie **listing);

/* Add a new word to the trie */
Trie **tTrie_add_word(Trie **list, char *string);

/* Add a n char of a string to the trie */
Trie **tTrie_add_n_char(Trie **list, int len, char *string);

/* Output trie via given function */
void tTrie_output(Trie **list, void (*func)(void*, void*, int), void *var);

/* Dispose of trie */
void tTrie_free(Trie **list);
