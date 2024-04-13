#include "header.h"

#define CHUNKS 80

typedef struct node
{
    string str;
    struct node *next;
    struct node *prev;
} node;

typedef struct string_list
{
    node *head;
    node *end;
    size_t size;
} string_list;

#define foreach(T, item, list) \
    for (T *item = list->head; item->next != NULL; item = item->next)

void free_string_list(string_list *list);

void empty_string_list(string_list *list);

string delete_substr(string str, int idx, size_t n);

string malloc_string();

string_list *init_string_list();

string read_line(FILE *file);

string_list *split_string(string_list *list, string str);

node *get(string_list *list, int index);

