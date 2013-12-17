#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct node {
	int data;
	struct node* next;
};

void Push(struct node** headRef, int data) {
	struct node* newNode = malloc(sizeof(struct node));

	newNode->data = data;
	newNode->next = *headRef;
	*headRef = newNode;
}

void Append(struct node** headRef, int data) {
	struct node* current = *headRef;

	if(current == NULL) Push(&(*headRef), data);
	else {
		while(current->next != NULL)
			current = current->next;
		Push(&(current->next), data);
	}
}

int Length(struct node* head) {
	struct node* current;
	int length = 0;

	for(current = head; current != NULL; current = current->next)
		length++;

	return length;
}

struct node* BuildOneTwoThree() {
	struct node* head = NULL;
	struct node* current;

	Append(&head, 1);
	current = head;
	Append(&current, 2);
	Append(&current, 3);	

	return head;
}

struct node* GetNth(struct node* head, int n) {
	struct node* current = head;
	int i;

	for(i = 0; i < n; i++) {
		if(current->next == NULL) assert(i == n);
		current = current->next;
	}
	return current;
}

void Insert(struct node* head, int position, int data) {
	struct node* before = GetNth(head, position);
	struct node* after = before->next;
	struct node* newNode = malloc(sizeof(struct node));

	Push(&(before->next), data);
}

void TraverseList(struct node* head) {
	struct node* current;
	int i;

	for(current = head; current != NULL; current = current->next)
		printf("%d\n", current->data);
}

int Count(struct node* head, int searchFor) {
	struct node* current;
	int count = 0;

	for(current = head; current != NULL; current = current->next)
		if(current->data == searchFor) count++;

	return count;
}

void DeleteList(struct node** head) {
	struct node* current = *head;
	struct node* deleteNode;

	while(current != NULL) {
		deleteNode = current;
		current = current->next;
		free(deleteNode);
	}
	*head = current;
}

int Pop(struct node** head) {
	struct node* current = *head;
	int popped;

	*head = current->next;
	popped = current->data;
	free(current);

	return popped;
}

void InsertNth(struct node** head, int index, int data) {
	struct node* current = *head;
	int i;

	assert(index >= 0);	
	
	if(index == 0) {
		Push(&(*head), data);
		return;
	}

	for(i = 0; i < index - 1; i++) {
		current = current->next;
		assert(current != NULL);
	}

	Push(&(current->next), data);
}

int main() {
	struct node* list = NULL;

	InsertNth(&list, 0, 1);
	InsertNth(&list, 1, 2);
	InsertNth(&list, 2, 3);
	TraverseList(list);

	return 0;
}