#include "header.h"

typedef struct Person
{
    string first_name;
    string last_name;
    string company_name;
    string address;
    string city;
    string county;
    string state;
    string zip;
    string phone1;
    string phone;
    string email;

    struct Person *next;
    struct Person *prev;
} Person;

Person *Init_Person();
Person *Create_Person(string_list *info);

void free_person(Person *person);

typedef struct 
{
    Person *head;
    Person *end;
    size_t size;
} Person_List;

Person_List *Init_Person_List();

void free_person_list(Person_List * list);

void empty_person_list(Person_List * list);

void add_person(Person_List * list, string_list *info);

void print_info(FILE *file, Person *person);

void print_schema(FILE *file, Person *person);