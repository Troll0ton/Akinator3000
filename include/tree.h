//! @file tree.h

#ifndef   TREE_H
#define   TREE_H

//-----------------------------------------------------------------------------

#include "../include/lines_handle.h"
#include "../include/input_output.h"
#include "../include/stack.h"

//-----------------------------------------------------------------------------

#define tprint(...) fprintf (Info->file_out, __VA_ARGS__)

#define dot_print(...) fprintf (Info->file_dot, __VA_ARGS__)

//-----------------------------------------------------------------------------

#define tree_info_ctor() tree_info_ctor_ (__FILE__, __LINE__)

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
    FILE *file_dump;

    FILE *file_dot;
    int   graph_num;

    Line *Text;
    File *File_input;

    Node *Root;
    Node *Curr_parent;

    int   N(CURR_LINE);
    int   N(CURR_CELL);
    int   flag_stop;

    const char *name;
    const char *file;
    int         line;
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

Tree_info *tree_info_ctor_      (const char* file, int line);

void       tree_info_dtor       (Tree_info *Info);

Node      *find_node            (Node *Curr_node, char *name);

void       print_tree_inorder   (Node *Root);

void       tree_dump            (Tree_info *Info);

void       make_tree_graph      (Tree_info *Info);

void       print_tree_postorder (Node *Root);

void       cell_builder         (Node *Root, Tree_info *Info);

void       connections_builder  (Node *Root, Tree_info *Info);

void       tree_dtor            (Node *Curr_node);

//-----------------------------------------------------------------------------

#endif //TREE_H
