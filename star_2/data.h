#ifndef _DATA_H
#define _DATA_H

#include <stdbool.h>


typedef struct _data_t *data_t;

data_t data_from_string(char *source);
/*
 * Return a newly created data from the given string 'source'.
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

data_t data_destroy(data_t data);
/*
 * Free the resources used by the given 'data', and set it to NULL.
 */

unsigned int data_max_length(void);
/*
 * Return the maximum length for the string representation of any data.
 */

unsigned int data_length(data_t data);
/*
 * Return the length of the given 'data'.
 *
 * PRE: 'data' is not NULL.
 */

char *data_to_string(data_t data);
/*
 * Return the string representation of the given 'data'.
 *
 * The caller is responsible for the allocated reources for the result, thus
 * those should be freed when done using it.
 *
 * PRE: 'data' is not NULL.
 *
 * POST: the result is not NULL, and is a null-terminated string.
 */

bool data_is_equal(data_t data, data_t other);
/*
 * Return whether 'data' is equal to 'other'.
 *
 * PRE: 'data' and 'other' are not NULL.
 */

data_t data_copy(data_t data);
/*
 * Return a cloned copy of the given 'data'.
 *
 * PRE: 'data' is not NULL.
 *
 * POST: the result is not NULL, and data_is_equal(result, data) holds.
 */

#endif
