#ifndef TREE_A_H_INCLUDED
#define TREE_A_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "../c_hash/lib/constants.h"
#include "../c_hash/lib/strings_int.h"

void linecopy(int* s, int* t);

int readline(int* line);

int fprintline(FILE* outfile, int* line);

int linestrcopy(int* line, char* s);

void fprinttabs(FILE* outfile, int num);

int freadline(FILE* infile, int* line);






struct Tree_a_item
{
    int name[MAX_STR_LEN];
    struct Tree_a_item* left;
    struct Tree_a_item* right;
    struct Tree_a_item* parent;
};

void Tree_a_item_dump(FILE* outfile, struct Tree_a_item* this, int num_of_tabs);

int Tree_a_item_set(struct Tree_a_item* this);

struct Tree_a_item* Tree_a_item_load(FILE* infile);

void Tree_a_item_delete(struct Tree_a_item* this);





struct Tree_a
{
    struct Tree_a_item* head;
};

void Tree_a_dump(struct Tree_a* this);

void Tree_a_add(struct Tree_a* this);

void Tree_a_load(struct Tree_a* this);

void Tree_a_destructor(struct Tree_a* this);

/* NEW! */

struct Tree_a_item* Tree_a_item_search(struct Tree_a_item* this, int* name);

struct Tree_a_item* Tree_a_find(struct Tree_a* this, int* name);

void Tree_a_item_info(struct Tree_a_item* this);

void Tree_a_difference(struct Tree_a* this, int* first, int* second);


#endif // TREE_A_H_INCLUDED
