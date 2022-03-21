#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int value;
    struct Node *next;
}Node;

typedef struct Linked_list{
    struct Node *head, *tail;
}Linked_list;

void Linked_list_start(Linked_list *list){
    list->head = (Node*)malloc(sizeof(Node*));
    list->head->next = NULL;
    list->tail = list->head;
}

void Linked_list_print(Linked_list *list){
    Node* curr_node = list->head->next;
    int i=0;
    printf("Linked List:\n");
    while(curr_node != list->tail->next){
        printf("[%d]: %d\n",i,curr_node->value);
        curr_node = curr_node->next;
        i++;
    }
}
void Linked_list_add(Linked_list* list, Node node){
  Node *new_node = malloc(sizeof(Node));
	new_node->value = node.value;
	new_node->next = NULL;
	list->tail->next = new_node;
	list->tail = list->tail->next;
}
void Linked_list_invert(Linked_list* list){
    Node *curr=list->head->next, *right=list->head->next->next;
    printf("c %d r %d\n",curr->value,right->value);
    
    curr->next = NULL;
    Node *saved_right_next = right->next;
    right->next=curr;
    
    curr=right;
    right=saved_right_next;
    
    while(curr!=list->tail){
        saved_right_next = right->next;
        right->next = curr;
        
        curr = right;
        right = saved_right_next;
    }
    Node *saved_head_next = list->head->next;; 
    list->head->next = curr;
    list->tail = saved_head_next;

    printf("h %d t %d\n",list->head->next->value,list->tail->value);
}
int main(){
    Linked_list list; Linked_list_start(&list);
    
    int values[] = {10,11,12,13,14,15,16,17,18,19};
    
    for(int i=0; i<10; i++){ // adding to the linked list 
        Node temp;
        temp.value = values[i];

        Linked_list_add(&list,temp);
    }
    Linked_list_print(&list);
    Linked_list_invert(&list);
    Linked_list_print(&list);

    return 0;
}
