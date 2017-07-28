#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "dict.h"
#include "dict_helpers.h"
#include "helpers.h"

#define SIZE 'z'
#define SEARCH 's'
#define ADD 'a'
#define DELETE 'd'
#define EMPTY 'e'
#define SHOW 'h'
#define COPY 'c'
#define LOAD 'l'
#define DUMP 'u'
#define QUIT 'q'


char print_menu(void) {
    char result = '\0';
    char *in = NULL;

    printf("\nChoose what you want to do. Options are:\n\n"
           "\t**************************************************************\n"
           "\t* z: Size of the dictionary                                  *\n"
           "\t* s: Search for a entry in the dict                          *\n"
           "\t* a: Add a new entry to the dict                             *\n"
           "\t* d: Delete an entry from the dict                           *\n"
           "\t* e: Empty the dict                                          *\n"
           "\t* h: Show the dict in stdout                                 *\n"
           "\t* c: Duplicate the current dict, show copied dict in stdout  *\n"
           "\t* l: Load the dict from a file                               *\n"
           "\t* u: Dump the dict to a file                                 *\n"
           "\t* q: Quit                                                    *\n"
           "\t**************************************************************\n"
           "\nPlease enter your choice: ");

    in = readline_from_stdin();
    assert(in != NULL);
    result = in[0];
    free(in);
    in = NULL;

    return (result);
}


int main(void) {
    char option = '\0';
    dict_t dict = NULL, copy = NULL;
    char *filename = NULL, *word = NULL, *def = NULL;

    dict = dict_empty();

    while (1) {
        option = print_menu();
        switch (option) {
            case SIZE:
                printf("\t-> The size is %u.\n", dict_length(dict));
                break;
            case SEARCH:
                printf("\tPlease enter the word to search in the dict: ");
                word = readline_from_stdin();
                assert(word != NULL);
                if (dict_exists(dict, word)) {
                    def = dict_search(dict, word);
                    printf("\t-> The definition for \"%s\" is \"%s\".\n", word,
                           def);
                    free(def);
                    def = NULL;
                } else {
                    printf("\t-> The word \"%s\" does not exist in the "
                           "dict.\n", word);
                }
                free(word);
                word = NULL;
                break;
            case ADD:
                printf("\tPlease enter the word to add to the dict: ");
                word = readline_from_stdin();
                assert(word != NULL);
                if (dict_exists(dict, word)) {
                    printf("\t-> The word %s already exists.\n", word);
                } else {
                    printf("\tPlease enter the definition: ");
                    def = readline_from_stdin();
                    assert(def != NULL);
                    dict = dict_add(dict, word, def);
                    printf("\t-> The word and definition were added.\n");
                    free(def);
                    def = NULL;
                }
                free(word);
                word = NULL;
                break;
            case DELETE:
                printf("\tPlease enter the word to delete from the dict: ");
                word = readline_from_stdin();
                assert(word != NULL);
                if (dict_exists(dict, word)) {
                    dict = dict_remove(dict, word);
                    printf("\t-> The word was successfully removed.\n");
                } else {
                    printf("\t-> The word %s does not exist.\n", word);
                }
                free(word);
                word = NULL;
                break;
            case EMPTY:
                dict = dict_destroy(dict);
                dict = dict_empty();
                printf("\t-> The dictionary was successfully emptied.\n");
                break;
            case SHOW:
                printf("{\n");
                dict_dump(dict, stdout);
                printf("}\n");
                break;
            case COPY:
                copy = dict_copy(dict);
                printf("\t-> The dictionary was duplicated. Showing the "
                       "duplicated dict:\n");
                printf("{\n");
                dict_dump(copy, stdout);
                printf("}\n");
                copy = dict_destroy(copy);
                break;
            case LOAD:
                printf("\tPlease enter the filename to load the dict from: ");
                filename = readline_from_stdin();
                assert(filename != NULL);
                copy = dict_from_file(filename);
                if (copy != NULL) {
                    dict = dict_destroy(dict);
                    dict = copy;
                    copy = NULL;
                    printf("\t-> The dictionary was successfully loaded.\n");
                } else {
                    printf("Can not load dict from filename %s\n", filename);
                }
                free(filename);
                filename = NULL;
                break;
            case DUMP:
                printf("\tPlease enter the filename to dump the dict to: ");
                filename = readline_from_stdin();
                assert(filename != NULL);
                dict_to_file(dict, filename);
                printf("\t-> The dictionary was successfully dumped.\n");
                free(filename);
                filename = NULL;
                break;
            case QUIT:
                printf("\t-> Exiting.\n");
                dict = dict_destroy(dict);
                return (EXIT_SUCCESS);
            default:
                printf("\n\"%c\" is invalid. Please choose a valid option."
                       "\n\n", option);
        }
    }

    return (EXIT_SUCCESS);
}
