#include "../include/tree.h"

//-----------------------------------------------------------------------------

Tree_info *tree_info_ctor_ (const char* file, int line)
{
    Tree_info *Info = (Tree_info*) calloc (1, sizeof (Tree_info));

    Info->line = line;
    Info->file = file;

    Info->Root        = NULL;
    Info->Curr_parent = NULL;

    Info->file_in   = fopen ("../files/tree_in.txt",   "r");
    Info->file_out  = fopen ("../files/tree_out.txt",  "w+");
    Info->file_dump = fopen ("../dump/tree_dump.html", "w+");

    Info->File_input = file_reader (Info->file_in);
    Info->Text = lines_separator (Info->File_input);

    Info->N(CURR_LINE) = 0;
    Info->N(CURR_CELL) = 0;

    Info->flag_stop    = 0;
    Info->graph_num    = 0;

    return Info;
}

//-----------------------------------------------------------------------------

void tree_info_dtor (Tree_info *Info)
{
    Info->Root = NULL;

    fclose (Info->file_in);
    fclose (Info->file_out);
    fclose (Info->file_dump);

    clear_mem (Info->Text, Info->File_input);

    Info->N(CURR_LINE) = DELETED_PAR;

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
        New_node->name   = NULL;
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

Node *find_node (Node *Curr_node, char *name)
{
    if(!Curr_node)
    {
        return NULL;
    }

    if(stricmp (Curr_node->name, name) == 0)
    {
        return Curr_node;
    }

    Node* Find_left  = find_node (Curr_node->Left,  name);
    Node* Find_right = find_node (Curr_node->Right, name);

    if (Find_left)  return Find_left;
    if (Find_right) return Find_right;

    return NULL;
}

//-----------------------------------------------------------------------------

void *print_tree (Node *Curr_node, Tree_info *Info)
{
    tprint("{%s", Curr_node->name);

    if(Curr_node->Left || Curr_node->Right)
    {
        tprint("\n");

        if(Curr_node->Left)
        {
            print_tree (Curr_node->Left, Info);
        }

        else tprint("{NULL}\n");

        if(Curr_node->Right)
        {
            print_tree (Curr_node->Right, Info);
        }

        else tprint("{NULL}\n");
    }

    tprint("}\n");
}

//-----------------------------------------------------------------------------

Node *read_tree (Tree_info *Info)
{
    char sym = 0;

    Node *New_node = NULL;

    sscanf (Info->Text[Info->N(CURR_LINE)].begin_line, "%c", &sym);

    if(sym == '{')
    {
        if(strchr (Info->Text[Info->N(CURR_LINE)].begin_line, '}') == NULL)
        {
            if(!Info->Root)
            {
                New_node = create_root (Info->Text[Info->N(CURR_LINE)].name, Info);
            }

            else
            {
                New_node = create_node ();

                New_node->name = Info->Text[Info->N(CURR_LINE)].name;

                New_node->Parent = Info->Curr_parent;
            }

            Info->Curr_parent = New_node;

            Info->N(CURR_LINE)++;

            New_node->Left  = read_tree (Info);
            New_node->Right = read_tree (Info);

            Info->N(CURR_LINE)++;

            return New_node;
        }

        else
        {
            New_node = create_node ();
            New_node->Parent = Info->Curr_parent;
            New_node->name = Info->Text[Info->N(CURR_LINE)].name;

            Info->N(CURR_LINE)++;

            return New_node;
        }
    }

    else
    {
        printf ("unidentifed symbol;\n");
    }

    printf ("\n");
}

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
    Node *Curr_node = Root;

    printf ("(");

    if(Curr_node->Left)  print_tree_inorder (Curr_node->Left);

    printf ("%s", Curr_node->name);

    if(Curr_node->Right) print_tree_inorder (Curr_node->Right);

    printf (")");
}

//-----------------------------------------------------------------------------

void print_tree_postorder (Node *Root)
{
    Node *Curr_node = Root;

    printf ("(");

    if(Curr_node->Left)  print_tree_postorder (Curr_node->Left);

    if(Curr_node->Right) print_tree_postorder (Curr_node->Right);

    printf ("%s)", Curr_node->name);
}

//-----------------------------------------------------------------------------

void tree_dump (Tree_info *Info)
{
    fprintf (Info->file_dump,
             "<pre>\n"
             "_________________________TREE__________________________________\n\n"
             "TREE - [Root - %p] at %s, LINE - %d \n\n",
             Info->Root, Info->file, Info->line);

    make_tree_graph (Info);

    fprintf (Info->file_dump,
             "_______________________________________________________________ \n</pre>\n\n\n\n\n");
}

//-----------------------------------------------------------------------------

void make_tree_graph (Tree_info *Info)
{
    Info->file_dot = fopen ("../dump/list_graph.dot", "w+");

    dot_print ("digraph structs {                                                                  \n"
               "rankdir = TB;                                                                      \n"
               "graph [dpi = 100];                                                                 \n"
               "ranksep = 1.5;                                                                     \n"
               "edge[penwidth = 10];                                                               \n");

    Info->N(CURR_CELL) = 0;

    cell_builder (Info->Root, Info);

    Info->N(CURR_CELL) = 0;

    connections_builder (Info->Root, Info);

    dot_print ("}\n");

    fclose (Info->file_dot);

    char img_name[MAX_LEN] = "";
    char dot_name[MAX_LEN] = "";

    sprintf (img_name, "<img width=\"1400px\" src=\"../dump/graph%d.png\">   \n", Info->graph_num);
    sprintf (dot_name, "dot -Tpng ../dump/list_graph.dot -o ../dump/graph%d.png", Info->graph_num);
    Info->graph_num++;

    system  (dot_name);
    fprintf (Info->file_dump, img_name);
}

//-----------------------------------------------------------------------------

void cell_builder (Node *Root, Tree_info *Info)
{
    dot_print ("cell%d [style = filled, color = black, fillcolor = paleturquoise1,\n"
               "shape=record,label = \" { <ptr> %s} \" ];                         \n",
               Info->N(CURR_CELL), Root->name);

    Info->N(CURR_CELL)++;

    if(Root->Left)
    {
        cell_builder (Root->Left, Info);
    }

    if(Root->Right)
    {
        cell_builder (Root->Right, Info);
    }
}

//-----------------------------------------------------------------------------

void connections_builder (Node *Root, Tree_info *Info)
{
    dot_print("-> cell%d;\n",
              Info->N(CURR_CELL));

    Info->N(CURR_CELL)++;

    if(Root->Left)
    {
        dot_print("cell%d -> ",
                  Info->N(CURR_CELL));

        Info->N(CURR_CELL)++;

        connections_builder (Root->Left, Info);
    }

    if(Root->Right)
    {
        dot_print("cell%d -> ",
                  Info->N(CURR_CELL));

        Info->N(CURR_CELL)++;

        connections_builder (Root->Right, Info);
    }
}

//-----------------------------------------------------------------------------

void tree_dtor (Node *Curr_node)
{
    if(Curr_node->Left) tree_dtor (Curr_node->Left);

    if(Curr_node->Right) tree_dtor (Curr_node->Right);

    free (Curr_node->name);
    free (Curr_node);
}

//-----------------------------------------------------------------------------


