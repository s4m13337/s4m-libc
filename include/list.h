#ifndef LIST_H
#define LIST_H

typedef struct ListNode {
  char* data;
  struct ListNode* next;
} ListNode;

ListNode* list_node_create(char* data);
ListNode* list_create(char* data);
int list_append(ListNode* head, char* data);
size_t list_length(ListNode* head);
int list_free(ListNode* head);

#endif
