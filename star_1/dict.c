#include <assert.h>
#include <stdlib.h>

#include "dict.h"
#include "list.h"


struct _dict_t {
    list_t list;
    unsigned int length;
};

dict_t dict_empty(void) {
    dict_t result = NULL;

    result = calloc(1, sizeof(struct _dict_t));
    assert(result != NULL);
    result->list = list_empty();
    result->length = 0;

    /* POST */
    assert(dict_length(result) == 0);

    return (result);
}

dict_t dict_destroy(dict_t dict) {
    if (dict != NULL) {
        dict->list = list_destroy(dict->list);
        dict->length = 0;
        free(dict);
        dict = NULL;
    }

    return (dict);
}

unsigned int dict_length(dict_t dict) {
    /* PRE */
    assert(dict != NULL);

    return (dict->length);
}

bool dict_is_equal(dict_t dict, dict_t other) {
    /* PRE */
    assert(dict != NULL && other != NULL);

    bool result = false;

    result = list_is_equal(dict->list, other->list) &&
        dict->length == other->length;

    return (result);
}

bool dict_exists(dict_t dict, word_t word) {
    /* PRE */
    assert(dict != NULL && word != NULL);

    bool result = false;
    index_t index = NULL;

    index = index_from_string(word);
    result = list_search(dict->list, index) != NULL;
    free(index);

    return (result);
}

def_t dict_search(dict_t dict, word_t word) {
    /* PRE */
    assert(dict != NULL && word != NULL && dict_exists(dict, word));

    def_t result = NULL;
    index_t index = NULL;

    index = index_from_string(word);
    result = data_to_string(list_search(dict->list, index));
    free(index);

    /* POST */
    assert(result != NULL);

    return (result);
}

dict_t dict_add(dict_t dict, word_t word, def_t def) {
    /* PRE */
    assert(dict != NULL && word != NULL && def != NULL &&
           !dict_exists(dict, word));

    index_t index = NULL;
    data_t data = NULL;

    index = index_from_string(word);
    data = data_from_string(def);
    dict->list = list_add(dict->list, index, data);
    dict->length += 1;

    return (dict);
}

dict_t dict_remove(dict_t dict, word_t word) {
    /* PRE */
    assert(dict != NULL && word != NULL && dict_exists(dict, word));

    index_t index = NULL;

    index = index_from_string(word);
    dict->list = list_remove(dict->list, index);
    dict->length -= 1;
    free(index);

    return (dict);
}

dict_t dict_copy(dict_t dict) {
    dict_t result = NULL;

    result = calloc(1, sizeof(struct _dict_t));
    assert(result != NULL);
    result->list = list_copy(dict->list);
    result->length = dict->length;

    /* POST */
    assert(result != NULL && dict_is_equal(result, dict));

    return (result);
}

void dict_dump(dict_t dict, FILE * fd) {
    /* PRE */
    assert(dict != NULL && fd != NULL);
    list_dump(dict->list, fd);
}
