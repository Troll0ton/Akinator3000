#include "../include/akinator3000.h"

//-----------------------------------------------------------------------------

int main ()
{
    Tree_info *Info = tree_info_ctor ();

    read_tree (Info);

    print_tree_preorder (Info->Root);

    print_tree (Info->Root, Info);

    //-----------------------------------------------------------------------------

/*
    create_root ("TOMT", Info);

    insert_node ("amogus", Info->Root, LEFT);
    insert_node ("grigorievich", Info->Root, RIGHT);

    Node *Cur_cell = find_node (Info->Root, "amogus");

    insert_node ("MOSCOW", Cur_cell, RIGHT);
    insert_node ("BERLIN", Cur_cell, LEFT);

    Cur_cell = find_node (Info->Root, "BERLIN");
    insert_node ("LIBLIN", Cur_cell, LEFT);
    insert_node ("TOUT", Cur_cell, RIGHT);



    print_tree_preorder (Info->Root);*/

    //-----------------------------------------------------------------------------

    tree_dtor (Info->Root);

    tree_info_dtor (Info);

    return 0;
}

//-----------------------------------------------------------------------------
