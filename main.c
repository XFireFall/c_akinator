#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "lib/constants.h"
#include "lib/tree_a.h"

enum {
    #define DEF_CMD( cmd, instr ) cmd_##cmd,
    #include "lib/commands.h"
    #undef DEF_CMD
    nil
    };

int main()
{
    printf(BLUE"# Akintor (binary-tree-based game)\n"
               "# (c) XFireFall 2018\n\n"RESET);

    //*******************



    struct Tree_a akinator = {};
    int cur_id = 0;

    Tree_a_constructor(&akinator, cur_id);

    int line1[MAX_STR_LEN], line2[MAX_STR_LEN];
    int state = 0;
    char cmd[MAX_STR_LEN] = "";
    printf("Type help for... help\n"
           "Current tree ID: "BLUE"%d"RESET"\n", cur_id);

    do
    {
        printf("$ ==>"BLUE);
        scanf("%s", cmd);
        printf(RESET);

        #define DEF_CMD( cmdname, instr ) if(!strcmp(cmd, #cmdname)) state = cmd_##cmdname; else
        #include "lib/commands.h"
        #undef DEF_CMD
        state = nil;


        switch(state)
        {
        #define DEF_CMD( cmdname, instr ) case cmd_##cmdname: instr break;
        #include "lib/commands.h"
        #undef DEF_CMD

        default:
            printf("Unknown command\n");
            break;
        }

        printf("\n");
    } while(state != cmd_exit);

    Tree_a_destructor(&akinator);
    return 0;
}
