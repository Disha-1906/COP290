#ifndef LIST_H
#define LIST_H
#include<stdlib.h>
struct list {
	struct listentry* head;
	struct listentry* tail;
};

struct listentry {
	void *data;
	struct listentry *prev;
	struct listentry *next;
};

// Remove an item from the list
void list_rm(struct list* l, struct listentry* e){
	struct listentry* p = l->head;
	struct listentry* q = p->next;
	if(p==e){
		l->head=q;
		free(p);
		return;
	}
	else{
	while(q != NULL){
		if(p == e){
			p->prev->next = q;
			q->prev = p->prev;
			free(p);
			return;
		}
	}
	if(p==e){
		l->tail= p->prev;
		free(p);
		return;
	}
	}
}   

// Add an item to the list
struct listentry* list_add(struct list* l, void* data){
	struct listentry* p = (struct listentry* )malloc(sizeof(struct listentry));

	p->prev = l->tail;
	p->next = NULL;
	p->data = data;
	if (l->tail){
	l->tail->next = p;}
	l->tail = p;
	if(!l->head){
	l->head = p;}
	return p;
	
}

// Return an initialized list
struct list* list_new(){
	struct list* new_list = (struct list*)malloc(sizeof(struct list));
	new_list->head = NULL;
	new_list->tail = NULL;
	return new_list;
} 

// Check if list is empty or not
int is_empty(struct list* l){
	if(l->head == NULL){
		return 1;
	}
	else{
		return 0;
	}
}

#endif
