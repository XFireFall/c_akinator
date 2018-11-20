#ifndef TREE_A_H_INCLUDED
#define TREE_A_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "constants.h"
#include "strings_int.h"

#define CHECKED   (1)
#define UNCHECKED (0)

#define PATIENCE_LVL (4) /**< number of attempts to enter an answer */

enum {
    OK,             /**< Everything is OK */
    ERR_LOOP,       /**< If some descendant is it's own ancestor */
    ERR_SIZE,       /**< If calculated size is not equal to current tree size */
    ERR_NAME,       /**< If name of some item has not been initialized yet */
    ERR_FILE,       /**< Having problems with non-existing file */
    ERR_DUMB_USER,  /**< In case the user is silly */
    ERR_POINTER     /**< Any pointer exception (example: left = right) */
    };


//==========================__LINECOPY__========================
/** \brief Copies one string (as integers array) to another
 *
 * \param s int* [in/out] - string to copy to
 * \param t const int* [in] - string to copy from
 *
 */
void linecopy(int* s, const int* t);

//==========================__LINESTRCOPY__=====================
/** \brief Copies string to string as integers array
 *
 * \param line int* [in/out] - string to copy to
 * \param s const char* [in] - string to copy from
 *
 */
void linestrcopy(int* line, const char* s);

//==========================__READLINE__========================
/** \brief Reads string (array of integers) from console
 *
 * \param line int* [in/out] - string to read to
 *
 */
void readline(int* line);

//==========================__FREADLINE__=======================
/** \brief Reads string (array of integers) from opened file
 *
 * \param infile FILE* [in] - the file to read from
 * \param line int* [in/out] - the string to read to
 *
 * \note The given file must be opened
 * \note Does not ignore 'end line' symbols
 *
 */
void freadline(FILE* infile, int* line);

//==========================__FPRINTLINE__======================
/** \brief Prints string (array of integers) into opened file
 *
 * \param outfile FILE* [in] - the file to print into
 * \param line const int* [in] - the string to print out
 *
 * \note The given file must be opened
 *
 */
void fprintline(FILE* outfile, const int* line);

//==========================__PRINTTABS__=======================
/** \brief Prints given number of '__|_' strings in console
 *
 * \param num int [in] - number of tabs to print
 *
 */
void printtabs(int num);

//==========================__FPRINTTABS__======================
/** \brief Prints given number of 'tab' symbols in opened file
 *
 * \param outfile FILE* [in] - the file to print into
 * \param num int [in] - number of tabs to print
 *
 * \note The given file must be opened
 *
 */
void fprinttabs(FILE* outfile, int num);







/** \brief
 * \param name[MAX_STR_LEN] int - name of the object
 * \param int checked - variable used only for verifying
 * \param left struct Tree_a_item* - next item to the left
 * \param right struct Tree_a_item* - next item to the right
 * \param parent struct Tree_a_item* - previous item
 *
 */
struct Tree_a_item
{
    int name[MAX_STR_LEN];
    int checked;
    struct Tree_a_item* left;
    struct Tree_a_item* right;
    struct Tree_a_item* parent;
};

//======================item__INFO__============================
/** \brief Prints full information (till the tree root) referred to given object
 *
 * \param this struct Tree_a_item* [in] - the item to give information about
 *
 */
void Tree_a_item_info(struct Tree_a_item* this);

//======================item__PATH__============================
/** \brief Initializes full path of given item, beginning from root
 *
 * \param this struct Tree_a_item* [in] - current item to initialize the path of
 * \param arr struct Tree_a_item*** [in] - POINTER on the current POSITION in ARRAY of tree items (their POINTERS, actually)
 *
 * \warning the array must have enough space to carry all the path
 *
 */
void Tree_a_item_path(struct Tree_a_item* this, struct Tree_a_item*** arr);



/** \brief
 * \param ID - ID number of the tree
 * \param size - total number of items
 * \param depth - depth of the tree-graph
 * \param head struct Tree_a_item* - root item
 *
 */
struct Tree_a
{
    int ID;
    int size;
    int depth;
    struct Tree_a_item* head;
};

//======================tree__CONSTRUCTOR__=====================
/** \brief Initializes given tree with start-up data
 *
 * \param this struct Tree_a* [in] - tree to initialize
 * \param number int [in] - new ID of the tree
 *
 */
void Tree_a_constructor(struct Tree_a* this, int number);

//======================tree__DIFFERENCE__======================
/** \brief Prints the first item in which objects' paths begin to differ
 *
 * \param this struct Tree_a* [in] - tree, in which the objects are placed
 * \param first const int* [in] - name of the first object
 * \param second const int* [in] - name of the second object
 *
 */
void Tree_a_difference(struct Tree_a* this, const int* first, const int* second);





//======================item__UNCHECK__=========================
/** \brief Sets current item's and its descendants' 'checked' to UNCHECKED
 *
 * \param this struct Tree_a_item* [in] - current item to uncheck
 *
 */
void Tree_a_item_uncheck(struct Tree_a_item* this);

//======================tree__UNCHECK__=========================
/** \brief Sets all tree's items' 'checked' to UNCHECKED
 *
 * \param this struct Tree_a* [in] - tree to uncheck
 *
 */
