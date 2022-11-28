#include "../include/akinator3000.h"

//-----------------------------------------------------------------------------

void choose_mode ()
{
    Tree_info *Info = tree_info_ctor();

    read_tree (Info);

    print_tree_preorder (Info->Root);

    say_sentence ("GOOD MORNING MY DEAR FRIENDE!");

    printf ("________________________________________________________________________\n"
            "   HELLO WORLD! It is Akinator, choose the mode:\n\n"
            "   0 - GUEESSING MODE\n"
            "   1 - SEARCHING MODE\n"
            "   2 - COMPARISON MODE\n\n");

    int mode_par = 0;

    scanf ("%d", &mode_par);

    switch(mode_par)
    {
        case GUEESSING:
            guessing_mode (Info);
            break;
        case SEARCHING:
            searching_mode (Info);
            break;
        case COMPARISON:
            comparison_mode (Info);
            break;
        default:
            printf ("MODE DOES NOT EXIST!\n");
            break;
    }

    fclose (Info->file_tree);

    Info->file_tree = fopen ("../files/tree.txt", "w+");

    save_tree (Info->Root, Info);

    tree_dump (Info);

    tree_dtor (Info->Root);

    tree_info_dtor (Info);
}

//-----------------------------------------------------------------------------

void searching_mode (Tree_info *Info)
{
    printf ("HELLO WORLD! It is searching mode\n"
            "Input name:\n\n");

    char name[MAX_LEN] = "";

    scanf ("%s", name);

    Stack Stk = { 0 };
    stack_ctor (&Stk, SIZE_INIT);

    printf ("description: ");

    if(find_node (Info->Root, name, &Stk))
    {
        while(Stk.size_stk > 0)
        {
            printf ("%s, ", stack_pop (&Stk));
        }
    }

    else
    {
        printf ("This name does not exists!\n");
    }

    stack_dtor (&Stk);
}

//-----------------------------------------------------------------------------

void guessing_mode (Tree_info *Info)
{
    printf ("HELLO WORLD! It is guessing mode\n");

    Info->Curr_parent = Info->Root;

    asking (Info);
}

//-----------------------------------------------------------------------------

void asking (Tree_info *Info)
{
    printf ("Is it %s?\n", Info->Curr_parent->name);

    char answer[MAX_LEN] = "";

    scanf ("%s", answer);

    if(stricmp (answer, "YES") == 0)
    {
        Info->Curr_parent = Info->Curr_parent->Left;

        if(Info->Curr_parent)
        {
            asking (Info);
        }

        else
        {
            printf ("I knew it!\n");
        }
    }

    else if(stricmp (answer, "NO") == 0)
    {
        if(Info->Curr_parent->Right)
        {
            Info->Curr_parent = Info->Curr_parent->Right;

            asking (Info);
        }

        else
        {
            char *description = (char*) calloc (MAX_LEN, sizeof (char));
            char *difference  = (char*) calloc (MAX_LEN, sizeof (char));

            printf ("I do not know this thing! Enter your description:\n");
            scanf  ("%s", description);

            printf ("Enter your difference:\n");
            scanf  ("%s", difference);

            char *old_name = Info->Curr_parent->name;

            Info->Curr_parent->name = difference;

            insert_node (description, Info->Curr_parent, LEFT);
            insert_node (old_name,    Info->Curr_parent, RIGHT);
        }
    }

    else
    {
        printf ("I don not understand you\n");

        asking (Info);
    }
}

//-----------------------------------------------------------------------------

void comparison_mode (Tree_info *Info)
{
    printf ("HELLO WORLD! It is comparison mode\n"
            "Input names:\n\n");

    char name1[MAX_LEN] = "";
    char name2[MAX_LEN] = "";

    scanf ("%s %s", name1, name2);

    Stack Stk1 = { 0 };
    stack_ctor (&Stk1, SIZE_INIT);

    Stack Stk2 = { 0 };
    stack_ctor (&Stk2, SIZE_INIT);

    Node *First_node  = find_node (Info->Root, name1, &Stk1);
    Node *Second_node = find_node (Info->Root, name2, &Stk2);

    if(First_node && Second_node)
    {
        char *first_description  = NULL;
        char *second_description = NULL;

        printf ("SAME THINGS: ");

        while(Stk1.size_stk > 0 && Stk2.size_stk > 0)
        {
            first_description  = stack_pop (&Stk1);
            second_description = stack_pop (&Stk2);

            if(stricmp (first_description, second_description) == 0)
            {
                printf ("%s, ", first_description);
            }

            else break;
        }

        printf ("\n"
                "DIFFERENCES: FIRST: ");

        while(Stk1.size_stk > 0)
        {
            printf ("%s, ", first_description);

            first_description = stack_pop (&Stk1);
        }

        printf ("\n"
                "             SECOND: ");

        while(Stk2.size_stk > 0)
        {
            printf ("%s, ", second_description);

            second_description = stack_pop (&Stk2);
        }
    }

    else
    {
        printf ("One of names was not found!\n");
    }

    stack_dtor (&Stk1);
    stack_dtor (&Stk2);
}

//-----------------------------------------------------------------------------

void say_sentence (char* sentence)
{
    char speak_sentence[MAX_LEN] = "";

    sprintf (speak_sentence, "<speak version=\"1.0\" xmlns=\"http://www.w3.org/2001/10/synthesis\" xml:lang=\"en-US\"> \
                    <voice name=\"en-US-TonyNeural\">                         \
                    %s                                                                                 \
                    </voice>                                                               \
                    </speak>", sentence);

    txSpeak (speak_sentence);
}

//-----------------------------------------------------------------------------


