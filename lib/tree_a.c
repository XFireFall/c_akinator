#include "tree_a.h"


//==========================__LINECOPY__========================
void linecopy(int* s, const int* t)
{
    assert(t != NULL);
    assert(s != NULL);
    assert(s != t);

    for( ; *t != 0; s++, t++)
        *s = *t;
    *s = 0;
    return;
}

//==========================__LINESTRCOPY__=====================
void linestrcopy(int* line, const char* s)
{
    assert(line != NULL);
    assert(s != NULL);

    int i = 0;
    for( ; s[i] != '\0'; i++)
        line[i] = (int) s[i];
    line[i] = 0;
    return;
}

//==========================__READLINE__========================
void readline(int* line)
{
    assert(line != NULL);

    int c = 1;
    while((c = getchar()) == (int) '\n')
        ;
    ungetc(c, stdin);

    while((c = getchar()) != (int) '\n')
        *line++ = c;
    *line = 0;

    return;
}

//==========================__FREADLINE__=======================
void freadline(FILE* infile, int* line)
{
    assert(infile != NULL);
    assert(line != NULL);

    int c = 1;
    while((c = getc(infile)) != (int) '\n')
        *line++ = c;
    *line = 0;

    return;
}

//==========================__FPRINTLINE__======================
void fprintline(FILE* outfile, const int* line)
{
    assert(outfile != NULL);
    assert(line != NULL);

    while(*line)
        fprintf(outfile, "%c", (char) *line++);
    return;
}

//==========================__PRINTTABS__=======================
void printtabs(int num)
{
    assert(num >= 0);

    printf(BLUE);
    for( ; num; num--)
        printf("  | ");
    printf(RESET);
    return;
}

//==========================__FPRINTTABS__======================
void fprinttabs(FILE* outfile, int num)
{
    assert(outfile != NULL);
    assert(num >= 0);

    for( ; num; num--)
        fprintf(outfile, "\t");
    return;
}




//======================item__INFO__============================
void Tree_a_item_info(struct Tree_a_item* this)
{
    if(this == NULL)
        return;

    printf("Current information about ");
    printline(this->name);
    printf(":\n");

    do
    {
        printf("\t");

        if(this->parent->left == this)
            printf("not ");

        printline(this->parent->name);
        printf("\n");

        this = this->parent;
    } while(this->parent);

    return;
}

//======================item__PATH__============================
void Tree_a_item_path(struct Tree_a_item* this, struct Tree_a_item*** arr)
{
    assert(arr != NULL);

    if(this->parent == NULL)
        return;

    Tree_a_item_path(this->parent, arr);
    **arr = this->parent;
    (*arr)++;
    return;
}






//======================tree__CONSTRUCTOR__=====================
void Tree_a_constructor(struct Tree_a* this, int number)
{
    assert(this != NULL);

    this->ID = number;
    this->size = 0;
    this->depth = 0;
    this->head = NULL;
    return;
}

//======================tree__DIFFERENCE__======================
void Tree_a_difference(struct Tree_a* this, const int* first_name,const  int* second_name)
{
    assert(this != NULL);
    assert(first_name != NULL);
    assert(second_name != NULL);

    struct Tree_a_item* frst_item = Tree_a_find(this, first_name);
    struct Tree_a_item* scnd_item = Tree_a_find(this, second_name);

    if(frst_item == NULL)
    {
        printf(RED"NO SUCH ITEM: "RESET);
        printline(first_name);
        printf("\n");
        return;
    }
    if(scnd_item == NULL)
    {
        printf(RED"NO SUCH ITEM: "RESET);
        printline(second_name);
        printf("\n");
        return;
    }

    struct Tree_a_item** fir_a = (struct Tree_a_item**) calloc(this->depth + 1, sizeof(struct Tree_a_item*));
    struct Tree_a_item** sec_a = (struct Tree_a_item**) calloc(this->depth + 1, sizeof(struct Tree_a_item*));

    struct Tree_a_item** fir_p = fir_a;
    struct Tree_a_item** sec_p = sec_a;

    Tree_a_item_path(frst_item, &fir_p);
    Tree_a_item_path(scnd_item, &sec_p);

    int i = 0;
    while(fir_a[i] == sec_a[i] && fir_a[i] != NULL)
        i++;
    i--;

    printline(frst_item->name);
    printf(" is ");
    if(fir_a[i]->left == fir_a[i + 1])
        printf("not ");
    printline(fir_a[i]->name);

    printf(", but ");
    printline(scnd_item->name);
    printf(" is");
    if(fir_a[i]->right == fir_a[i + 1])
        printf(" not");
    printf("\n");

    free(fir_a);
    free(sec_a);

    return;
}





