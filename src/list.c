#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "list.h"

ListNode* list_node_create(char* data){
  ListNode* new_node = malloc(sizeof(ListNode));
  if(new_node == NULL){
    perror("Failed creating list node");
    return NULL;
  }

  new_node->data = strdup(data);
  new_node->next = NULL;
  return new_node;
}

// Alias function for creating list --- just a convenient name
ListNode* list_create(char* data){
  ListNode* new_list = list_node_create(data);
  if(new_list == NULL){
    perror("Failed creating list");
    return NULL;
  }
  return new_list;
}

int list_append(ListNode* head, char* data){
  ListNode* new_node = list_create(data);

  new_node->data = strdup(data);
  new_node->next = NULL;

  ListNode* current_node = head;
  while(current_node->next != NULL)
    current_node = current_node->next;
  current_node->next = new_node;
  return 0;
}

size_t list_length(ListNode* head){
  ListNode* current_node = head;
  size_t n=0;
  while(current_node != NULL){
    n++;
    current_node = current_node->next;
  }
  return n;
}

int list_free(ListNode* head){
  ListNode* current_node = head;
  while(current_node != NULL){
    ListNode* next_node = current_node->next;
    free(current_node->data);
    free(current_node);
    current_node = next_node;
  }
  return 0;
}
