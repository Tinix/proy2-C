#ifndef _INDEX_H
#define _INDEX_H

#include <stdbool.h>


typedef struct _index_t *index_t;

index_t index_from_string(char *source);
/*
 * Return a newly created index from the given string 'source'.
 *
 * The string 'source' is null-terminated, and this function will
 * make a copy of it to store locally, so is the caller's responsability
 * to free it.
 *
 * PRE: 'source' is not NULL.
 *
 * POST: the result is not NULL, and its string representation is equal to
 * 'source'.
 */

index_t index_destroy(index_t index);
/*
 * Free the resources used by the given 'index', and set it to NULL.
 */

unsigned int index_max_length(void);
/*
 * Return the maximum length for the string representation of any index.
 */

unsigned int index_length(index_t index);
/*
 * Return the length of the given 'index'.
 *
 * PRE: 'index' is not NULL.
 */

char *index_to_string(index_t index);
/*
 * Return the string representation of the given 'index'.
 *
 * The caller is responsible for the allocated reources for the result, thus
 * those should be freed when done using it.
 *
 * PRE: 'index' is not NULL.
 *
 * POST: the result is not NULL, and is a null-terminated string.
 */

bool index_is_equal(index_t index, index_t other);
/*
 * Return whether the given 'index' is equal to 'other'.
 *
 * PRE: 'index' and 'other' are not NULL.
 */

bool index_is_less_than(index_t index, index_t other);
/*
 * Return whether the given 'index' is less than 'other'
 * (alphabetically sorted).
 *
 * For example, index_from_string("aaaa") is less than index_from_string("b").
 *
 * PRE: 'index' and 'other' are not NULL.
 */

index_t index_copy(index_t index);
/*
 * Return a cloned copy of the given 'index'.
 *
 * PRE: 'index' is not NULL.
 *
 * POST: the result is not NULL, and index_is_equal(result, index) holds.
 */

#endif
