#include "trie.h"
#include "board.h"
#include <stdio.h>
#include <stdlib.h>

#define UCHAR 127 /* Length of character index for c_list */

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  Create and fill
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

Trie *new_c_node(char c)
{
	Trie *new_node = malloc(sizeof(Trie));
	if ((new_node) == NULL)
		return NULL;
	new_node->c = c;
	new_node->next = NULL;
	new_node->word_end = 0;

	return new_node;
}

Trie **new_c_list(Trie **list)
{
	int i;
	if ((list = malloc(UCHAR * sizeof(Trie*))) == NULL)
		return NULL;

	for (i = 0; i < UCHAR; i++)
		list[i] = NULL;

	return list;
}

Trie *add_word(Trie *word, char *str)
{
	Trie *ptr, *c_node = word;
	ptr = c_node;

	while (*++str) {

		/* Next node list */
		if (c_node->next == NULL)
			if ((c_node->next = new_c_list(c_node->next)) == NULL)
				return NULL;
		/* Next node */
		if (c_node->next[(int)*str] == NULL)
			if ((c_node->next[(int)*str] = new_c_node(*str)) == NULL)
				return NULL;

		c_node = c_node->next[(int)*str];
	}

	c_node->word_end = 1;

	return ptr;
}

Trie **tTrie_add_word(Trie **list, char *string)
{
	char* str = (char*)string;

	if (list[(int)*str] == NULL)
		if ((list[(int)*str] = new_c_node(*str)) == NULL)
			return NULL;

	if ((add_word(list[(int)*str], str)) == NULL)
		return NULL;

	return list;
}

Trie **tTrie_add_n_char(Trie **list, int len, char *string)
{
	char str[len+1];
	snprintf(str, len+1, string);

	if (list[(int)*str] == NULL)
		if ((list[(int)*str] = new_c_node(*str)) == NULL)
			return NULL;

	if ((add_word(list[(int)*str], str)) == NULL)
		return NULL;

	return list;
}

Trie **tTrie_init(Trie **list)
{
	return new_c_list(list);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  Output
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void output_word(Trie *word, char *out, char *pt_out, void (*func)(void*, void*, int), void *var)
{
	int i;
	static int count;
	pt_out += sprintf(pt_out, "%c", word->c);

	if (word->next != NULL)
		for (i = 0; i < UCHAR; i++)
			if (word->next[i] != NULL)
				output_word(word->next[i], out, pt_out, func, var);

	if (word->word_end)
		(*func)((void*)out, var, ++count);
}

void output_list(Trie **list, char *out, char *pt_out, void (*func)(void*, void*, int), void *var)
{
	int i;
	for (i = 0; i < UCHAR; i++)
		if (list[i] != NULL)
			output_word(list[i], out, pt_out, func, var);
}

/* Output trie via given function */
void tTrie_output(Trie **list, void (*func)(void*, void*, int), void *var)
{
	char *pt, out[UCHAR] = {'\0'};
	pt = out;

	output_list(list, pt, pt, func, var);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  Disposal
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void trie_free_word(Trie *word)
{
	int i;

	if (word->next != NULL) {
		for (i = 0; i < UCHAR; i++)
			if (word->next[i] != NULL)
				trie_free_word(word->next[i]);
		free(word->next);
	}
	free(word);
}

void tTrie_free(Trie **list)
{
	int i;
	for (i = 0; i < UCHAR; i++)
		if (list[i] != NULL)
			trie_free_word(list[i]);
	free(list);
}

