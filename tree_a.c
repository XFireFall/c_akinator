#include "tree_a.h"

void linecopy(int* s, int* t)
{
    assert(t != NULL);
    assert(s != NULL);
    assert(s != t);

    for( ; *t != 0; s++, t++)
        *s = *t;
    *s = 0;
    return;
}

int linestrcopy(int* line, char* s)
{
    int i = 0;
    for( ; s[i] != '\0'; i++)
        line[i] = (int) s[i];
    line[i] = 0;
    return 0;
}

int readline(int* line)
{
    int c = 1;
    while((c = getchar()) == (int) '\n')
        ;
    ungetc(c, stdin);
    while((c = getchar()) != (int) '\n')
        *line++ = c;
    *line = 0;

    return 0;
}

int freadline(FILE* infile, int* line)
{
    int c = 0;
    while((c = getc(infile)) != (int) '\n')
        *line++ = c;
    *line = 0;

    return 0;
}

int fprintline(FILE* outfile, int* line)
{
    assert(line != NULL);

    while(*line)
        fprintf(outfile, "%c", (char) *line++);
    return 0;
}

void fprinttabs(FILE* outfile, int num)
{
    for(int i = 0; i < num; i++)
        fprintf(outfile, "\t");
    return;
}





void Tree_a_item_dump(FILE* outfile, struct Tree_a_item* this, int num_of_tabs)
{
    if(this == NULL)
        return;

    //printline(this->name);

    fprinttabs(outfile, num_of_tabs);
    fprintline(outfile, this->name);
    fprintf(outfile, "\n");

    fprinttabs(outfile, num_of_tabs);
    fprintf(outfile, "{\n");

    //fprinttabs(outfile, num_of_tabs);
    Tree_a_item_dump(outfile, this->right, num_of_tabs + 1);

    fprinttabs(outfile, num_of_tabs);
    fprintf(outfile, "}\n");


    fprinttabs(outfile, num_of_tabs);
    fprintf(outfile, "{\n");

    //fprinttabs(outfile, num_of_tabs);
    Tree_a_item_dump(outfile, this->left, num_of_tabs + 1);

    fprinttabs(outfile, num_of_tabs);
    fprintf(outfile, "}\n");
    return;
}

int Tree_a_item_set(struct Tree_a_item* this)
{
    if(this == NULL)
        return 1;

    char s[MAX_STR_LEN] = "";
    int new_name[MAX_STR_LEN];
    printline(this->name);
    printf("?\n\t");
    scanf("%s", s);

    if(!strcmp(s, "yes"))
    {
        if(this->right == NULL)
            printf("hell yeah\n");
        else
            Tree_a_item_set(this->right);
    }
    else if(!strcmp(s, "no"))
    {
        if(this->left == NULL)
        {
            printf("What is this?\n\t");
            readline(new_name);

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

            printf("State the difference:\n\t");
            readline(this->name);
        }
        else
            Tree_a_item_set(this->left);
    }
    else
        printf("idk what you mean\n");
    return 0;
}

struct Tree_a_item* Tree_a_item_load(FILE* infile)
{
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

    while(isspace(c = getc(infile)));
    new_item->right = Tree_a_item_load(infile);
    if(new_item->right != NULL)
        new_item->right->parent = new_item;
    while(isspace(c = getc(infile)));

    while(isspace(c = getc(infile)));
    new_item->left = Tree_a_item_load(infile);
    if(new_item->left != NULL)
        new_item->left->parent = new_item;
    while(isspace(c = getc(infile)));

    return new_item;
}

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






void Tree_a_dump(struct Tree_a* this)
{
    FILE* outfile = fopen("akinator_data.txt", "w");
    Tree_a_item_dump(outfile, this->head, 0);
    fclose(outfile);
    return;
}

void Tree_a_add(struct Tree_a* this)
{
    if(Tree_a_item_set(this->head))
    {
        int new_name[MAX_STR_LEN];
        readline(new_name);
        this->head = (struct Tree_a_item*) malloc(sizeof(struct Tree_a_item));
        linecopy(this->head->name, new_name);
    }
    return;
}

void Tree_a_load(struct Tree_a* this)
{
    FILE* infile = fopen("akinator_data.txt", "r");
    this->head = Tree_a_item_load(infile);
    if(this->head != NULL)
        this->head->parent = NULL;
    fclose(infile);
    return;
}

void Tree_a_destructor(struct Tree_a* this)
{
    Tree_a_item_delete(this->head);
    free(this->head);
    this->head = NULL;
    return;
}


/* NEW! */

struct Tree_a_item* Tree_a_item_search(struct Tree_a_item* this, int* name)
{
    if(this == NULL)
        return NULL;

    /*printf("...");
    printline(this->name);
    printf("\n");*/

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

struct Tree_a_item* Tree_a_find(struct Tree_a* this, int* name)
{
    return Tree_a_item_search(this->head, name);
}

void Tree_a_item_info(struct Tree_a_item* this)
{
    printf("information about ");
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

void Tree_a_item_path(struct Tree_a_item* this, struct Tree_a_item*** arr)
{
    if(this == NULL)
        return;
    if(this->parent == NULL)
        return;
    Tree_a_item_path(this->parent, arr);
    **arr = this->parent;
    printf("%p\n", **arr);
    (*arr)++;
    return;
}

int linecomp2(int* a, int* b)
{
    for( ; *a == *b && *a != 0; a++, b++)
        ;
    return *a - *b;
}

void Tree_a_difference(struct Tree_a* this, int* first, int* second)
{
    struct Tree_a_item* frst = Tree_a_find(this, first);
    struct Tree_a_item* scnd = Tree_a_find(this, second);

    if(frst == NULL || scnd == NULL)
    {
        printf("no such items\n");
        return;
    }

    struct Tree_a_item* path_frst[100] = {};
    struct Tree_a_item* path_scnd[100] = {};

    struct Tree_a_item** fir = path_frst;
    struct Tree_a_item** sec = path_scnd;

    Tree_a_item_path(frst, &fir);
    Tree_a_item_path(scnd, &sec);

    int i = 0;
    while(path_frst[i + 1] == path_scnd[i + 1] && path_frst[i + 1] != NULL)
        i++;

    printline(first);
    printf(" is not ");
    printline(path_scnd[i]->name);
    printf(", but ");
    printline(second);
    printf(" is\n");



    /*for(int i = 0; i < 10; i++)
    {
        if(path_frst[i] != NULL)
            printline(path_frst[i]->name);
        else
            printf("null");
        printf("\n");
    }*/

    printf("___");

    return;
}

