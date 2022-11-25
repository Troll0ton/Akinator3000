//! @file akinator3000.h

#ifndef   AKINATOR3000_H
#define   AKINATOR3000_H

//-----------------------------------------------------------------------------


#include <TXLib.h>
#include "../include/tree.h"

#include "../include/lines_handle.h"
#include "../include/input_output.h"
#include "../include/stack.h"

//-----------------------------------------------------------------------------

#define tprint(...) fprintf (Info->file_out, __VA_ARGS__)

//-----------------------------------------------------------------------------

#define N(suffix)  NUM_OF_##suffix

//-----------------------------------------------------------------------------

#define DELETED_PAR -1

//-----------------------------------------------------------------------------

enum TREE_INFO
{
    MAX_LEN = 100,
};

//-----------------------------------------------------------------------------

typedef struct Node
{
    Node *Parent;
    Node *Left;
    Node *Right;
    char *name;
} Node;

//-----------------------------------------------------------------------------

typedef struct Tree_info
{
    FILE *file_in;
    FILE *file_out;
    int   N(CURR_LINE);
    Line *Text;
    File *File_input;
    Node *Root;
    Node *Curr_parent;
    int   flag_stop;
} Tree_info;

//-----------------------------------------------------------------------------

enum SIDES
{
    LEFT,
    RIGHT,
};

//-----------------------------------------------------------------------------

Node      *create_node          ();

Node      *create_root          (char *name, Tree_info *Info);

Node      *insert_node          (char *name, Node *Parent, int side);

void      *print_tree           (Node *Curr_node, Tree_info *Info);

Node      *read_tree            (Tree_info *Info);

void       get_node             (Node *Root);

void       print_tree_preorder  (Node *Root);

Tree_info *tree_info_ctor       ();

void       tree_info_dtor       (Tree_info *Info);

Node      *find_node            (Node *Curr_node, char *name);

void       print_tree_inorder   (Node *Root);

void       print_tree_postorder (Node *Root);

void       tree_dtor            (Node *Curr_node);

//-----------------------------------------------------------------------------

#endif //AKINATOR3000_H
