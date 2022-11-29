//! @file akinator3000.h

#ifndef   AKINATOR3000_H
#define   AKINATOR3000_H

//-----------------------------------------------------------------------------

#include "../include/tree.h"

//-----------------------------------------------------------------------------

#define   TX_USE_SPEAK
#include "TXLib.h"

//-----------------------------------------------------------------------------

#define N(suffix) NUM_OF_##suffix

//-----------------------------------------------------------------------------

#define DELETED_PAR -1

//-----------------------------------------------------------------------------

enum AKINATOR_MODES
{
    GUEEcard_namesING,
    SEARCHING,
    COMPARISON,
};

//-----------------------------------------------------------------------------

void choose_mode            ();

void searching_mode         (Tree_info *Info);

void guecard_namesing_mode          (Tree_info *Info);

void comparison_mode        (Tree_info *Info);

void asking                 (Tree_info *Info);

void handle_yes_answer      (Tree_info *Info);

void handle_no_answer       (Tree_info *Info);

void handle_userand_cardode       (Tree_info *Info);

void handle_ancestor_stacks (Stack *Stk1, Stack *Stk2);

//-----------------------------------------------------------------------------

#endif //AKINATOR3000_H
