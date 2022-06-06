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
typedef struct node_t{
    
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
typedef struct list_t {
    
    node_t* headPtr;
    int itemCount;
} list_t;

/** function to allocates memory for an empty list_t struct
 * @return ptr to list_t
 */
list_t* create_empty_list();

/** prints contents of list
 */
void printList(list_t * list);

/** function to add the contents of the string ptr elem to the end
 *  of the list
 */
void add(list_t* list, char* elem);

/** function to adds the contents of the string ptr elem to the ith 
 *  position in the list
 */
void add_at(list_t* list, char* elem, int i);

/** function to removes a node from the list at position i. 
 *  Also frees dynmaically allocated nodes on removal
 *
 *  @return Null if i out of range, node -> string otherwise
 */
char* remove_at(list_t* list, int i);

/** function that returns node -> string at index i.
 * 
 *  @return node -> string at index i
 */
char* get(list_t* list, int i);

/** function that returns the size of the list
 *  @return size of the list
 */
int size(list_t* list);

/** function to clear the contents of the list
 *  also frees memory of all the nodes in the list.
 */
void clear(list_t* list);

/** function to free the memory of the list
 */ 
void destroy_empty_list(list_t* list);

#endif