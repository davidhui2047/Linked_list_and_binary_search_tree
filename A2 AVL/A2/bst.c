#include <stdlib.h>
#include <stdio.h>
#include<string.h>
#include "bst.h"

//create an empty bst
BST create_bst()
{
    BST tree;
    tree.root = NULL;
    return tree;
}

/*
find a BST node
@param:self, a BSTNodePtr that contain a course
@param:course_name, the name of a course
*/
BSTNodePtr find_bst_node(BSTNodePtr self, String course_name)
{
    if (self == NULL || (strcmp(self->course.name, course_name) == 0))
    {
        return self;
    }
    else if (strcmp(self->course.name, course_name) > 0)
    {
        return find_bst_node(self->left, course_name);
    }
    else
    {
        return find_bst_node(self->right, course_name);
    }
}

/*
pass a BST root to find_bst_node
@param:self, a BST that contain all the course
@param:course_name, the name of a course
*/
BSTNodePtr find_bst(BST* self, String course_name)
{
    return find_bst_node(self->root, course_name);
}

/*
insert a node to a BST
@param:self, a BSTNodePtr that contain a course
@param:course_name, the name of a course
*/
BSTNodePtr insert_bst_node(BSTNodePtr self, String course_name)
{
    if (self == NULL)
    {
        self = malloc(sizeof * self);
        self->course.name = course_name;
        self->course.students= create_list();
        self->left = self->right = NULL;
    }
    else if (strcmp(self->course.name, course_name) > 0)
    {
        self->left = insert_bst_node(self->left, course_name);
    }
    else if (strcmp(self->course.name, course_name) < 0)
    {
        self->right = insert_bst_node(self->right, course_name);
    }
    return self;
}

/*
pass a BST root to insert_bst_node
@param:self, a BST that contain all the course
@param:course_name, the name of a course
*/
void insert_bst(BST* self, String course_name)
{
    self->root = insert_bst_node(self->root, course_name);
}

/*
find a node that has the smallest value
@param:self, a BSTNodePtr that contain a course
*/
BSTNodePtr min_node(BSTNodePtr self)
{
    BSTNodePtr current = self;
    while (current->left != NULL)
    {
        current = current->left;
    }
    return current;
}

/*
delete a node from a BST
@param:self, a BSTNodePtr that contain a course
@param:course_name, the name of a course
*/
BSTNodePtr delete_bst_node(BSTNodePtr self, String course_name)
{
    if (self != NULL)
    {
        if (strcmp(self->course.name, course_name) == 0)
        {
            if (self->left != NULL && self->right != NULL)
            {
                BSTNodePtr successor = min_node(self->right);
                self->course.name = successor->course.name;
                self->right = delete_bst_node(self->right, self->course.name);
            }
            else
            {
                BSTNodePtr to_free = self;
                if (self->left)
                {
                    self = self->left;
                }
                else
                {
                    self = self->right;
                }
                destroy_list(&to_free->course.students); 
                free(to_free); 
            }
        }
        else if (strcmp(self->course.name, course_name) > 0)
        {
            self->left = delete_bst_node(self->left, course_name);
        }
        else
        {
            self->right = delete_bst_node(self->right, course_name);
        }
    }
    return self;
}

/*
pass a BST root to delete_bst_node
@param:self, a BST that contain all the course
@param:course_name, the name of a course
*/
void delete_bst(BST* self, String course_name)
{
    self->root = delete_bst_node(self->root, course_name);
}

/*
print a BST node that contain the student id
@param:self, a BSTNodePtr that contain a course
@param:student_id, the student id of a student
*/
void print_bst_node(BSTNodePtr self, long student_id)
{
    if (self != NULL)
    {
        print_bst_node(self->left, student_id);
        if (search_stdNode(&self, student_id) != NULL) {
            printf("%s \n", self->course.name);
        }
        print_bst_node(self->right, student_id);
    }
}

/*
pass a BST root to print_bst_node
@param:self, a BST that contain all the course
@param:student_id, the student id of a student
*/
void print_bst(BST* self, long student_id)
{
    print_bst_node(self->root, student_id);
}

/*
empty the all the BST node
@param:self, a BSTNodePtr that contain a course
*/
void destroy_bst_node(BSTNodePtr self)
{
    if (self != NULL)
    {
        destroy_bst_node(self->left);
        destroy_bst_node(self->right);
        destroy_list(&self->course.students);
        free(self); 
    }
}

/*
pass a BST root to destroy_bst_node
@param:self, a BST that contain all the course
*/
void destroy_bst(BST* self)
{
    destroy_bst_node(self->root);
}

/*===================================================
The following function is for AVL
uncomment the below function to switch to AVL
Also comment the above insert_bst and delete_bst function
Reference:
https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
https://www.geeksforgeeks.org/avl-tree-set-2-deletion/?ref=lbp
===================================================*/

