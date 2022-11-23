#include "../include/akinator3000.h"

//-----------------------------------------------------------------------------

Tree_info *tree_info_ctor ()
{
    Tree_info *Info = (Tree_info*) calloc (1, sizeof (Tree_info));

    Info->Root        = NULL;
    Info->Curr_parent = NULL;

    Info->tree_in_file  = fopen ("../files/tree_in.txt",  "r");
    Info->tree_out_file = fopen ("../files/tree_out.txt", "w+");

    Info->File_input = file_reader (Info->tree_in_file);
    Info->Text = lines_separator (Info->File_input);

    Info->N(CURR_LINE) = 0;

    return Info;
}

//-----------------------------------------------------------------------------

void tree_info_dtor (Tree_info *Info)
{
    Info->Root = NULL;

    fclose (Info->tree_in_file);
    fclose (Info->tree_out_file);

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

        New_node->name = (char*) calloc (MAX_LEN, sizeof (char));

        if(New_node->name == NULL)
        {
            printf ("ERROR - memory allocation for Node name!\n");
        }
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

    if(side == LEFT)
    {
        if(Parent->Left == NULL)
        {
            Parent->Left = New_node;
        }

        else
        {
            New_node->Left = Parent->Left;
            Parent->Left->Parent = New_node;
            Parent->Left = New_node;
        }
    }

    else if(side == RIGHT)
    {
        if(Parent->Right == NULL)
        {
            Parent->Right = New_node;
        }

        else
        {
            New_node->Left = Parent->Right;
            Parent->Right->Parent = New_node;
            Parent->Right = New_node;
        }
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

void read_tree (Tree_info *Info)
{
    while(Info->N(CURR_LINE) < Info->File_input->num_of_lines)
    {
        char name[MAX_LEN] = "";

        Node *New_node = NULL;

        if(sscanf (Info->Text[Info->N(CURR_LINE)].begin_line, "{%s", name) == 1 &&
           strchr (Info->Text[Info->N(CURR_LINE)].begin_line, '}') != NULL        )
        {
            if(!Info->Curr_parent->Left)
            {
                insert_node (name, Info->Curr_parent, LEFT);
            }

            else
            {
                insert_node (name, Info->Curr_parent, RIGHT);
            }

            printf ("-%s\n", name);

            ++Info->N(CURR_LINE);
        }

        else if(sscanf (Info->Text[Info->N(CURR_LINE)].begin_line, "{%s", name) == 1)
        {

            if(!Info->Root)
            {
                create_root (name, Info);

                Info->Curr_parent = Info->Root;
            }

            else
            {
                if(!Info->Curr_parent->Left)
                {
                    New_node = insert_node (name, Info->Curr_parent, LEFT);
                }

                else
                {
                    New_node = insert_node (name, Info->Curr_parent, RIGHT);
                }

                Info->Curr_parent = New_node;
            }

            printf ("-%s\n", name);

            read_tree (Info);

            ++Info->N(CURR_LINE);
        }

        else if(Info->Text[Info->N(CURR_LINE)].begin_line[0] == '}')
        {
            Info->Curr_parent = Info->Curr_parent->Parent;

            ++Info->N(CURR_LINE);
        }

        else
        {
            printf ("WHAS IS DAS?\n");
        }
    }
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

    printf ("%d", Curr_node->name);

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

    printf ("%d)", Curr_node->name);
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


