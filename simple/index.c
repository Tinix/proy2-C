#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "index.h"

#define INDEX_MAX_LENGTH 40


struct _index_t {
    char content[INDEX_MAX_LENGTH + 1];
};

unsigned int index_max_length(void) {
    return (INDEX_MAX_LENGTH);
}

unsigned int index_length(index_t index) {
    assert(index != NULL);
    return (strlen(index->content));
}

bool index_is_equal(index_t index, index_t other) {
    assert(index != NULL);
    assert(other != NULL);
    return (strncmp(index->content, other->content, INDEX_MAX_LENGTH) == 0);
}

bool index_is_less_than(index_t index, index_t other) {
    assert(index != NULL);
    assert(other != NULL);
    return (strncmp(index->content, other->content, INDEX_MAX_LENGTH) < 0);
}

index_t index_from_string(char *s) {
    index_t result = NULL;

    assert(s != NULL);

    result = calloc(1, sizeof(struct _index_t));
    assert(result != NULL);

    strncpy(result->content, s, INDEX_MAX_LENGTH + 1);
    result->content[INDEX_MAX_LENGTH] = '\0';

    return (result);
}

char *index_to_string(index_t index) {
    char *result = NULL;

    assert(index != NULL);

    result = calloc(INDEX_MAX_LENGTH + 1, sizeof(char));
    assert(result != NULL);

    strncpy(result, index->content, INDEX_MAX_LENGTH + 1);

    return (result);
}

index_t index_copy(index_t index) {
    assert(index != NULL);
    return (index_from_string(index->content));
}

index_t index_destroy(index_t index) {
    free(index);
    index = NULL;
    return (index);
}
