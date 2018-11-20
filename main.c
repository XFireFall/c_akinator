#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "lib/constants.h"
#include "lib/tree_a.h"

enum {
    CMD_EXIT,
    CMD_ADD,
    CMD_INFO,
    CMD_LOAD,
    CMD_SAVE,
    CMD_GRAPH,
    CMD_DUMP,
    CMD_COMP,
    CMD_ID,
    CMD_HELP
    };

int main()
{
    printf(BLUE"# Akintor (binary-tree-based game)\n"
               "# (c) XFireFall 2018\n\n"RESET);

    //*******************

    printf("Type help for... help\n");

    struct Tree_a a = {};

    Tree_a_constructor(&a, 0);

    int line1[MAX_STR_LEN], line2[MAX_STR_LEN];
    int state = 0;
    char cmd[MAX_STR_LEN] = "";

    do
    {
        printf("$ ==>"BLUE);
        scanf("%s", cmd);
        if(!strcmp(cmd, "exit"))
            state = CMD_EXIT;
        else if(!strcmp(cmd, "add"))
            state = CMD_ADD;
        else if(!strcmp(cmd, "info"))
            state = CMD_INFO;
        else if(!strcmp(cmd, "load"))
            state = CMD_LOAD;
        else if(!strcmp(cmd, "save"))
            state = CMD_SAVE;
        else if(!strcmp(cmd, "graph"))
            state = CMD_GRAPH;
        else if(!strcmp(cmd, "dump"))
            state = CMD_DUMP;
        else if(!strcmp(cmd, "comp"))
            state = CMD_COMP;
        else if(!strcmp(cmd, "id"))
            state = CMD_ID;
        else if(!strcmp(cmd, "help"))
            state = CMD_HELP;
        else
            state = -1;
        printf(RESET);

        switch(state)
        {
        case CMD_EXIT:
            break;

        case CMD_ADD:
            Tree_a_add(&a);
            break;

        case CMD_INFO:
            printf("Enter the name of the object to search for:\n==>\t"BLUE);
            readline(line1);
            printf(RESET);

            Tree_a_item_info(Tree_a_find(&a, line1));
            break;

        case CMD_LOAD:
            Tree_a_load(&a);
            break;

        case CMD_SAVE:
            Tree_a_save(&a);
            break;

        case CMD_GRAPH:
            Tree_a_make_graph(&a);
            break;

        case CMD_DUMP:
            Tree_a_dump(&a);
            break;

        case CMD_COMP:
            printf("Enter names of the objects to compare:\n==>\t"BLUE);
            readline(line1);
            printf(RESET"==>\t"BLUE);
            readline(line2);
            printf(RESET);

            Tree_a_difference(&a, line1, line2);
            break;

        case CMD_ID:
            printf("Enter new tree ID:\n==>\t"BLUE);
            scanf("%d", &a.ID);
            printf(RESET);
            break;

        case CMD_HELP:
            printf("\tadd   - Add new item (play the akinator game)\n");
            printf("\tcomp  - Compare two objects\n");
            printf("\tdump  - Print the tree in console (may be quite huge)\n");
            printf("\texit  - Exit program\n");
            printf("\tgraph - Make graph using the tree\n");
            printf("\thelp  - Your host, briieef manuuaal\n");
            printf("\tid    - Set tree ID\n");
            printf("\tinfo  - Get detailed information on the object\n");
            printf("\tload  - Load tree from file\n");
            printf("\tsave  - Save to file\n");
            break;

        default:
            printf("Unknown command\n");
            break;
        }

        printf("\n");
    } while(state != CMD_EXIT);

    Tree_a_destructor(&a);
    return 0;
}
