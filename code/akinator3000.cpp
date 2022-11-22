#include "../include/akinator3000.h"

//-----------------------------------------------------------------------------

int main ()
{
    Node *Root = create_root ("aboba");

    Tree_info Info = { 0 };

    Info.tree_file = fopen ("../dump/tree.txt", "w+");

    insert_node ("amogus", Root, LEFT);

    print_tree (Root, Info.tree_file);

    tree_dtor (Root);

    fclose (Info.tree_file);

    return 0;
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

        New_node->name = (char*) calloc (LM(NAME_LEN), sizeof (char));

        if(New_node->name == NULL)
        {
            printf ("ERROR - memory allocation for Node name!\n");
        }
    }

    return New_node;
}

//-----------------------------------------------------------------------------

Node *create_root (char *name)
{
    Node *Root = create_node ();

    Root->name = name;

    return Root;
}

//-----------------------------------------------------------------------------

void insert_node (char *name, Node *Parent, int side)
{
    Node *New_node  = create_node ();

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

void *print_tree (Node *Curr_node, FILE *file_out)
{
    if(Curr_node)
    {
        tprint("\n");

        for(int i = 0; i < 0; i++)
        {
            tprint(" ");
        }

        tprint("{%s", Curr_node->name);
    }

    if(Curr_node->Left)
    {
        print_tree (Curr_node->Left, file_out);
    }

    if(Curr_node->Left)
    {
        print_tree (Curr_node->Left, file_out);
    }

    tprint("}\n");
}

//-----------------------------------------------------------------------------

void print_tree_preorder (Node *Root)
{
    Node *Curr_node = Root;

    printf ("(%d", Curr_node->name);

    if(Curr_node->Left)  print_tree_preorder (Curr_node->Left);
    if(Curr_node->Right) print_tree_preorder (Curr_node->Right);

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

