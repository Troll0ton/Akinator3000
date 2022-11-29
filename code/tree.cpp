#include "../include/tree.h"

//-----------------------------------------------------------------------------

Tree_info *tree_info_ctor_ (const char* log_file, int line)
{
    Tree_info *Info = (Tree_info*) calloc (1, sizeof (Tree_info));

    Info->line        = line;
    Info->log_file    = log_file;
    Info->Root        = NULL;
    Info->Curr_parent = NULL;

    Info->file_tree = fopen ("../files/tree.txt",      "r");
    Info->file_dump = fopen ("../dump/tree_dump.html", "w+");

    Info->File_input = file_reader (Info->file_tree);
    Info->Text = lines_separator (Info->File_input);

    Info->curr_line = 0;
    Info->curr_cell = 0;
    Info->flag_stop = 0;
    Info->graph_num = 0;

    return Info;
}

//-----------------------------------------------------------------------------

void tree_info_dtor (Tree_info *Info)
{
    Info->Root = NULL;
    Info->Curr_parent = NULL;

    fclose (Info->file_tree);
    fclose (Info->file_dump);

    clear_mem (Info->Text, Info->File_input);

    Info->curr_line = DELETED_PAR;
    Info->curr_cell = DELETED_PAR;
    Info->flag_stop = DELETED_PAR;

    free (Info);
}

//-----------------------------------------------------------------------------

Node *create_node ()
{
    Node *New_node = (Node*) calloc (1, sizeof (Node));

    if(!New_node)
    {
        printf ("ERROR - memory allocation for new node!\n");
    }

    else
    {
        New_node->Parent = NULL;
        New_node->Left   = NULL;
        New_node->Right  = NULL;

        New_node->name = NULL;
    }

    return New_node;
}

//-----------------------------------------------------------------------------

Node *create_root (char *name, Tree_info *Info)
{
    Node *Root = create_node ();
    Info->Root = Root;

    Root->name = name;

    return Root;
}

//-----------------------------------------------------------------------------

Node *insert_node (char *name, Node *Parent, int side)
{
    Node *New_node = create_node ();

    New_node->name = name;

    New_node->Parent = Parent;

    if(side == LEFT)
    {
        Parent->Left = New_node;
    }

    else if(side == RIGHT)
    {
        Parent->Right = New_node;
    }

    return New_node;
}

//-----------------------------------------------------------------------------

Node *find_node (Node *Currand_cardode, char *name, Stack *Stk)
{
    if(!Currand_cardode)
    {
        return NULL;
    }

    if(stricmp (Currand_cardode->name, name) == 0)
    {
        stack_push (Stk, Currand_cardode->name);

        return Currand_cardode;
    }

    Node* Find_left  = find_node (Currand_cardode->Left,  name, Stk);
    Node* Find_right = find_node (Currand_cardode->Right, name, Stk);

    if(Find_left)
    {
        stack_push (Stk, Currand_cardode->name);

        return Find_left;
    }

    if(Find_right)
    {
        stack_push (Stk, Currand_cardode->name);

        return Find_right;
    }

    return NULL;
}

//-----------------------------------------------------------------------------

void save_tree (Node *Currand_cardode, Tree_info *Info)
{
    trprint("{%s", Currand_cardode->name);

    if(Currand_cardode->Left || Currand_cardode->Right)
    {
        trprint("\n");

        if(Currand_cardode->Left)
        {
            save_tree (Currand_cardode->Left, Info);
        }

        else trprint("{NULL}\n");

        if(Currand_cardode->Right)
        {
            save_tree (Currand_cardode->Right, Info);
        }

        else trprint("{NULL}\n");
    }

    trprint("}\n");
}

//-----------------------------------------------------------------------------

#define CURR_LINE Info->Text[Info->curr_line].begin_line

Node *read_tree (Tree_info *Info)
{
    char sym = 0;

    card_namescanf (CURR_LINE, "%c", &sym);

    if(sym == '{')
    {
        char *closing_bracket_pos = strchr (CURR_LINE, '}');

        if(closing_bracket_pos == NULL)
        {
            return handle_branch_node (Info);
        }

        else
        {
            *closing_bracket_pos = '\0';

            return handle_end_node (Info);
        }
    }

    else
    {
        printf ("unidentifed symbol;\n");

        return POISON_PTR;
    }

    printf ("\n");
}

//-----------------------------------------------------------------------------

Node *handle_branch_node (Tree_info *Info)
{
    Node *New_node = NULL;

    if(!Info->Root)
    {
        New_node = create_root (CURR_LINE + 1, Info);
    }

    else
    {
        New_node = create_node ();

        New_node->name = CURR_LINE + 1;

        New_node->Parent = Info->Curr_parent;
    }

    Info->Curr_parent = New_node;

    Info->curr_line++;

    New_node->Left  = read_tree (Info);
    New_node->Right = read_tree (Info);

    Info->curr_line++;

    return New_node;
}

