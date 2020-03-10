/* Example code for Exercises in C.

Based on an example from http://www.learn-c.org/en/Linked_lists

Copyright 2016 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node *next;
} Node;


/* Makes a new node structure.
*
* val: value to store in the node.
* next: pointer to the next node
*
* returns: pointer to a new node
*/
Node *make_node(int val, Node *next) {
    Node *node = malloc(sizeof(Node));
	node->val = val;
    node->next = next;
    return node;
}


/* Prints the values in a list.
*
* list: pointer to pointer to Node
*/
void print_list(Node **list) {
    Node *current = *list;

    printf("[ ");
    while (current != NULL) {
        printf("%d ", current->val);
        current = current->next;
    }
    printf("]\n");
}


/* Removes and returns the first element of a list.
*
* list: pointer to pointer to Node
*
* returns: int or -1 if the list is empty
*/
int pop(Node **list) {
	Node * head = *list;
	if (head == NULL) {
		return -1;
	}
	*list = head->next;
	return head->val;
}


/* Adds a new element to the beginning of the list.
*
* list: pointer to pointer to Node
* val: value to add
*/
void push(Node **list, int val) {
	Node *head = *list;
	Node *new_node = make_node(val, head);
	*list = new_node;
}


/* Removes the first element with the given value
*
* Frees the removed node.
*
* list: pointer to pointer to Node
* val: value to remove
*
* returns: number of nodes removed
*/
int remove_by_value(Node **list, int val) {
	Node *current = *list;
	while (current->next != NULL && current->next->val != val) {
		current = current->next;
	}
	// Now current will either be last node or the node before the node with the val we want to free
	
	if (current->next == NULL) {
		return 0;
	}

	if (current->next->next == NULL) {
		free(current->next);
		current->next == NULL;
		return 1;
	} else {
		Node *new_next = current->next->next;
		free(current->next);
		current->next = new_next;
		return 1;
	}
}


/* Reverses the elements of the list.
*
* Does not allocate or free nodes.
*
* list: pointer to pointer to Node
*/
void reverse(Node **list) {
	Node *current = *list;
	Node *next_node = NULL;
	Node *prev_node = NULL;
	while (current != NULL) {
		next_node = current->next;
		current->next = prev_node;
		prev_node = current;
		current = next_node;
	}
	*list = prev_node;
}


int main() {
    Node *head = make_node(1, NULL);
    head->next = make_node(2, NULL);
    head->next->next = make_node(3, NULL);
    head->next->next->next = make_node(4, NULL);

    Node **list = &head;
    print_list(list);

    int retval = pop(list);
    print_list(list);

    push(list, retval+10);
    print_list(list);

    print_list(list);

    print_list(list);

    reverse(list);
    print_list(list);
}
