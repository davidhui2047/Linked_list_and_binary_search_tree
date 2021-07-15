#include <stdlib.h>
#include <stdio.h>
#include "list.h"

/*
Create an empty student list
*/
StudentList create_list()
{
    StudentList self;
    self.head = NULL;
    return self;
}

/*
Check whether a student is in the student list
@param:self, a List that store all the student in a course
@param:student_id, student id
*/
ListNodePtr search_stdNode(StudentList* self, long student_id)
{
    ListNodePtr current = self->head;
    while (current != NULL)
    {
        if (current->id == student_id)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

/*
Count how many student is in a course
@param:self, a List that store all the student in a course
*/
int count_stdNode(StudentList* self)
{
    int count = 0;
    ListNodePtr current = self->head;
    while (current != NULL)
    {
        current = current->next;
        count++;
    }
    return count;
}

/*
Add a student into a student list
@param:self, a List that store all the student in a course
@param:student_id, student id
*/
void insert_list(StudentList* self, long student_id)
{
    ListNodePtr current = self->head;
    ListNodePtr prev = NULL;
    ListNodePtr new_node = malloc(sizeof * new_node);
    new_node->id = student_id;
    new_node->next = NULL;
    while (current != NULL)
    {
        prev = current;
        current = current->next;
    }

    if (current == self->head)
    {
        new_node->next = current;
        self->head = new_node;
    }
    else
    {
        new_node->next = current;
        prev->next = new_node;
    }
}

/*
Delete a student from a student list
@param:self, a List that store all the student in a course
@param:student_id, student id
*/
void delete_list_item(StudentList* self, long student_id)
{
    ListNodePtr current = self->head;
    ListNodePtr prev = NULL;

    while (current != NULL)
    {
        if (current->id == student_id)
        {
            if (prev == NULL)
            {
                self->head = current->next;
                free(current);
                current = self->head;
            }
            else
            {
                prev->next = current->next;
                free(current);
                current = prev->next;
            }
        }
        else
        {
            prev = current;
            current = current->next;
        }
    }
}

/*
Empty a student list and free the memory
@param:self, a List that store all the student in a course
*/
void destroy_list(StudentList* self) {
    ListNodePtr current = self->head;
    while (current != NULL) {
        ListNodePtr to_free = current;
        current = current->next;
        free(to_free);
    }
    self->head = NULL;
}