#pragma once

//Define the information that a student can have, a student will have student id
typedef struct listNode {
    long id;
    struct listNode* next;
} *ListNodePtr;

//Define the structure of StudentList
typedef struct list {
    ListNodePtr head;
} StudentList;

StudentList create_list(); //Create an empty student list
ListNodePtr search_stdNode(StudentList* self, long student_id); //Check whether a student is in the student list
int count_stdNode(StudentList* self); //Count how many student is in a course
void insert_list(StudentList* self, long student_id); //Add a student into a student list
void delete_list_item(StudentList* self, long student_id); //Delete a student from a student list
void destroy_list(StudentList* self); //Empty a student list and free the memory