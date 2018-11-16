#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../c_hash/lib/constants.h"

#include "tree_a.h"

int main()
{
    struct Tree_a a = {};
    Tree_a_load(&a);
    int line1[MAX_STR_LEN], line2[MAX_STR_LEN];
    //while(1)
    {
        //readline(line1);
        //readline(line2);
        linestrcopy(line1, "cat");
        linestrcopy(line2, "frog");
        Tree_a_difference(&a, line1, line2);
        //printf("%p\n", Tree_a_find(&a, line));
        //printline(a.head->name);
        //Tree_a_add(&a);Tree_a_dump(&a); printf("\n\n");
    }
    //Tree_a_dump(&a);
    Tree_a_destructor(&a);
    return 0;
}
