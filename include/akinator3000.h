//! @file akinator3000.h

#ifndef   AKINATOR3000_H
#define   AKINATOR3000_H

//-----------------------------------------------------------------------------

#include "../include/lines_handle.h"
#include "../include/input_output.h"
#include "../include/stack.h"

//-----------------------------------------------------------------------------

#define N(suffix)  NUM_OF_##suffix

#define SG(suffix) SIGNATURE_##suffix

#define SZ(suffix) SIZE_OF_##suffix

#define LM(suffix) LIMIT_##suffix

#define F(suffix)  FLAG_##suffix

#define E(suffix)  ERROR_##suffix

#define P(suffix)  POISON_##suffix

//-----------------------------------------------------------------------------

typedef struct Node
{
    Node *Parent;
    Node *Left;
    Node *Right;
    char  name;
} Node;

//-----------------------------------------------------------------------------

enum NODE_INFO
{
    LM(NAME_LEN) = 300,
};

//-----------------------------------------------------------------------------

Node *create_node          ();

Node *init_root            (char *name);

void  insert_node          (Node *Root, int value);

void  get_node             (Node *Root);

void  print_tree_preorder  (Node *Root);

void  print_tree_inorder   (Node *Root);

void  print_tree_postorder (Node *Root);

void  tree_dtor            (Node *Root);

void  check_empty_tree     (Node *Root);

void  menu                 (Node *Root, Tree_info *Info);

void  find_depth           (Node *Root, Tree_info *Info);

//-----------------------------------------------------------------------------

#endif //AKINATOR3000_H