//======================item__UNCHECK__=========================
void Tree_a_item_uncheck(struct Tree_a_item* this)
{
    if(this == NULL)
        return;

    this->checked = UNCHECKED;
    Tree_a_item_uncheck(this->left);
    Tree_a_item_uncheck(this->right);
    return;
}

//======================tree__UNCHECK__=========================
void Tree_a_uncheck(struct Tree_a* this)
{
    assert(this != NULL);

    Tree_a_item_uncheck(this->head);
    return;
}

//**************

//======================item__OK__==============================
int Tree_a_item_OK(struct Tree_a_item* this, int* size)
{
    if(this == NULL)
        return OK;

    if(this->checked == CHECKED)
        return ERR_LOOP;

    if(this->name == NULL)
        return ERR_NAME;

    if(this->left == this->right && this->left != NULL)
        return ERR_POINTER;

    this->checked = CHECKED;
    ++*size;

    int error = Tree_a_item_OK(this->left, size);
    error = Tree_a_item_OK(this->right, size);

    return error;
}

//======================tree__OK__==============================
int Tree_a_OK(struct Tree_a* this)
{
    assert(this != NULL);

    if(this->head == NULL)
        return (this->size == 0) ? OK : ERR_SIZE;

    int cur_size = 0;

    int error = Tree_a_item_OK(this->head, &cur_size);
    Tree_a_uncheck(this);

    if(cur_size != this->size)
        return ERR_SIZE;

    return error;
}

//**************

//======================item__DUMP__============================
void Tree_a_item_dump(struct Tree_a_item* this, int num_of_tabs)
{
    if(this == NULL)
    {
        printtabs(num_of_tabs);
        printf(BLUE"nil"RESET"\n");
        return;
    }

    printtabs(num_of_tabs);

    if(this->right == NULL)
        printf(RED);
    else
        printf(BLUE);
    printline(this->name);
    printf(RESET"\n");

    if(this->right == NULL)
        return;

    // RIGHT

    printtabs(num_of_tabs);
    printf("right: {\n");

    Tree_a_item_dump(this->right, num_of_tabs + 1);

    printtabs(num_of_tabs);
    printf("}\n");

    // LEFT

    printtabs(num_of_tabs);
    printf("left: {\n");

    Tree_a_item_dump(this->left, num_of_tabs + 1);

    printtabs(num_of_tabs);
    printf("}\n");
    return;
}

//======================tree__DUMP__============================
void Tree_a_dump(struct Tree_a* this)
{
    assert(this != NULL);

    printf("Tree #%d\n", this->ID);
    printf("{\nsize = %d\ndepth = %d\n", this->size, this->depth);
    Tree_a_item_dump(this->head, 1);
    printf("}\n");
    return;
}

//**************

//======================item__GRAPH__===========================
void Tree_a_item_graph_edge(FILE* outfile, struct Tree_a_item* this, int* cur_num)
{
    assert(outfile != NULL);

    if(this == NULL)
        return;

    int item_num = *cur_num;
    ++*cur_num;

    fprintf(outfile, "%d [label = \"", item_num);
    fprintline(outfile, this->name);
    fprintf(outfile, "\"]\n");

    if(this->right == NULL)
        return;

    fprintf(outfile, "%d -> %d [color = \"red\" penwidth = 2.0 label = \"NO\"];\n", item_num, *cur_num);
    Tree_a_item_graph_edge(outfile, this->left, cur_num);

    fprintf(outfile, "%d -> %d [color = \"green\" penwidth = 2.0 label = \"YES\"];\n", item_num, *cur_num);
    Tree_a_item_graph_edge(outfile, this->right, cur_num);
    return;
}

