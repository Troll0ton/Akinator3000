#include "../include/akinator3000.h"

//-----------------------------------------------------------------------------

void choose_mode ()
{
    Tree_info *Info = tree_info_ctor();

    while (getchar () != '\n') { }

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

    Node *Root = Info->Root;

    tree_dtor (Root);

    tree_info_dtor (Info);
}

//-----------------------------------------------------------------------------

void searching_mode (Tree_info *Info)
{
    speak_and_print ("HELLO WORLD! It is searching mode. Input name:\n\n");

    char *name = NULL;

    name = get_line ();

    Stack Stk = { 0 };
    stack_ctor (&Stk, SIZE_INIT);

    speak_and_print ("description: ");

    if(search_node (Info->Root, name, &Stk))
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

    free (name);

    stack_dtor (&Stk);
}

//-----------------------------------------------------------------------------

void guessing_mode (Tree_info *Info)
{
    speak_and_print ("HELLO WORLD! It is guessing mode\n");

    Info->Curr_parent = Info->Root;

    ask_user (Info);
}

//-----------------------------------------------------------------------------

void ask_user (Tree_info *Info)
{
    char text[MAX_LEN] = "Is it ";

    strcat (text, Info->Curr_parent->name);

    speak_and_print (text);

    if(Info->Curr_parent->Left)
    {
        printf ("?");
    }

    printf ("\n");

    char answer[MAX_LEN] = "";

    scanf ("%s", answer);

    if(stricmp (answer, "YES") == 0)
    {
        handle_positive_answer (Info);
    }

    else if(stricmp (answer, "NO") == 0)
    {
        handle_negative_answer (Info);
    }

    else
    {
        speak_and_print ("I do not understand you\n");

        ask_user (Info);
    }
}

//-----------------------------------------------------------------------------

void handle_positive_answer (Tree_info *Info)
{
    Info->Curr_parent = Info->Curr_parent->Left;

    if(Info->Curr_parent)
    {
        ask_user (Info);
    }

    else
    {
        speak_and_print ("I knew it!\n");
    }
}

//-----------------------------------------------------------------------------

void handle_negative_answer (Tree_info *Info)
{
    if(Info->Curr_parent->Right)
    {
        Info->Curr_parent = Info->Curr_parent->Right;

        ask_user (Info);
    }

    else
    {
        handle_user_node (Info);
    }
}

//-----------------------------------------------------------------------------

void handle_user_node (Tree_info *Info)
{
    char *description = NULL;
    char *difference  = NULL;

    speak_and_print ("I do not know this thing! Enter your description:\n");
    description = get_line ();

    speak_and_print ("Enter your difference:\n");
    difference = get_line ();

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

    char *name1 = NULL;
    char *name2 = NULL;

    name1 = get_line ();
    name2 = get_line ();

    Stack Stk1 = { 0 };
    stack_ctor (&Stk1, SIZE_INIT);

    Stack Stk2 = { 0 };
    stack_ctor (&Stk2, SIZE_INIT);

    Node *First_node  = search_node (Info->Root, name1, &Stk1);
    Node *Second_node = search_node (Info->Root, name2, &Stk2);

    if(CORRECT_INPUT)
    {
        handle_ancestor_stacks (&Stk1, &Stk2);
    }

    else
    {
        speak_and_print ("One of names was not found!\n");
    }

    free (name1);
    free (name2);

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

    printf ("\n");

    if(Stk1->size_stk > 0)
    {
        speak_and_print ("But first is ");
    }

    while(Stk1->size_stk > 0)
    {
        speak_and_print (first_description);

        first_description = stack_pop(Stk1)->name;
    }

    printf ("\n");

    if(Stk2->size_stk > 0)
    {
        speak_and_print ("And the second ");
    }

    while(Stk2->size_stk > 0)
    {
        speak_and_print (second_description);

        second_description = stack_pop(Stk2)->name;
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

