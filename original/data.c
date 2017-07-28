#include <assert.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "data.h"

#define DATA_MAX_LENGTH (INT_MAX - 1)


struct _data_t {
    char *content;
    unsigned int length;
};

unsigned int data_max_length(void) {
    return (DATA_MAX_LENGTH);
}

unsigned int data_length(data_t data) {
    assert(data != NULL);
    return (data->length);
}

data_t data_from_string(char *s) {
    data_t result = NULL;

    assert(s != NULL);

    result = calloc(1, sizeof(struct _data_t));
    assert(result != NULL);

    result->length = strlen(s);
    result->content = calloc(result->length + 1, sizeof(char));
    assert(result->content != NULL);

    strncpy(result->content, s, result->length + 1);
    result->content[result->length] = '\0';

    return (result);
}

data_t data_destroy(data_t data) {
    if (data != NULL) {
        free(data->content);
    }
    free(data);
    data = NULL;
    return (data);
}

char *data_to_string(data_t data) {
    char *result = NULL;

    assert(data != NULL);

    result = calloc(data->length + 1, sizeof(char));
    assert(result != NULL);

    strncpy(result, data->content, data->length + 1);

    return (result);
}

bool data_is_equal(data_t data, data_t other) {
    return (strncmp(data->content, other->content, DATA_MAX_LENGTH) == 0);
}

data_t data_copy(data_t data) {
    data_t result = NULL;

    assert(data != NULL);

    result = data_from_string(data->content);

    assert(data_is_equal(data, result));
    return (result);
}