///*
//Compare two student id and find the bigger one
//@param:student_id_a, first student id
//@param:student_id_b, second student id
//*/
//int bigger_num(long student_id_a, long student_id_b)
//{
//    return (student_id_a > student_id_b) ? student_id_a : student_id_b;
//}
//
///*
//calculate the height of a BST
//@param:self, a BSTNodePtr that contain a course
//*/
//int height(BSTNodePtr self)
//{
//    if (self == NULL)
//    {
//        return 0;
//    }
//    else
//    {
//        int left = height(self->left);
//        int right = height(self->right);
//        if (left < right)
//        {
//            return 1 + right;
//        }
//        else
//        {
//            return 1 + left;
//        }
//    }
//}
//
///*
//figure out how to balance a node 
//@param:self, a BSTNodePtr that contain a course
//*/
//int getBalance(BSTNodePtr self)
//{
//    int balance = 0;
//    if (self == NULL)
//    {
//        return 0;
//    }
//    return balance = height(self->left) - height(self->right);;
//}
//
///*
//rotate a node to left
//@param:self, a BSTNodePtr that contain a course
//*/
//BSTNodePtr left_rotate(BSTNodePtr self)
//{
//    BSTNodePtr y = self->right;
//    BSTNodePtr t2 = y->left;
//    y->left = self;
//    self->right = t2;
//    self->height = bigger_num(height(self->left), height(self->right)) + 1;
//    y->height = bigger_num(height(y->left), height(y->right)) + 1;
//    return y;
//}
//
///*
//rotate a node to right
//@param:self, a BSTNodePtr that contain a course
//*/
//BSTNodePtr right_rotate(BSTNodePtr self)
//{
//    BSTNodePtr y = self->left;
//    BSTNodePtr t2 = y->right;
//    y->right = self;
//    self->left = t2;
//    self->height = bigger_num(height(self->left), height(self->right)) + 1;
//    y->height = bigger_num(height(y->left), height(y->right)) + 1;
//    return y;
//}
//
///*
//insert a node to avl
//@param:self, a BSTNodePtr that contain a course
//@param:course_name, the name of a course
//*/
//BSTNodePtr insert_avl_node(BSTNodePtr self, String course_name)
//{
//    int balance = 0;
//    if (self == NULL)
//    {
//        self = malloc(sizeof * self);
//        self->course.name = course_name;
//        self->course.students = create_list();
//        self->left = self->right = NULL;
//
//    }
//    else if (strcmp(self->course.name, course_name) > 0)
//    {
//        self->left = insert_avl_node(self->left, course_name);
//    }
//    else if (strcmp(self->course.name, course_name) < 0)
//    {
//        self->right = insert_avl_node(self->right, course_name);
//    }
//
//    balance = getBalance(self);
//
//    if (balance > 1 && strcmp(self->course.name, course_name) > 0)
//    {
//        return right_rotate(self);
//    }
//    else if (balance < -1 && strcmp(self->course.name, course_name) < 0)
//    {
//        self->left = left_rotate(self->left);
//        return right_rotate(self);
//    }
//    else if (balance > 1 && strcmp(self->course.name, course_name) < 0)
//    {
//        return left_rotate(self);
//    }
//    else if (balance < -1 && strcmp(self->course.name, course_name) > 0)
//    {
//        return left_rotate(self);
//    }
//    return self;
//}
//
///*
//pass a BST root to insert_avl_node
//@param:self, a BST that contain all the course
//@param:course_name, the name of a course
//*/
//void insert_avl(BST* self, String course_name)
//{
//    self->root = insert_avl_node(self->root, course_name);
//}
//
///*
//delete a node from avl
//@param:self, a BSTNodePtr that contain a course
//@param:course_name, the name of a course
//*/
//BSTNodePtr delete_avl_node(BSTNodePtr self, String course_name)
//{
//    int balance = 0;
//    if (self != NULL)
//    {
//        if (strcmp(self->course.name, course_name) == 0)
//        {
//            if (self->left != NULL && self->right != NULL)
//            {
//                BSTNodePtr successor = min_node(self->right);
//                self->course.name = successor->course.name;
//                self->right = delete_avl_node(self->right, self->course.name);
//            }
//            else
//            {
//                BSTNodePtr to_free = self;
//                if (self->left)
//                {
//                    self = self->left;
//                }
//                else
//                {
//                    self = self->right;
//                }
//                free(to_free);
//            }
//        }
//        else if (strcmp(self->course.name, course_name) > 0)
//        {
//            self->left = delete_avl_node(self->left, course_name);
//        }
//        else
//        {
//            self->right = delete_avl_node(self->right, course_name);
//        }
//    }
//
//    balance = getBalance(self);
//
//    if (balance > 1 && getBalance(self->left) >= 0)
//    {
//        return right_rotate(self);
//    }
//    else if (balance > 1 && getBalance(self->left) < 0)
//    {
//        self->left = left_rotate(self->left);
//        return right_rotate(self);
//    }
//    else if (balance < -1 && getBalance(self->right) <= 0)
//    {
//        return left_rotate(self);
//    }
//    else if (balance < -1 && getBalance(self->right) > 0)
//    {
//        return left_rotate(self);
//    }
//    return self;
//}
//
///*
//pass a BST root to delete_avl_node
//@param:self, a BST that contain all the course
//@param:course_name, the name of a course
//*/
//void delete_avl(BST* self, String course_name)
//{
//    self->root = delete_avl_node(self->root, course_name);
//}