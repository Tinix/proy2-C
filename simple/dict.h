#ifndef _DICT_H
#define _DICT_H

#include <stdio.h>
#include <stdbool.h>


typedef char *word_t;
typedef char *def_t;
typedef struct _dict_t *dict_t;

dict_t dict_empty(void);
/*
 * Return a newly created, empty dictionary.
 *
 * The caller must call dict_destroy when done using the resulting dict,
 * so the resources allocated by this call are freed.
 *
 * POST: the result is not NULL, and dict_length(result) is 0.
 */

dict_t dict_destroy(dict_t dict);
/*
 * Free the resources allocated for the given 'dict', and set it to NULL.
 */

unsigned int dict_length(dict_t dict);
/*
 * Return the amount of elements in the given 'dict'.
 * Constant order complexity.
 *
 * PRE: 'dict' is not NULL.
 */

bool dict_is_equal(dict_t dict, dict_t other);
/*
 * Return whether 'dict' is equal to 'other'.
 *
 * PRE: 'dict' and 'other' are not NULL.
 */

bool dict_exists(dict_t dict, word_t word);
/*
 * Return if the given 'word' exists in the dictionary 'dict'.
 *
 * PRE: 'dict' and 'word' are not NULL.
 */

def_t dict_search(dict_t dict, word_t word);
/*
 * Return the definition associated with 'word'.
 *
 * The caller must free the resources allocated for the result when done
 * using it.
 *
 * PRE: 'dict' and 'word' are not NULL, and 'word' does exist in 'dict'.
 *
 * POST: the result is not NULL.
 */

dict_t dict_add(dict_t dict, word_t word, def_t def);
/*
 * Return the given 'dict' with the given ('word', 'def') added.
 *
 * PRE: all 'dict', 'word' and 'def' are not NULL, and 'word' does not
 * exist in the given 'dict'.
 *
 * POST: the elements of the result are the same as the one in 'dict' with
 * the new pair ('word', 'def') added.
 */

dict_t dict_remove(dict_t dict, word_t word);
/*
 * Return the given 'dict' with the given 'word' removed.
 *
 * PRE: 'dict' and 'word' are not NULL, and the definition for 'word' does
 * exists in the dictionary.
 *
 * POST: the elements of the result are the same as the one in 'dict' with
 * the entry for 'word' removed.
 */

dict_t dict_copy(dict_t dict);
/*
 * Return a newly created copy of the given 'dict'.
 *
 * The caller must call dict_destroy when done using the resulting dict,
 * so the resources allocated by this call are freed.
 *
 * POST: the result is not NULL and it is an exact copy of 'dict'.
 * In particular, dict_is_equal(result, dict) holds.
 */

void dict_dump(dict_t dict, FILE * fd);
/*
 * Dump the given 'dict' in the given file descriptor 'fd'.
 *
 * PRE: 'dict' is not NULL, and 'fd' is a valid file descriptor.
 */

#endif
