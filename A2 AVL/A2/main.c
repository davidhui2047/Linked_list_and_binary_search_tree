#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "list.h"
#include"bst.h"

/*
let user enter course code
*/
String prompt_course_code()
{
    char buffer[100];
    scanf_s("%s", buffer, 100);
    String course_code = malloc(sizeof(char) * (strlen(buffer) + 1));
    strcpy_s(course_code, sizeof(char) * (strlen(buffer) + 1), buffer);
    return course_code;
}

/*
let use input student id
*/
int prompt_student_id()
{
    int student_id;
    scanf_s("%d", &student_id);
    return student_id;
}

/*
Free all the memory that are used for this program
@param:self, a BST that store all the course
*/
void free_all_memory(BST* self)
{
    destroy_bst(self);
}

/*
call insert_bst or insert_avl to insert a course
@param:self, a BST that store all the course
*/
void insert_course(BST* self)
{
    printf("Course name: ");
    insert_bst(self, prompt_course_code()); //comment this line to switch to avl
    //insert_avl(self, prompt_course_code()); //uncomment this line to switch to avl
}

/*
call delete_bst or delete_avl to delete a course
@param:self, a BST that store all the course
*/
void delete_course(BST* self)
{
    printf("Course name: ");
    delete_bst(self, prompt_course_code()); //comment this line to switch to avl
    //delete_avl(self, prompt_course_code()); //uncomment this line to switch to avl
}

/*
call find_bst to find a course
then call insert_list to enroll a student in a course
@param:self, a BST that store all the course
*/
void enrol_student(BST* self)
{
    BSTNodePtr course;
    printf("Course Name: ");
    course = find_bst(self, prompt_course_code());
    printf("Student ID: ");
    insert_list(&course->course.students, prompt_student_id());
}

/*
call find_bst to find a course
then call delete_list_item to unenroll a student from a course
@param:self, a BST that store all the course
*/
void unenrol_student(BST* self)
{
    BSTNodePtr course;
    printf("Course Name: ");
    course = find_bst(self, prompt_course_code());
    printf("Student ID: ");
    delete_list_item(&course->course.students, prompt_student_id());
}

/*
Print all the courses and the number of 
students that enrolled in each course
@param:self, a root of a BST that store all the course
*/
void summary_item(BSTNodePtr self)
{
    if (self != NULL)
    {
        summary_item(self->left);
        printf("%s ", self->course.name);
        printf("%d ", count_stdNode(&(self->course.students)));
        summary_item(self->right);
    }
    printf("\n");
}

/*
Pass the root of the BST to the summary_item function
@param:self, a BST that store all the course
*/
void print_ordered_summary(BST* self) {
    summary_item(self->root);
}

/*
Print the ordered students enrolled in a course 
@param:self, a BST that store all the course
*/
void print_student_list(BST* self)
{
    BSTNodePtr course;
    printf("Course Name: ");
    course = find_bst(self, prompt_course_code());
    ListNodePtr current = course->course.students.head;
    while (current != NULL) {
        printf("%d \n", current->id);
        current = current->next;
    }
}

/*
Print the ordered courses that a student enrolled in
@param:self, a BST that store all the course
*/
void print_course_list(BST* self)
{
    printf("Student ID: ");
    print_bst(self, prompt_student_id());
    printf("\n");
}

/*
Prompt a menu and let use select function
*/
int main(int argc, char* argv[]) {
    BST courses = create_bst();
    int quit = 0;
    while (!quit)
    {
        int choice = 0;
        printf("\n0.quit\n1.add Course\n2.remove course\n");
        printf("3.enrol student\n4.unenrol student\n5.print summary\n");
        printf("6.print students\n7.print course list\nEnter option: ");
        printf("Enter option: ");
        scanf_s("%d", &choice);
        switch (choice)
        {
        case 0: free_all_memory(&courses); 
            quit = 1;
            break;
        case 1: insert_course(&courses);
            break;
        case 2: delete_course(&courses);
            break;
        case 3:enrol_student(&courses);
            break;
        case 4:unenrol_student(&courses);
            break;
        case 5:print_ordered_summary(&courses);
            break;
        case 6:print_student_list(&courses);
            break;
        case 7:print_course_list(&courses);
            break;
        }
    }
}
