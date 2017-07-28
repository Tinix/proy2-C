#ifndef _PAIR_H
#define _PAIR_H

#include <stdbool.h>
#include "index.h"
#include "data.h"


typedef struct _pair_t *pair_t;

pair_t pair_from_index_data(index_t index, data_t data);
/*
 * Build a new pair from the given index and data using references to them.
 *
 * Do NOT free index and data after creating the pair, but only through
 * pair_destroy.
 *
 * PRE: 'index' and 'data' are not NULL.
 *
 * POST: the result is not NULL, and pair_fst(result) is equal to 'index',
 * and pair_snd(result) is equal to 'data'.
 */

pair_t pair_destroy(pair_t pair);
/*
 * Free the memory allocated by the given 'pair', as well as the respective
 * index and data. Set 'pair' to NULL.
 */

index_t pair_fst(pair_t pair);
/*
 * Return a reference to the first pair element.
 *
 * PRE: 'pair' is not NULL.
 *
 * POST: the result is not NULL, and should never be freed by the caller.
 */

data_t pair_snd(pair_t pair);
/*
 * Return a reference to the second pair element.
 *
 * PRE: 'pair' is not NULL.
 *
 * POST: the result is not NULL, and should never be freed by the caller.
 */

bool pair_is_equal(pair_t pair, pair_t other);
/*
 * Return whether 'pair' is equal to 'other'.
 *
 * PRE: 'pair' and 'other' are not NULL.
 */

pair_t pair_copy(pair_t pair);
/*
 * Return a cloned copy of the given pair.
 *
 * PRE: 'pair' is not NULL.
 *
 * POST: the result is not NULL, and pair_is_equal(result, pair holds.
 */

#endif