//======================tree__GRAPH__===========================
int Tree_a_make_graph(struct Tree_a* this)
{
    assert(this != NULL);

    if(Tree_a_OK(this))
        return Tree_a_OK(this);

    printf(RED"WARNING"RESET": If Russian words are used in the tree, node names may be cursed\n");
    printf("Making graph...");

    char outfilename[MAX_STR_LEN] = "";
    sprintf(outfilename, "graphs/tree_a_graph_%d.dot", this->ID);
    FILE* outfile = fopen(outfilename, "w");
    if(outfile == NULL)
    {
        printf("\t["RED"FAILED"RESET"]\n");
        printf(RED"\tFOLDER 'graphs' DOES NOT EXIST IN THE 'main.c' DIRECTORY\n"RESET);
        return ERR_FILE;
    }

    fprintf(outfile, "digraph tree_a_graph_%d\n"
                      "{\n"
                      "rankdir = TB;\n"
                      "node [shape = Mrecord];\n"
                      "nodesep = 1.5;\n", this->ID);

    int cur_num = 0;
    Tree_a_item_graph_edge(outfile, this->head, &cur_num);

    fprintf(outfile, "}\n");

    fclose(outfile);
    printf("\t[  "GREEN"OK"RESET"  ]\n");
    printf("Wrote graph data in \"%s\"\n", outfilename);

    return Tree_a_OK(this);
}

//**************

//======================item__SEARCH__==========================
struct Tree_a_item* Tree_a_item_search(struct Tree_a_item* this, const int* name)
{
    assert(name != NULL);

    if(this == NULL)
        return NULL;

    if(this->right == NULL)
    {
        if(!linecomp(name, this->name))
            return this;
        else return NULL;
    }

    struct Tree_a_item* p = NULL;

    p = Tree_a_item_search(this->right, name);
    if(p)
        return p;

    p = Tree_a_item_search(this->left, name);
    if(p)
        return p;

    return NULL;
}

//======================tree__FIND__============================
struct Tree_a_item* Tree_a_find(struct Tree_a* this, const int* name)
{
    assert(this != NULL);
    assert(name != NULL);

    return Tree_a_item_search(this->head, name);
}

//**************

//======================item__SAVE__============================
void Tree_a_item_save(FILE* outfile, struct Tree_a_item* this, int num_of_tabs)
{
    assert(outfile != NULL);

    if(this == NULL)
        return;

    fprinttabs(outfile, num_of_tabs);
    fprintline(outfile, this->name);
    fprintf(outfile, "\n");

    // LEFT

    fprinttabs(outfile, num_of_tabs);
    fprintf(outfile, "{\n");

    Tree_a_item_save(outfile, this->right, num_of_tabs + 1);

    fprinttabs(outfile, num_of_tabs);
    fprintf(outfile, "}\n");

    // RIGHT

    fprinttabs(outfile, num_of_tabs);
    fprintf(outfile, "{\n");

    Tree_a_item_save(outfile, this->left, num_of_tabs + 1);

    fprinttabs(outfile, num_of_tabs);
    fprintf(outfile, "}\n");
    return;
}

//======================tree__SAVE__============================
void Tree_a_save(struct Tree_a* this)
{
    assert(this != NULL);

    printf("Saving data...");

    char outfilename[MAX_STR_LEN] = "";
    sprintf(outfilename, "saves/tree_a_save_%d.txt", this->ID);
    FILE* outfile = fopen(outfilename, "w");
    if(outfile == NULL)
    {
        printf(RED"\tFOLDER 'saves' DOES NOT EXIST IN THE 'main.c' DIRECTORY\n"RESET);
        return;
    }
    Tree_a_item_save(outfile, this->head, 0);
    fclose(outfile);

    printf("\t[  "GREEN"OK"RESET"  ]\n");
    printf("Saved to \"%s\"\n", outfilename);
    return;
}

//**************

//======================item__LOAD__============================
struct Tree_a_item* Tree_a_item_load(FILE* infile, struct Tree_a* this, int cur_depth)
{
    assert(infile != NULL);
    assert(this != NULL);

