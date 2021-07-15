#pragma once
#include "list.h"

//Use string to store course name
typedef char* String;

/*Define the information that a course can have, 
a course can have course name and a list or student*/
typedef struct course {
	String name;
	StudentList students;
} Course;

//Define the structure of BSTNodePtr
typedef struct bstNode {
	Course course;
	//int height; //This variable is for AVL, uncomment this line to switch to avl
	struct bstNode* left;
	struct bstNode* right;
} *BSTNodePtr;

//Define the structure of BST
typedef struct bst {
	BSTNodePtr root;
} BST;

BST create_bst(); //create an empty bst
BSTNodePtr find_bst(BST* self, String course_name); //pass a BST root to find_bst_node
void insert_bst(BST* self, String course_name); //pass a BST root to insert_bst_node //comment this line to switch to avl
void delete_bst(BST* self, String course_name); //pass a BST root to delete_bst_node //comment this line to switch to avl
void print_bst(BST* self, long student_id); //pass a BST root to print_bst_node
void destroy_bst(BST* self); //pass a BST root to destroy_bst_node

//The following function is for AVL
//void insert_avl(BST* self, String course_name); //pass a BST root to insert_avl_node //uncomment this line to switch to avl
//void delete_avl(BST* self, String course_name); //pass a BST root to delete_avl_node //uncomment this line to switch to avl