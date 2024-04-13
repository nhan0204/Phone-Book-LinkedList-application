#include "string_lib.h"

void free_string_list(string_list *list)
{
    node *iterator = list->head;

    while (iterator != NULL)
    {
        node *next = iterator->next;
        free(iterator);
        iterator = next;
    }

    list->head = NULL;
    list->end = NULL;
}

void empty_string_list(string_list *list)
{
    node *iterator = list->head;

    while (iterator != NULL)
    {
        node *next = iterator->next;
        free(iterator);
        iterator = next;
    }

    list->head = NULL;
    list->end = NULL;
}

node *alloc_node()
{
    node *tmp_node = malloc(sizeof(node));

    if (tmp_node == NULL)
    {
        printf("Failed to create node.\n");
        return NULL;
    }

    return tmp_node;
}

string malloc_string(size_t size)
{
    if (size == 0) return NULL;

    string str = (string) malloc(size * sizeof(char));

    if (str == NULL)
    {
        printf("Failed to allocate string.\n");
    }
    
    return str;
}

string realloc_string(string str, size_t size)
{
    string realloc_string = (string)realloc(str, size * sizeof(char));

    if (realloc_string == NULL)
    {
        printf("Failed to reallocate string.\n");
        return NULL;
    }

    return realloc_string;
}

string_list * init_string_list()
{
    string_list *init_list = (string_list *) malloc(sizeof(string_list));

    if (init_list == NULL)
    {
        printf("Initialize string list failed.\n");
        return NULL;
    }

    init_list->head = NULL;
    init_list->end = NULL;
    init_list->size = 0;

    return init_list;
}

void add_item(string_list *list, string item, const char mode)
{
    // create new node
    node *new_node = alloc_node();
    new_node->str = item;
    new_node->next = NULL;
    new_node->prev = NULL;

    if (list->size == 0)
    {
        list->head = new_node;
        list->end = new_node;
    }

    if (mode == 'f')
    {
        // in order to put new node in front of list
        // link next of new node to current node
        new_node->next = list->head;
        // link previous of head node to new node
        list->head->prev = new_node;
        // then update the head node to be new node
        list->head = new_node;
    }
  
    if (mode == 'b')
    {
        // in ordet to put new node to the back of list
        // link next of end node to new node
        list->end->next = new_node;
        // link previous of new node to end node
        new_node->prev = list->end;
        // then upadte the end node to be the new node
        list->end = new_node;
    }

    list->size++;
}

string read_line(FILE *file)
{
    size_t chunks = CHUNKS;
    size_t len = 0;
    int c;
    
    string str = malloc_string(chunks);

    do
    {
        c = fgetc(file);
        if (len == chunks) 
            str = realloc_string(str, (chunks *= 2));
        
        str[len++] = c;
    } while (c != EOF && c != '\r' && c != '\n');

    if (c == '\n' || c == '\r')
        fgetc(file);

    if (c == EOF)
        return "EOF";

    str[len] = '\0';
    
    return realloc_string(str, len);
}

string_list * split_string(string_list *list, string str)
{
    // get first token
    string token = strtok(str, ",");
    add_item(list, token, 'b');

    string tmp = NULL;

    do
    {
        token = strtok(NULL, ",");

        if (token != NULL)
        {
            if (token[0] == '\"')
            {
                tmp = token;
            }
            else if (token[strlen(token) - 1] == '\"')
            {
                tmp = delete_substr(tmp, 0, 1);
                token = delete_substr(token, strlen(token) - 1, 1);

                strcat(tmp, ",");
                strncat(tmp, token, strlen(token));
                token = strcpy(token, tmp);
                tmp = NULL;

                add_item(list, token, 'b');
            }
            else
            {
                add_item(list, token, 'b');
            }
        }
    } while (token != NULL);

    return list;
}

node * get(string_list *list, int index)
{
    int count = 1;
    node *iterator = list->head;

    while (iterator != NULL && count + 1 <= index)
    {
        iterator = iterator->next;
        count++;
    }

    if (iterator == NULL)
        return NULL;

    return iterator;
}

string delete_substr(string str, int idx, size_t n)
{
    string tmp = malloc_string((strlen(str) - n));

    // copy everything before idx
    memcpy(tmp, str, idx * sizeof(char));
    // copy everything after idx
    memcpy(tmp + idx, str + (idx + 1), (strlen(str) - idx - 1) * sizeof(char));
    
    str = tmp;
    return realloc_string(str, strlen(str));
}