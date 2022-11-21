#include "../include/akinator3000.h"

//-----------------------------------------------------------------------------

int main ()
{
    Node      *Root = create_node ();
    Tree_info *Info = (Tree_info*) calloc (1, sizeof (Tree_info));

    printf ("Enter root: ");

    scanf ("%d", &Root->value);

    menu (Root, Info);

    tree_dtor (Root);

    return 0;
}

//-----------------------------------------------------------------------------

Node *create_node ()
{
    Node *New_node = (Node*) calloc (1, sizeof (Node));

    if(!New_node)
    {
        printf ("ERROR -memory allocation for new node!\n");
    }

    else
    {
        New_node->Parent = NULL;
        New_node->Left   = NULL;
        New_node->Right  = NULL;

        New_node->name = (char*) calloc (LM(NAME_LEN), sizeof (char));
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

void insert_node (Node *Root, int value)
{
    Node *Curr_node = Root;
    Node *New_node  = create_node ();

    if(Curr_node->value >= value)
    {
        if(Curr_node->Left)
        {
            insert_node (Curr_node->Left, value);
        }

        else
        {
            Curr_node->Left  = New_node;
            New_node->Parent = Curr_node;
            New_node->value  = value;
        }
    }

    else
    {
        if(Curr_node->Right)
        {
            insert_node (Curr_node->Right, value);
        }

        else
        {
            Curr_node->Right = New_node;
            New_node->Parent = Curr_node;
            New_node->value  = value;
        }
    }
}

//-----------------------------------------------------------------------------

void print_tree_preorder (Node *Root)
{
    Node *Curr_node = Root;

    if(!Curr_node)
    {
        return;
    }

    printf ("(%d", Curr_node->value);

    if(Curr_node->Left)  print_tree_preorder (Curr_node->Left);
    if(Curr_node->Right) print_tree_preorder (Curr_node->Right);

    printf (")");
}

//-----------------------------------------------------------------------------

void print_tree_inorder (Node *Root)
{
    Node *Curr_node = Root;

    if(!Curr_node)
    {
        return;
    }

    printf ("(");

    if(Curr_node->Left)  print_tree_inorder (Curr_node->Left);

    printf ("%d", Curr_node->value);

    if(Curr_node->Right) print_tree_inorder (Curr_node->Right);

    printf (")");
}

//-----------------------------------------------------------------------------

void print_tree_postorder (Node *Root)
{
    Node *Curr_node = Root;

    if(!Curr_node)
    {
        return;
    }

    printf ("(");

    if(Curr_node->Left)  print_tree_postorder (Curr_node->Left);

    if(Curr_node->Right) print_tree_postorder (Curr_node->Right);

    printf ("%d)", Curr_node->value);
}

//-----------------------------------------------------------------------------

void get_node (Node *Root)
{
    int value = 0;

    scanf ("%d", &value);

    insert_node (Root, value);

    printf ("\n");
}

//-----------------------------------------------------------------------------

void tree_dtor (Node *Root)
{
    Node *Curr_node = Root;

    if(!Curr_node)
    {
        return;
    }

    if(Curr_node->Left)  tree_dtor (Curr_node->Left);

    if(Curr_node->Right) tree_dtor (Curr_node->Right);

    free (Curr_node);
}

//-----------------------------------------------------------------------------

void check_empty_tree (Node *Root)
{
    if(!Root) printf ("EMPTY!\n");
    else      printf ("FULL! \n");
}

//-----------------------------------------------------------------------------

void menu (Node *Root, Tree_info *Info)
{
    int cmd = -1;

    printf ("____________________________________________________| QUEUE |____________________________________________________\n\n");
    printf ("------------------------------------------------------------\n");
    printf ("1 value            - get_node \n\n");
    printf ("2                  - print_tree_preorder \n\n");
    printf ("3                  - print_tree_inorder\n\n");
    printf ("4                  - print_tree_postorder\n\n");
    printf ("5                  - check_empty_tree\n\n");
    printf ("6                  - find_depth\n\n");
    printf ("0                  - |||STOP|||\n\n");
    printf ("------------------------------------------------------------\n");

    while (cmd != 0)
    {
        scanf ("%d", &cmd);

        if(cmd == 1)
        {
            get_node (Root);
        }

        else if(cmd == 2)
        {
            print_tree_preorder (Root);
            printf ("\n------------------------------------------------------------\n");
        }

        else if(cmd == 3)
        {
            print_tree_inorder (Root);
            printf ("\n------------------------------------------------------------\n");
        }

        else if(cmd == 4)
        {
            print_tree_postorder (Root);
            printf ("\n------------------------------------------------------------\n");
        }

        else if(cmd == 5)
        {
            check_empty_tree (Root);
        }

        else if(cmd == 6)
        {
            Info->curr_depth = 0;
            Info->tree_depth = 0;

            find_depth (Root, Info);
            printf ("|CURRENT DEPTH - %d|\n", Info->tree_depth);
        }

        else if(cmd == 0)
        {
            printf ("\n--------------------STOP--------------------\n");
        }

        else printf ("-?-");
    }
}

//-----------------------------------------------------------------------------

void find_depth (Node *Root, Tree_info *Info)
{
    Node *Curr_node = Root;

    if(!Curr_node)
    {
        if(Info->curr_depth > Info->tree_depth)
        {
            Info->tree_depth = Info->curr_depth;
        }

        Info->curr_depth--;

        return;
    }

    if(Curr_node->Left)
    {
        find_depth (Curr_node->Left, Info);
        Info->curr_depth++;
    }

    if(Curr_node->Right)
    {
        find_depth (Curr_node->Right, Info);
        Info->curr_depth++;
    }

    free (Curr_node);
}

//-----------------------------------------------------------------------------

