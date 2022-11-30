//! @file akinator3000.h

#ifndef   AKINATOR3000_H
#define   AKINATOR3000_H

//-----------------------------------------------------------------------------

#define N(suffix) NUM_OF_##suffix

//-----------------------------------------------------------------------------

#include "../include/tree.h"

//-----------------------------------------------------------------------------

#define DELETED_PAR -1

//-----------------------------------------------------------------------------

enum AKINATOR_MODES
{
    GUESSING,
    SEARCHING,
    COMPARISON,
};

//-----------------------------------------------------------------------------

void  choose_mode            ();

void  searching_mode         (Tree_info *Info);

void  guessing_mode          (Tree_info *Info);

void  comparison_mode        (Tree_info *Info);

void  ask_user               (Tree_info *Info);

void  handle_positive_answer (Tree_info *Info);

void  handle_negative_answer (Tree_info *Info);

void  handle_user_node       (Tree_info *Info);

void  handle_ancestor_stacks (Stack *Stk1, Stack *Stk2);

void  speak_up               (char *text);

void  speak_and_print        (char *text);

//-----------------------------------------------------------------------------

#endif //AKINATOR3000_H
