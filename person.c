#include "string_lib.h"
#include "person.h"

Person *Init_Person()
{
    Person *person = (Person *) malloc(sizeof(Person));

    if (person == NULL)
    {
        printf("Failed to initialize person.\n");
        return NULL;
    }

    person->first_name = NULL;
    person->last_name = NULL;
    person->city = NULL;
    person->county = NULL;
    person->state = NULL;
    person->zip = NULL;
    person->phone1 = NULL;
    person->phone = NULL;
    person->email = NULL;

    person->next = NULL;
    person->prev = NULL;
    return person;
}

Person *Create_Person(string_list *info)
{
    Person *person = Init_Person();

    person->first_name = get(info, 1)->str;
    person->last_name = get(info, 2)->str;
    person->company_name = get(info, 3)->str;
    person->address = get(info, 4)->str;
    person->city = get(info, 5)->str;
    person->county = get(info, 6)->str;
    person->state = get(info, 7)->str;
    person->zip = get(info, 8)->str;
    person->phone1 = get(info, 9)->str;
    person->phone = get(info, 10)->str;
    person->email = get(info, 11)->str;

    return person;
}

void free_person(Person *person)
{
    free(person->first_name);
    free(person->last_name);
    free(person->city);
    free(person->county);
    free(person->state);
    free(person->zip);
    free(person->phone1);
    free(person->phone);
    free(person->email);
    free(person);
}

Person_List *Init_Person_List()
{
    Person_List *init_list = (Person_List*) malloc(sizeof(Person_List));

    if (init_list == NULL)
    {
        printf("Initialize person list failed.\n");
        return NULL;
    }

    init_list->head = NULL;
    init_list->end = NULL;
    init_list->size = 0;

    return init_list;
}

void free_person_list(Person_List *list)
{
    Person *iterator = list->head;

    while (iterator != NULL)
    {
        Person *next = iterator->next;
        free_person(iterator);
        iterator = next;
    }

    free(list);
}

void empty_person_list(Person_List *list)
{
    Person *iterator = list->head;

    while (iterator != NULL)
    {
        Person *next = iterator->next;
        free_person(iterator);
        iterator = next;
    }

    list->head = NULL;
    list->end = NULL;
}

void add_person(Person_List * list, string_list *info)
{
    Person *new_person = Create_Person(info);

    if (list->size == 0)
    {
        list->head = new_person;
        list->end = new_person;
    }
    else
    {
        list->end->next = new_person;
        new_person->prev = list->end;
        list->end = new_person;
    }

    list->size++;
}

void print_schema(FILE *file, Person *schema)
{
    fprintf(file, "%s\t",schema->first_name);
    fprintf(file, "%s\t",schema->first_name);
    fprintf(file, "%s\t\t\t\t",schema->company_name);
    fprintf(file, "%s\t\t\t\t",schema->address);
    fprintf(file, "%s\t\t",schema->city);
    fprintf(file, "%s\t\t\t",schema->county);
    fprintf(file, "%s\t",schema->state);
    fprintf(file, "%s\t",schema->zip);
    fprintf(file, "%s\t\t",schema->phone1);
    fprintf(file, "%s\t\t",schema->phone);
    fprintf(file, "%s\t\n",schema->email);
}

void print_info(FILE *file,Person *person)
{
    if (strlen(person->first_name) >= 8)
        fprintf(file, "%s\t",person->first_name);
    else 
        fprintf(file, "%s\t\t",person->first_name);

    if (strlen(person->last_name) >= 8)
        fprintf(file, "%s\t",person->last_name);
    else 
        fprintf(file, "%s\t\t",person->last_name);

    if (strlen(person->company_name) <= 15)
        fprintf(file, "%s\t\t\t\t",person->company_name);
    else if (strlen(person->company_name) >= 25)
      fprintf(file, "%s\t\t",person->company_name);
    else
        fprintf(file, "%s\t\t\t",person->company_name);

    if (strlen(person->address) < 16)
        fprintf(file, "%s\t\t\t",person->address);
    else      
        fprintf(file, "%s\t\t",person->address);

    if (strlen(person->city) < 8)
        fprintf(file, "%s\t\t", person->city);
    else
        fprintf(file, "%s\t", person->city);

    if (strlen(person->county) < 8)
        fprintf(file, "%s\t\t\t", person->county);
    else if (strlen(person->county) >= 20)
        fprintf(file, "%s\t", person->county);
    else
        fprintf(file, "%s\t\t", person->county);

    fprintf(file, "%s\t", person->state);

    fprintf(file, "%s\t", person->zip);

    fprintf(file, "%s\t", person->phone1);

    fprintf(file, "%s\t", person->phone);

    fprintf(file, "%s\n", person->email);
}