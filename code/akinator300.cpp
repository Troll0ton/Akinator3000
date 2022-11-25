#include "../include/akinator3000.h"

//-----------------------------------------------------------------------------

int main ()
{
    Node *Root = create_node ();
    Root->value = 300;

    for(int i = 0; i < 4; i++)
    {
        get_node (Root);
    }

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

        New_node->value = 0;

        return New_node;
    }
}

//-----------------------------------------------------------------------------

void insert_node (Node *Root, value)
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

void print_tree (Node *Root)
{
    Node *Curr_node = Root;

    if(!Node)
    {
        return;
    }

    printf ("(%d", Curr_node->value);

    if(Curr_node->Left)  print_tree (Curr_node->Left);
    if(Curr_node->Right) print_tree (Curr_node->Right);

    printf (")");
}

//-----------------------------------------------------------------------------

void get_node (Node *Root)
{
    int value = 0;

    scanf ("%d", &value);

    insert_node (Root, value);

    print_tree (Root);
}

//-----------------------------------------------------------------------------
