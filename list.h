/** @file list.h
 * Header for for the singly linked list and node struct
 */

#ifndef LIST_
#define LIST_

/** creates a struct node_t
 *
 * Members:
 *  string : pointer string
 *  node_t : pointer to next node
 *
 */
typedef struct node_t
{
    char *string;
    struct node_t *next;
} node_t;

/** creates a struct list_t
 *
 * Members:
 *  headPtr : pointer to the head of the linked list
 *  itemCount : total amount of items in the list;
 *
 */
typedef struct list_t
{
    node_t *headPtr;
    int itemCount;
} list_t;

/** function to allocates memory for an empty list_t struct
 * @return ptr to list_t, returns null if error with malloc
 */
list_t *list_create();

/** prints contents of list
 */
void list_print(list_t *list);

/** function to list_add the contents of the string ptr elem to the end
 *  of the list
 *
 * @return 0 if list_add successfull, 1 if there was an error allocating memory with malloc
 */
int list_add(list_t *list, char *elem);

/** function to adds the contents of the string ptr elem to the ith
 *  position in the list
 *
 * @return 0 if list_add successfull, 1 if index i is out of range, and 2 if error with malloc
 */
int list_add_at(list_t *list, char *elem, int i);

/** function to removes a node from the list at position i.
 *  Also frees dynmaically allocated nodes on removal
 *
 *  @return Null if i out of range, node -> string otherwise
 */
char *list_remove_at(list_t *list, int i);

/** function that returns node -> string at index i.
 *
 *  @return node -> string at index i. Null if index i out of range
 */
char *list_get(list_t *list, int i);

/** function that returns the size of the list
 *  @return size of the list
 */
int list_size(list_t *list);

/** function to clear the contents of the list
 *  also frees memory of all the nodes in the list.
 */
void list_clear(list_t *list);

/** function to free the memory of the list
 */
void list_destroy(list_t *list);

#endif