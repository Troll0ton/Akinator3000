#include "../include/akinator3000.h"

//-----------------------------------------------------------------------------

void choose_mode ()
{
    printf ("________________________________________________________________________\n"
            "   HELLO WORLD! It is Akinator, choose the mode:"
            "   \n"
            "   1 - GUEESSING MODE\n"
            "   2 - SEARCHING MODE\n"
            "   3 - COMPARISON MODE\n\n");

    char mode_par = 0;

    scanf ("%d", mode_par);

    switch(mode_par)
    {
        case 1:
            guessing_mode ();
            break;
        case 2:
            searching_mode ();
            break;
        case 3:
            comparison_mode ();
            break;
    }

    else if(mode_par == 1)
    {
        guessing_mode ();
    }

    if(mode_par == 1)
    {
        guessing_mode ();
    }

}

//-----------------------------------------------------------------------------

void guessing_mode ()
{
    printf ("HELLO WORLD! It is ");

}

//-----------------------------------------------------------------------------

void guessing_mode ()
{
    printf ("HELLO WORLD! It is ");

}

//-----------------------------------------------------------------------------

void comparison_mode ()
{
    printf ("HELLO WORLD! It is ");

}

//-----------------------------------------------------------------------------


