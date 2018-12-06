#include <stdlib.h>
#include <stdio.h>


typedef struct node {
    int data;
    struct node *next;
} List;

List * sorted_merge(List * a, List *b);
List * merge(List * a, List *b);
void print(List * x);
void insert1(int data);
void insert2(int data);
List* revmerge(List * a, List * b);
void insertAtTail2(int data);
void insertAtTail1(int data);
void insertAtTail(int data, List** x);

List* head1 = NULL;
List* head2 = NULL;

int main(){
	
	insertAtTail(8,&head2);
	printf("%d\n",head2);
	insertAtTail2(12);
	insert2(7);
	insert2(6);
	insert2(3);
	insert2(1);
	insertAtTail2(13);
	insertAtTail(14,&head2);
	
	insertAtTail1(9);
	insert1(5);
	insert1(4);
	insert1(2);
	insert1(0);
	insert1(0);
	insert1(-1);
	insert1(-2);
	insertAtTail1(14);
	
	print(head1);
	print(head2);
	
	List * x = sorted_merge(head1,head2);
	print(x);
	
	return 0;
}

List * sorted_merge(List * a, List *b){
	List * newlist = NULL;
	while(a != NULL || b != NULL){
		if(a==NULL){
			insertAtTail(b->data,&newlist);
			b = b->next;
		}else if(b==NULL){
			insertAtTail(a->data,&newlist);
			a = a->next;
		}else if(a->data < b->data){
			insertAtTail(a->data,&newlist);
			a = a->next;
		}else if(b->data < a->data){
			insertAtTail(b->data,&newlist);
			b = b->next;
		}else if(a->data == b->data){
			insertAtTail(b->data,&newlist);
			insertAtTail(a->data,&newlist);
			a = a->next;
			b = b->next;
		}
	}
	return newlist;
}

List* merge(List * a, List * b){
	List * newlist = NULL;
	while(a != NULL){
		List * tmp = malloc(sizeof(List));
		tmp->data = a->data;
		tmp->next = newlist;
		newlist = tmp;
		a = a->next;
	}
	while(b != NULL){
		List * tmp = malloc(sizeof(List));
		tmp->data = b->data;
		tmp->next = newlist;
		newlist = tmp;
		b = b->next;
	}
	return newlist;
}

List* revmerge(List * a, List * b){
	List * tmp = NULL;
	while(a != NULL){
		insertAtTail(a->data,&tmp);
		a = a->next;
	}
	while(b != NULL){
		insertAtTail(b->data,&tmp);
		b = b->next;
	}
	return tmp;
}

void insertAtTail(int data, List** x){
	List* tmp = *x;
	if(*x == NULL){
		*x = malloc(sizeof(List));
		(*x)->next = NULL;
		(*x)->data = data;
		return;
	}
	while(tmp->next != NULL){
		tmp=tmp->next;
	}
	List* tmp2 = malloc(sizeof(List));
	tmp->next = tmp2;
	tmp2->data = data;
	tmp2->next = NULL;
}

void insertAtTail2(int data){
	List* tmp = head2;
	if(head2 == NULL){
		head2 = malloc(sizeof(List));
		head2->next = NULL;
		head2->data = data;
		return;
	}
	while(tmp->next != NULL){
		tmp=tmp->next;
	}
	List* tmp2 = malloc(sizeof(List));
	tmp->next = tmp2;
	tmp2->data = data;
	tmp2->next = NULL;
}

void insertAtTail1(int data){
	List* tmp = head1;
	if(head1 == NULL){
		head1 = malloc(sizeof(List));
		head1->next = NULL;
		head1->data = data;
		return;
	}
	while(tmp->next != NULL){
		tmp=tmp->next;
	}
	List* tmp2 = malloc(sizeof(List));
	tmp->next = tmp2;
	tmp2->data = data;
	tmp2->next = NULL;
}

void print(List * x){
	int len =0;
	printf("\nlocation: %d\n",x);
	while(x != NULL){
		printf("%d\n",x->data);
		x = x->next;
		len++;
	}
	printf("done printing, length=%d\n",len);
}

void insert1(int data){
	List *tmp = malloc(sizeof(List));
	tmp->data = data;
	tmp->next = head1;
	head1 = tmp;
}
void insert2(int data){
	List *tmp = malloc(sizeof(List));
	tmp->data = data;
	tmp->next = head2;
	head2 = tmp;
}