void Tree_a_uncheck(struct Tree_a* this);

//**************

//======================item__OK__==============================
/** \brief Tree item verification
 *
 * \param this struct Tree_a_item* [in] - item to verify
 * \param size int* [in/out] - current calculated size (used in tree verification)
 * \return int - see error cases codes
 *
 */
int Tree_a_item_OK(struct Tree_a_item* this, int* size);

//======================tree__OK__==============================
/** \brief Tree verification
 *
 * \param this struct Tree_a* [in] - tree to verify
 * \return int - see error cases codes
 *
 */
int Tree_a_OK(struct Tree_a* this);

//**************

//======================item__DUMP__============================
/** \brief Prints item and its descendants in console
 *
 * \param this struct Tree_a_item* [in] - current item to print
 * \param num_of_tabs int [in] - current horizontal indent
 *
 */
void Tree_a_item_dump(struct Tree_a_item* this, int num_of_tabs);

//======================tree__DUMP__============================
/** \brief Prints entire tree in console (may be quite big)
 *
 * \param this struct Tree_a* [in] - the tree to print
 *
 */
void Tree_a_dump(struct Tree_a* this);

//**************

//======================item__GRAPH__===========================
/** \brief Prints node-item data in opened .dot file
 *
 * \param outfile FILE* [in] - the .dot file to print to
 * \param this struct Tree_a_item* [in] - the item to print
 *
 * \note The given file must be opened
 *
 */
void Tree_a_item_graph_edge(FILE* outfile, struct Tree_a_item* this);

//======================tree__GRAPH__===========================
/** \brief Prints data for DOTTY graph in .dot file (file name depends on the tree ID)
 *
 * \param this struct Tree_a* [in] - tree to make graph on
 * \return int - see error cases codes
 *
 */
int Tree_a_make_graph(struct Tree_a* this);

//**************

//======================item__SEARCH__==========================
/** \brief Finds any object with given name among the item itself and its descendants
 *
 * \param this struct Tree_a_item* [in] - current item
 * \param name const int* [in] - name of the searched object
 * \return struct Tree_a_item* - NULL if no item found, the item if it was
 *
 */
struct Tree_a_item* Tree_a_item_search(struct Tree_a_item* this, const int* name);

//======================tree__FIND__============================
/** \brief Finds any object with given name in given tree
 *
 * \param this struct Tree_a* [in] - the tree to find the object in
 * \param name const int* [in] - name of the searched object
 * \return struct Tree_a_item* - NULL if no item found, the item if it was
 *
 */
struct Tree_a_item* Tree_a_find(struct Tree_a* this, const int* name);

//**************

//======================item__SAVE__============================
/** \brief Saves current item and its descendants to opened file
 *
 * \param outfile FILE* [in] - the file to print into
 * \param this struct Tree_a_item* [in] - current item to print
 * \param num_of_tabs int [in] - current horizontal indent
 *
 * \note The given file must be opened
 *
 */
void Tree_a_item_save(FILE* outfile, struct Tree_a_item* this, int num_of_tabs);

//======================tree__SAVE__============================
/** \brief Saves current tree data to file (file name depends on the tree ID)
 *
 * \param this struct Tree_a* [in] - the tree to be saved
 *
 */
void Tree_a_save(struct Tree_a* this);

//**************

//======================item__LOAD__============================
/** \brief Loads current item with the information from the opened file
 *
 * \param infile FILE* [in] - the file to load from
 * \param this struct Tree_a* [in] - tree that is being initialized
 * \param cur_depth int [in] - current calculated depth
 * \return struct Tree_a_item* - the initialized item that may even contain further descendants
 *
 * \note The given file must be opened
 *
 */
struct Tree_a_item* Tree_a_item_load(FILE* infile, struct Tree_a* this, int cur_depth);

//======================tree__LOAD__============================
/** \brief Loads tree data with the information from file (file name depends on the tree ID)
 *
 * \param this struct Tree_a* [in] - the tree to initialize
 * \return int - see error cases codes
 *
 */
int Tree_a_load(struct Tree_a* this);

//**************

//======================item__SET__=============================
/** \brief Game step / Adding item request
 *
 * \param tree struct Tree_a* [in] - the tree to add new item to
 * \param this struct Tree_a_item* [in] - current item
 * \param cur_depth int - current calculated depth
 * \return int - see error cases codes
 *
 */
int Tree_a_item_set(struct Tree_a* tree, struct Tree_a_item* this, int cur_depth);

//======================tree__ADD__=============================
/** \brief Game itself / Adding item process
 *
 * \param this struct Tree_a* [in] - the tree to add new item to
 *
 */
void Tree_a_add(struct Tree_a* this);

//**************

//======================item__DELETE__==========================
/** \brief Deletes current item's descendants from computer memory
 *
 * \param this struct Tree_a_item* [in] - current item to delete descendants of
 *
 */
void Tree_a_item_delete(struct Tree_a_item* this);

//======================tree__DESTRUCTOR__======================
/** \brief Destroys the tree from computer memory
 *
 * \param this struct Tree_a* [in] - the tree to destruct
 *
 */
void Tree_a_destructor(struct Tree_a* this);


#endif // TREE_A_H_INCLUDED
