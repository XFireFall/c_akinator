DEF_CMD(add, {Tree_a_add(&akinator);})

DEF_CMD(comp, {
            printf("Enter names of the objects to compare:\n==>\t"BLUE);
            readline(line1);
            printf(RESET"==>\t"BLUE);
            readline(line2);
            printf(RESET);
            Tree_a_difference(&akinator, line1, line2);})

DEF_CMD(dump, {Tree_a_dump(&akinator);})

DEF_CMD(exit, { })

DEF_CMD(graph, {Tree_a_make_graph(&akinator);})

DEF_CMD(help, {
            printf("\tadd   - Add new item (play the akinator game)\n");
            printf("\tcomp  - Compare two objects\n");
            printf("\tdump  - Print the tree in console (may be quite huge)\n");
            printf("\texit  - Exit program\n");
            printf("\tgraph - Make graph using the tree\n");
            printf("\thelp  - Your host, briieef manuuaal\n");
            printf("\tid    - Set tree ID\n");
            printf("\tinfo  - Get detailed information on the object\n");
            printf("\tload  - Load tree from file\n");
            printf("\tsave  - Save to file\n");})

DEF_CMD(id, {
            printf("Current tree ID: %d\n", cur_id);
            printf("Enter new tree ID:\n==>\t"BLUE);
            scanf("%d", &cur_id);
            printf(RESET);
            akinator.ID = cur_id;})

DEF_CMD(info, {
            printf("Enter the name of the object to search for:\n==>\t"BLUE);
            readline(line1);
            printf(RESET);
            Tree_a_item_info(Tree_a_find(&akinator, line1));})

DEF_CMD(load, {Tree_a_load(&akinator);})

DEF_CMD(save, {Tree_a_save(&akinator);})





