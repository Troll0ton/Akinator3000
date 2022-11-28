//! @file akinator3000.h

#ifndef   AKINATOR3000_H
#define   AKINATOR3000_H

//-----------------------------------------------------------------------------

#include "../include/tree.h"

//-----------------------------------------------------------------------------

#define tprint(...) fprintf (Info->file_out, __VA_ARGS__)

//-----------------------------------------------------------------------------

#define N(suffix)  NUM_OF_##suffix

//-----------------------------------------------------------------------------

#define DELETED_PAR -1

//-----------------------------------------------------------------------------

enum AKINATOR_MODES
{
    GUEESSING,
    SEARCHING,
    COMPARISON,
};

//-----------------------------------------------------------------------------

void choose_mode     ();

void searching_mode  (Tree_info *Info);

void guessing_mode   (Tree_info *Info);

void comparison_mode (Tree_info *Info);

void asking          (Tree_info *Info);

//-----------------------------------------------------------------------------

#endif //AKINATOR3000_H
