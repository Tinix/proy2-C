#include <assert.h>
#include <stdlib.h>

#include "list.h"
#include "pair.h"


struct _node_t {
    pair_t elem;
    list_t next;
};

list_t list_empty(void) {
    list_t result = NULL;

    /* POST */
    assert(list_length(result) == 0);

    return (result);
}

list_t list_destroy(list_t list) {
    list_t node = NULL;

    while (list != NULL) {
        node = list;
        node->elem = pair_destroy(node->elem);
        list = list->next;
        free(node);
    }

    return (list);
}

unsigned int list_length(list_t list) {
    unsigned int result = 0;

    while (list != NULL) {
        result += 1;
        list = list->next;
    }

    return (result);
}

bool list_is_equal(list_t list, list_t other) {
    bool result = false;

    result = true;
    while (result && list != NULL && other != NULL) {
        result = pair_is_equal(list->elem, other->elem);
        list = list->next;
        other = other->next;
    }
    if (result) {
        result = list == NULL && other == NULL;
    }

    return (result);
}

data_t list_search(list_t list, index_t index) {
    /* PRE */
    assert(index != NULL);

    data_t result = NULL;

    while (list != NULL) {
        if (index_is_equal(index, pair_fst(list->elem))) {
            result = pair_snd(list->elem);
            list = NULL;
        } else {
            list = list->next;
        }
    }

    return (result);
}

list_t list_append(list_t list, index_t index, data_t data) {
    /* PRE */
    assert(index != NULL && data != NULL);

    list_t node = NULL, aux = NULL;

    node = calloc(1, sizeof(struct _node_t));
    assert(node != NULL);
    node->elem = pair_from_index_data(index, data);
    node->next = NULL;
    if (list == NULL) {
        list = node;
    } else {
        aux = list;
        while (aux->next != NULL) {
            aux = aux->next;
        }
        aux->next = node;
    }

    return (list);
}

list_t list_remove(list_t list, index_t index) {
    /*PRE */
    assert(index != NULL);

    list_t node = NULL, prev = NULL;

    node = list;
    while (node != NULL && !index_is_equal(pair_fst(node->elem), index)) {
        prev = node;
        node = node->next;
    }
    if (node != NULL) {
        if (prev == NULL) {
            list = node->next;
        } else {
            prev->next = node->next;
            prev = NULL;
        }
        node->elem = pair_destroy(node->elem);
        free(node);
        node = NULL;
    }

    return (list);
}

list_t list_copy(list_t list) {
    list_t result = NULL, aux = NULL, node = NULL, prev = NULL;

    aux = list;
    while (aux != NULL) {
        node = calloc(1, sizeof(struct _node_t));
        assert(node != NULL);
        node->elem = pair_copy(aux->elem);
        node->next = NULL;
        if (prev == NULL) {
            result = node;
        } else {
            prev->next = node;
        }
        prev = node;
        node = NULL;
        aux = aux->next;
    }

    /* POST */
    assert(list_is_equal(result, list));

    return (result);
}

void list_dump(list_t list, FILE * fd) {
    /* PRE */
    assert(fd != NULL);

    char *word = NULL, *def = NULL;

    if (list == NULL) {
        fprintf(fd, "\n");
    }
    while (list != NULL) {
        word = index_to_string(pair_fst(list->elem));
        def = data_to_string(pair_snd(list->elem));
        fprintf(fd, "%s: %s\n", word, def);
        free(word);
        free(def);
        list = list->next;
    }
}