    int line[MAX_STR_LEN] = {};
    int c = 0;

    while(isspace(c = getc(infile)));
    ungetc(c, infile);

    if(c == (int) '}' || c == EOF)
        return NULL;

    freadline(infile, line);

    struct Tree_a_item* new_item = (struct Tree_a_item*) malloc(sizeof(struct Tree_a_item));
    linecopy(new_item->name, line);
    new_item->right = NULL;
    new_item->left = NULL;
    this->size++;
    cur_depth++;
    if(cur_depth > this->depth)
        this->depth = cur_depth;

    while(isspace(c = getc(infile)));
    new_item->right = Tree_a_item_load(infile, this, cur_depth);
    if(new_item->right != NULL)
        new_item->right->parent = new_item;
    while(isspace(c = getc(infile)));

    while(isspace(c = getc(infile)));
    new_item->left = Tree_a_item_load(infile, this, cur_depth);
    if(new_item->left != NULL)
        new_item->left->parent = new_item;
    while(isspace(c = getc(infile)));

    return new_item;
}

//======================tree__LOAD__============================
int Tree_a_load(struct Tree_a* this)
{
    assert(this != NULL);

    if(Tree_a_OK(this))
        return Tree_a_OK(this);

    if(this->size != 0)
    {
        char s[MAX_STR_LEN] = "";
        printf("Are you sure to load data? All unsaved data will be deleted ("GREEN"yes"RESET"/"RED"no"RESET", "GREEN"y"RESET"/"RED"n"RESET")\n==>\t"BLUE);
        scanf("%s", s);

        int patience = PATIENCE_LVL;
        while(patience-- && strcmp(s, "yes") && strcmp(s, "no") && strcmp(s, "y") && strcmp(s, "n"))
        {
            printf(RESET"\nEnter correct answer("GREEN"yes"RESET"/"RED"no"RESET", "GREEN"y"RESET"/"RED"n"RESET"):\n"RESET"==>\t"BLUE);
            scanf("%s", s);
        }
        printf(RESET);

        if(!strcmp(s, "no") || !strcmp(s, "n"))
            return Tree_a_OK(this);
        else if(!strcmp(s, "yes") || !strcmp(s, "y"))
            ;
        else
            printf("Program decided to ruin your data\n");
    }

    int id = this->ID;
    Tree_a_destructor(this);
    Tree_a_constructor(this, id);

    printf("Loading data...");

    char infilename[MAX_STR_LEN] = "";
    sprintf(infilename, "saves/tree_a_save_%d.txt", this->ID);
    FILE* infile = fopen(infilename, "r");
    if(infile == NULL)
    {
        printf("\t["RED"FAILED"RESET"]\n");
        printf(RED"\tFOLDER 'saves' DOES NOT EXIST IN THE 'main.c' DIRECTORY\n");
        printf("\tOR THERE IS NO SUCH FILE IN THE FOLDER"RESET": %s\n", infilename);
        return ERR_FILE;
    }

    this->head = Tree_a_item_load(infile, this, 0);

    if(this->head != NULL)
        this->head->parent = NULL;

    fclose(infile);
    printf("\t[  "GREEN"OK"RESET"  ]\n");
    printf("Loaded from \"%s\"\n", infilename);

    return Tree_a_OK(this);
}

//**************