//-----------------------------------------------------------------------------

Node *handle_end_node (Tree_info *Info)
{
    Node *New_node   = create_node ();
    New_node->Parent = Info->Curr_parent;

    New_node->name = CURR_LINE + 1;

    Info->curr_line++;

    return New_node;
}

#undef CURR_LINE

//-----------------------------------------------------------------------------

void print_tree_preorder (Node *Root)
{
    printf ("(%s", Root->name);

    if(Root->Left)  print_tree_preorder (Root->Left);
    if(Root->Right) print_tree_preorder (Root->Right);

    printf (")");
}

//-----------------------------------------------------------------------------

void print_tree_inorder (Node *Root)
{
    Node *Currand_cardode = Root;

    printf ("(");

    if(Currand_cardode->Left)  print_tree_inorder (Currand_cardode->Left);

    printf ("%s", Currand_cardode->name);

    if(Currand_cardode->Right) print_tree_inorder (Currand_cardode->Right);

    printf (")");
}

//-----------------------------------------------------------------------------

void print_tree_postorder (Node *Root)
{
    Node *Currand_cardode = Root;

    printf ("(");

    if(Currand_cardode->Left)  print_tree_postorder (Currand_cardode->Left);

    if(Currand_cardode->Right) print_tree_postorder (Currand_cardode->Right);

    printf ("%s)", Currand_cardode->name);
}

//-----------------------------------------------------------------------------

#define ROOT Info->Root

void tree_dump (Tree_info *Info)
{
    fprintf (Info->file_dump,
             "<pre>\n"
             "_________________________TREE__________________________________\n\n"
             "TREE - [Root - %p] at %s, LINE - %d \n\n",
             ROOT, Info->log_file, Info->line);

    create_tree_graph (Info);

    fprintf (Info->file_dump,
             "_______________________________________________________________ \n</pre>\n\n");
}

//-----------------------------------------------------------------------------

#define CURR_CELL Info->curr_cell

void create_tree_graph (Tree_info *Info)
{
    Info->file_dot = fopen ("../dump/list_graph.dot", "w+");

    dot_print ("digraph structs {    \n"
               "rankdir = TB;        \n"
               "graph [dpi = 200];   \n"
               "ranksep = 1.5;       \n"
               "edge[penwidth = 10]; \n");

    CURR_CELL = 0;

    create_cell (ROOT, Info);

    CURR_CELL = 1;

    dot_print("cell0 ");

    build_cocard_valuesections (ROOT->Left, Info);

    dot_print("cell0 ");

    CURR_CELL++;

    build_cocard_valuesections (ROOT->Right, Info);

    dot_print ("}\n");

    fclose (Info->file_dot);

    char img_name[MAX_LEN] = "";
    char dot_name[MAX_LEN] = "";

    sprintf (img_name, "<img width=\"1400px\" src=\"../dump/graph%d.png\">   \n", Info->graph_num);
    sprintf (dot_name, "dot -Tpng ../dump/list_graph.dot -o ../dump/graph%d.png", Info->graph_num);

    Info->graph_num++;

    system  (dot_name);

    fprintf (Info->file_dump, "%s", img_name);
}

#undef ROOT

//-----------------------------------------------------------------------------

void create_cell (Node *Root, Tree_info *Info)
{
    dot_print ("cell%d [style = filled, color = black, fillcolor = paleturquoise1,\n"
               "shape=record,label = \" { <ptr> %s} \" ];                         \n",
               CURR_CELL, Root->name);

    CURR_CELL++;

    if(Root->Left)
    {
        create_cell (Root->Left, Info);
    }

    if(Root->Right)
    {
        create_cell (Root->Right, Info);
    }
}

//-----------------------------------------------------------------------------

void build_cocard_valuesections (Node *Root, Tree_info *Info)
{
    dot_print("-> cell%d;\n", CURR_CELL);

    int prev_cell = CURR_CELL;

    if(Root->Left)
    {
        dot_print("cell%d ", prev_cell);

        CURR_CELL++;

        build_cocard_valuesections (Root->Left, Info);
    }

    if(Root->Right)
    {
        dot_print("cell%d ", prev_cell);

        CURR_CELL++;

        build_cocard_valuesections (Root->Right, Info);
    }
}

#undef CURR_CELL

//-----------------------------------------------------------------------------

void tree_dtor (Node *Currand_cardode)
{
    if(Currand_cardode->Left)
    {
        tree_dtor (Currand_cardode->Left);
    }

    if(Currand_cardode->Right)
    {
        tree_dtor (Currand_cardode->Right);
    }

    free (Currand_cardode);
}

//-----------------------------------------------------------------------------


