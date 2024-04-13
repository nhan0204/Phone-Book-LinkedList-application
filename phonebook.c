#include "header.h"
#include "string_lib.h"
#include "person.h"

int main(void)
{
    FILE *file = fopen("50-contacts.csv", "r");
    FILE *out = fopen("output.txt", "w");

    if (file == NULL && out == NULL)
    {
        printf("Failed to open file.\n");
        return 1;
    }

    printf("File open succesfully.\n");

    string line = NULL;
    string_list *info = NULL;
    Person_List *phone_book = Init_Person_List();

    // firstline is schema
    Person *schema = Create_Person(split_string(init_string_list(), read_line(file)));
    print_schema(out, schema);

    do 
    {
        line = read_line(file);
        
        if (strcmp(line, "EOF") == 0) break;

        info = init_string_list();
        info = split_string(info, line);

        add_person(phone_book, info);

    } while (strcmp(line, "EOF") != 0);


    foreach(Person, person, phone_book)
        print_info(out, person);

    free(file);
    free(out);
}