//======================item__SET__=============================
int Tree_a_item_set(struct Tree_a* tree, struct Tree_a_item* this, int cur_depth)
{
    assert(this != NULL);

    if(Tree_a_OK(tree))
        return Tree_a_OK(tree);

    char s[MAX_STR_LEN] = "";
    int new_name[MAX_STR_LEN];
    printf("Is it ");
    printline(this->name);
    printf("? ("GREEN"yes"RESET"/"RED"no"RESET", "GREEN"y"RESET"/"RED"n"RESET")\n==>\t"BLUE);
    scanf("%s", s);

    int patience = PATIENCE_LVL;
    while(patience-- && strcmp(s, "yes") && strcmp(s, "no") && strcmp(s, "y") && strcmp(s, "n"))
    {
        printf(RESET"\nEnter correct answer ("GREEN"yes"RESET"/"RED"no"RESET", "GREEN"y"RESET"/"RED"n"RESET"):\n==>\t"BLUE);
        scanf("%s", s);
    }
    printf(RESET);

    if(!strcmp(s, "yes") || !strcmp(s, "y"))
    {
        if(this->right == NULL)
            printf("This object already exists\n");
        else
            Tree_a_item_set(tree, this->right, cur_depth + 1);
    }
    else if(!strcmp(s, "no") || !strcmp(s, "n"))
    {
        if(this->left == NULL)
        {
            printf("What is this?\n==>\t"BLUE);
            readline(new_name);
            printf(RESET);

            this->right = (struct Tree_a_item*) malloc(sizeof(struct Tree_a_item));
            linecopy(this->right->name, new_name);
            this->right->right = NULL;
            this->right->left = NULL;
            this->right->parent = this;


            this->left = (struct Tree_a_item*) malloc(sizeof(struct Tree_a_item));
            linecopy(this->left->name, this->name);
            this->right->right = NULL;
            this->right->left = NULL;
            this->right->parent = this;

            printf("State the difference with ");
            printline(this->left->name);
            printf(":\n==>\t"BLUE);
            readline(this->name);
            printf(RESET);

            tree->size += 2;
            cur_depth += 1;
            if(cur_depth > tree->depth)
                tree->depth = cur_depth;
        }
        else
            Tree_a_item_set(tree, this->left, cur_depth + 1);
    }
    else
    {
        printf(RED"TOO MANY ANSWERS FAILURES\n"RESET);
        return ERR_DUMB_USER;
    }

    return Tree_a_OK(tree);
}

//======================tree__ADD__=============================
void Tree_a_add(struct Tree_a* this)
{
    assert(this != NULL);

    if(this->head == NULL)
    {
        int new_name[MAX_STR_LEN];

        printf("There is no root object. Please, state the one:\n==>\t"BLUE);
        readline(new_name);
        printf(RESET);

        this->head = (struct Tree_a_item*) malloc(sizeof(struct Tree_a_item));
        linecopy(this->head->name, new_name);
        this->size = 1;
        this->depth = 1;
    }

    int cur_size = this->size;
    int error = Tree_a_item_set(this, this->head, 1);
    if(error)
    {
        printf(RED"FAILED TO ADD NEW OBJECT\n"RESET);
        return;
    }

    if(this->size == cur_size)
        return;

    printf("\n");

    char s[MAX_STR_LEN] = "";
    printf("Successfully added new object\n");
    printf("Save to file? ("GREEN"yes"RESET"/"RED"no"RESET", "GREEN"y"RESET"/"RED"n"RESET")\n==>\t"BLUE);
    scanf("%s", s);

    int patience = PATIENCE_LVL;
    while(patience-- && strcmp(s, "yes") && strcmp(s, "no") && strcmp(s, "y") && strcmp(s, "n"))
    {
        printf(RESET"\nEnter correct answer("GREEN"yes"RESET"/"RED"no"RESET", "GREEN"y"RESET"/"RED"n"RESET"):\n"RESET"==>\t"BLUE);
        scanf("%s", s);
    }
    printf(RESET);

    if(!strcmp(s, "yes") || !strcmp(s, "y"))
        Tree_a_save(this);
    else if(!strcmp(s, "no") || !strcmp(s, "n"))
        return;
    else
        printf(RED"COULD NOT DETERMINE WHAT TO DO\n"RESET);

    return;
}

//**************

//======================item__DELETE__==========================
void Tree_a_item_delete(struct Tree_a_item* this)
{
    if(this == NULL)
        return;

    Tree_a_item_delete(this->left);
    free(this->left);

    Tree_a_item_delete(this->right);
    free(this->right);
    return;
}

//======================tree__DESTRUCTOR__======================
void Tree_a_destructor(struct Tree_a* this)
{
    assert(this != NULL);

    Tree_a_item_delete(this->head);
    free(this->head);
    this->head = NULL;
    return;
}

