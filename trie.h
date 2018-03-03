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
#ifndef _trie_h
#define _trie_h
typedef struct Trie {
	int c;
	struct Trie **next;
	int word_end;
} Trie;
#endif

/* Create a new trie list */
Trie **tTrie_init(Trie **listing);

/* Add a new word to the trie */
Trie **tTrie_add_word(Trie **list, char* str);

/* Print trie list to terminal */
void tTrie_print(Trie **list);

/* Dispose of trie */
void tTrie_free(Trie **list);
