#include <assert.h>
#include <stdlib.h>

#include "list.h"
#include "pair.h"


typedef struct _node_t *node_t;

struct _node_t {
    pair_t elem;
    node_t next;
};

struct _list_t {
    node_t fst;
    node_t lst;
};

list_t list_empty(void) {
    list_t result = NULL;

    result = calloc(1, sizeof(struct _list_t));
    assert(result != NULL);
    result->fst = NULL;
    result->lst = NULL;

    /* POST */
    assert(list_length(result) == 0);

    return (result);
}

list_t list_destroy(list_t list) {
    node_t node = NULL;

    if (list != NULL) {
        while (list->fst != NULL) {
            node = list->fst;
            node->elem = pair_destroy(node->elem);
            list->fst = list->fst->next;
            free(node);
        }
        free(list);
        list = NULL;
    }

    return (list);
}

unsigned int list_length(list_t list) {
    /* PRE */
    assert(list != NULL);

    unsigned int result = 0;
    node_t aux = NULL;

    aux = list->fst;
    while (aux != NULL) {
        result += 1;
        aux = aux->next;
    }

    return (result);
}

bool list_is_equal(list_t list, list_t other) {
    /* PRE */
    assert(list != NULL && other != NULL);

    bool result = false;
    node_t list_n = NULL, other_n = NULL;

    result = true;
    list_n = list->fst;
    other_n = other->fst;
    while (result && list_n != NULL && other_n != NULL) {
        result = pair_is_equal(list_n->elem, other_n->elem);
        list_n = list_n->next;
        other_n = other_n->next;
    }
    if (result) {
        result = list_n == NULL && other_n == NULL;
    }

    return (result);
}

data_t list_search(list_t list, index_t index) {
    /* PRE */
    assert(list != NULL && index != NULL);

    data_t result = NULL;
    node_t aux = NULL;

    aux = list->fst;
    while (aux != NULL) {
        if (index_is_equal(index, pair_fst(aux->elem))) {
            result = pair_snd(aux->elem);
            aux = NULL;
        } else {
            aux = aux->next;
        }
    }

    return (result);
}

list_t list_append(list_t list, index_t index, data_t data) {
    /* PRE */
    assert(list != NULL && index != NULL && data != NULL);

    node_t node = NULL;

    node = calloc(1, sizeof(struct _node_t));
    assert(node != NULL);
    node->elem = pair_from_index_data(index, data);
    node->next = NULL;
    if (list->fst == NULL) {
        list->fst = node;
    } else {
        list->lst->next = node;
    }
    list->lst = node;

    return (list);
}

list_t list_remove(list_t list, index_t index) {
    /*PRE */
    assert(list != NULL && index != NULL);

    node_t node = NULL, prev = NULL;

    node = list->fst;
    while (node != NULL && !index_is_equal(pair_fst(node->elem), index)) {
        prev = node;
        node = node->next;
    }
    if (node != NULL) {
        /* Si se borra el primer nodo, reasignar list->fst. */
        if (prev == NULL) {
            list->fst = node->next;
        } else {
            prev->next = node->next;
        }
        /* Si se borra el último nodo, reasignar list->lst. */
        if (node->next == NULL) {
            list->lst = prev;
            prev = NULL;
        }
        node->elem = pair_destroy(node->elem);
        free(node);
        node = NULL;
    }

    return (list);
}

list_t list_copy(list_t list) {
    /* PRE */
    assert(list != NULL);

    list_t result = NULL;
    node_t aux = NULL, prev = NULL, node = NULL;

    result = calloc(1, sizeof(struct _list_t));
    assert(result != NULL);
    aux = list->fst;
    while (aux != NULL) {
        node = calloc(1, sizeof(struct _node_t));
        assert(node != NULL);
        node->elem = pair_copy(aux->elem);
        node->next = NULL;
        if (prev == NULL) {
            result->fst = node;
        } else {
            prev->next = node;
        }
        if (aux->next == NULL) {
            result->lst = node;
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
    assert(list != NULL && fd != NULL);

    node_t aux = NULL;
    char *word = NULL, *def = NULL;

    aux = list->fst;
    if (aux == NULL) {
        fprintf(fd, "\n");
    }
    while (aux != NULL) {
        word = index_to_string(pair_fst(aux->elem));
        def = data_to_string(pair_snd(aux->elem));
        fprintf(fd, "%s: %s\n", word, def);
        free(word);
        free(def);
        aux = aux->next;
    }
}
