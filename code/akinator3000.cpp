#include "../include/akinator3000.h"

//-----------------------------------------------------------------------------

void choose_mode ()
{
    Tree_info *Info = tree_info_ctor();

    read_tree (Info);

    printf          ("________________________________________________________________________\n");
    speak_and_print ("   HELLO WORLD! It is Akinator, choose the mode");
    printf          (":  \n\n"
                     "   0 - GUESSING MODE\n"
                     "   1 - SEARCHING MODE\n"
                     "   2 - COMPARISON MODE\n\n");

    int mode_par = 0;

    scanf ("%d", &mode_par);

    switch(mode_par)
    {
        case GUESSING:
            guessing_mode (Info);
            break;
        case SEARCHING:
            searching_mode (Info);
            break;
        case COMPARISON:
            comparison_mode (Info);
            break;
        default:
            speak_and_print ("MODE DOES NOT EXIST!\n");
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
    speak_and_print ("HELLO WORLD! It is searching mode\n\
                     Input name:\n\n");

    char name[MAX_LEN] = "";

    scanf ("%s", name);

    Stack Stk = { 0 };
    stack_ctor (&Stk, SIZE_INIT);

    speak_and_print ("description: ");

    if(find_node (Info->Root, name, &Stk))
    {
        while(Stk.size_stk > 0)
        {
            speak_and_print ((stack_pop (&Stk))->name);
        }
    }

    else
    {
        speak_and_print ("This name does not exists!\n");
    }

    stack_dtor (&Stk);
}

//-----------------------------------------------------------------------------

void guessing_mode (Tree_info *Info)
{
    speak_and_print ("HELLO WORLD! It is guessing mode\n");

    Info->Curr_parent = Info->Root;

    asking (Info);
}

//-----------------------------------------------------------------------------

void asking (Tree_info *Info)
{
    speak_and_print ("Is it ");
    speak_and_print (Info->Curr_parent->name);

    if(Info->Curr_parent->Left)
    {
        printf ("?");
    }

    printf ("\n");

    char answer[MAX_LEN] = "";

    scanf ("%s", answer);

    if(stricmp (answer, "YES") == 0)
    {
        handle_yes_answer (Info);
    }

    else if(stricmp (answer, "NO") == 0)
    {
        handle_no_answer (Info);
    }

    else
    {
        speak_and_print ("I do not understand you\n");

        asking (Info);
    }
}

//-----------------------------------------------------------------------------

void handle_yes_answer (Tree_info *Info)
{
    Info->Curr_parent = Info->Curr_parent->Left;

    if(Info->Curr_parent)
    {
        asking (Info);
    }

    else
    {
        speak_and_print ("I knew it!\n");
    }
}

//-----------------------------------------------------------------------------

void handle_no_answer (Tree_info *Info)
{
    if(Info->Curr_parent->Right)
    {
        Info->Curr_parent = Info->Curr_parent->Right;

        asking (Info);
    }

    else
    {
        handle_user_node (Info);
    }
}

//-----------------------------------------------------------------------------

void handle_user_node (Tree_info *Info)
{
    char *description = (char*) calloc (MAX_LEN, sizeof (char));
    char *difference  = (char*) calloc (MAX_LEN, sizeof (char));

    speak_and_print ("I do not know this thing! Enter your description:\n");
    scanf           ("%s", description);

    speak_and_print ("Enter your difference:\n");
    scanf           ("%s", difference);

    char *old_name = Info->Curr_parent->name;

    Info->Curr_parent->name = difference;

    insert_node (description, Info->Curr_parent, LEFT);
    insert_node (old_name,    Info->Curr_parent, RIGHT);
}

//-----------------------------------------------------------------------------

#define CORRECT_INPUT (First_node && Second_node)

void comparison_mode (Tree_info *Info)
{
    speak_and_print ("HELLO WORLD! It is comparison mode. Input names:\n\n");

    char name1[MAX_LEN] = "";
    char name2[MAX_LEN] = "";

    scanf ("%s %s", name1, name2);

    Stack Stk1 = { 0 };
    stack_ctor (&Stk1, SIZE_INIT);

    Stack Stk2 = { 0 };
    stack_ctor (&Stk2, SIZE_INIT);

    Node *First_node  = find_node (Info->Root, name1, &Stk1);
    Node *Second_node = find_node (Info->Root, name2, &Stk2);

    if(CORRECT_INPUT)
    {
        handle_ancestor_stacks (&Stk1, &Stk2);
    }

    else
    {
        speak_and_print ("One of names was not found!\n");
    }

    stack_dtor (&Stk1);
    stack_dtor (&Stk2);
}

#undef CORRECT_INPUT

//-----------------------------------------------------------------------------

void handle_ancestor_stacks (Stack *Stk1, Stack *Stk2)
{
    char *first_description  = NULL;
    char *second_description = NULL;

    while(Stk1->size_stk > 0 && Stk2->size_stk > 0)
    {
        first_description  = (stack_pop (Stk1))->name;
        second_description = (stack_pop (Stk2))->name;

        if(first_description == second_description)
        {
            speak_and_print ("they are same in: ");
            speak_and_print (first_description);

            printf ("\n");
        }

        else break;
    }

    speak_and_print (", but first is");

    while(Stk1->size_stk > 0)
    {
        speak_and_print (first_description);

        first_description = (stack_pop (Stk1))->name;
    }

    speak_and_print (", and second: ");

    while(Stk2->size_stk > 0)
    {
        speak_and_print (second_description);

        second_description = (stack_pop (Stk2))->name;
    }
}

//-----------------------------------------------------------------------------

void speak_up (char *text)
{
    char espeak_text[MAX_LEN] = "";

    strcpy (espeak_text, "espeak \"");

    strcat (espeak_text, text);
    strcat (espeak_text, "\"");

    system (espeak_text);
}

//-----------------------------------------------------------------------------

void speak_and_print (char *text)
{
    printf ("%s ", text);

    speak_up (text);
}

//-----------------------------------------------------------------------------

