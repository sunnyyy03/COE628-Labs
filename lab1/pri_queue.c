#include <stdlib.h>
#include <stdio.h>
#include "pri_queue.h"
/** @file pri_queue.c */
static Node_ptr_t head = NULL;
/**
 * Insert a Node into a priority queue.
 * @param priority
 * @param data
 * @author Sanchit Das
 */

void PQ_insert(int priority, char * data) {
    Node_ptr_t new_node = (Node_ptr_t)malloc(sizeof(Node_t));
    new_node->priority = priority;
    new_node->data = data;
    if (!head) {
        head = new_node;
        new_node->next = NULL;
    } else {
        Node_ptr_t* prev = &head;
        Node_ptr_t curr = head;
        while (curr && curr->priority > new_node->priority) {
            prev = &curr->next;
            curr = curr->next;
        }
        *prev = new_node;
        new_node->next = curr;
    }
}
/**
 * Delete and return the node with the highest priority.
 * @return The highest priority Node.
 */
Node_ptr_t PQ_delete() {
    Node_t* tmp;
    if(head){
        tmp = head;
        head = head->next;
        return tmp;
    } else {
        return NULL;
    }
}

/**
 * Do NOT modify this function.
 * @return A pointer to the head of the list.  (NULL if list is empty.)
 */
Node_ptr_t PQ_get_head() {
    return head;
}

/**
 * Do NOT modify this function.
 * @return the number of items in the queue
 */
int PQ_get_size() {
    int size = 0;
    Node_ptr_t tmp;
    for(tmp = head; tmp != NULL; tmp = tmp->next, size++)
        ;
    return size;
}


