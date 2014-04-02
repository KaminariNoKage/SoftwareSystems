/* Example code for Software Systems at Olin College.

Based on an example from http://www.learn-c.org/en/Linked_lists

Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node * next;
} Node;

Node *make_node(int val, Node *next) {
    Node *node = malloc(sizeof(Node));
    node->val = val;
    node->next = next;
    return node;
}

void print_list(Node *head) {
    Node *current = head;

    while (current != NULL) {
        printf("%d\n", current->val);
        current = current->next;
    }
}

int pop(Node **head) {
    int retval;
    Node *next_node;

    if (*head == NULL) {
        return -1;
    }

    next_node = (*head)->next;
    retval = (*head)->val;
    free(*head);
    *head = next_node;

    return retval;
}

// Add a new element to the beginning of the list.
void push(Node **head, int val) {
    Node *nuNode = make_node(val, *head);
    *head = nuNode;
}

// Remove the first element with the given value; return the number
// of nodes removed.
int remove_by_value(Node **head, int val) {
    int n = 0;
    Node *cur = *head;
    Node *prev;
    //Check head of current list
    while (cur->next != NULL){
        //Check first of the list
        if (cur->val == val){
            pop(head);
            n++;
        }
        else {
            //Else get the next element
            prev = cur;
            cur = cur->next;
            if (cur->val == val){
                //If the values match out, then set previous to current's next
                prev->next = cur->next;
                n++;
            }
            //If they don't match out, continue on
        }
        cur = cur->next;
    }

    return n;
}

// Reverse the elements of the list without allocating new nodes.
void reverse(Node **head) {
    // FILL THIS IN!
}


int main() {
    Node *test_list = make_node(1, NULL);
    test_list->next = make_node(2, NULL);
    test_list->next->next = make_node(3, NULL);
    test_list->next->next->next = make_node(4, NULL);

    int retval = pop(&test_list);
    push(&test_list, retval+10);

    remove_by_value(&test_list, 3);
    remove_by_value(&test_list, 7);

    reverse(&test_list);

    print_list(test_list);
}
