#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#include "data.h"
#include "index.h"
#include "pair.h"


struct _pair_t {
    index_t index;
    data_t data;
};

pair_t pair_from_index_data(index_t index, data_t data) {
    /* PRE */
    assert(index != NULL && data != NULL);

    pair_t result = NULL;

    result = calloc(1, sizeof(struct _pair_t));
    assert(result != NULL);
    result->index = index;
    result->data = data;

    /* POST */
    assert(result != NULL && index_is_equal(pair_fst(result), index) &&
           data_is_equal(pair_snd(result), data));

    return (result);
}

pair_t pair_destroy(pair_t pair) {
    if (pair != NULL) {
        pair->index = index_destroy(pair->index);
        pair->data = data_destroy(pair->data);
        free(pair);
        pair = NULL;
    }

    return (pair);
}

index_t pair_fst(pair_t pair) {
    /* PRE */
    assert(pair != NULL);

    /* POST */
    assert(pair->index != NULL);

    return (pair->index);
}

data_t pair_snd(pair_t pair) {
    /* PRE */
    assert(pair != NULL);

    /* POST */
    assert(pair->data != NULL);

    return (pair->data);
}

bool pair_is_equal(pair_t pair, pair_t other) {
    /* PRE */
    assert(pair != NULL && other != NULL);

    bool result = false;

    result = index_is_equal(pair->index, other->index) &&
        data_is_equal(pair->data, other->data);

    return (result);
}

pair_t pair_copy(pair_t pair) {
    /* PRE */
    assert(pair != NULL);

    pair_t result = NULL;

    result = calloc(1, sizeof(struct _pair_t));
    assert(result != NULL);
    result->index = index_copy(pair->index);
    result->data = data_copy(pair->data);

    /* POST */
    assert(result != NULL && pair_is_equal(result, pair));

    return (result);
}
