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

void long_SortedInsert(struct node** head, struct node* newNode) {
	struct node* current;
	newNode->next = NULL;

	// Will newNode replace node 0?
	if(current == NULL || newNode->data <= (*head)->data) {
		newNode->next = *head;
		*head = newNode;
		return;
	}

	// This code will run if newNode doesn't replace node 0
	for(current = *head; current->next != NULL; current = current->next) {
		if(newNode->data > current->data && newNode->data <= (current->next)->data) {
			newNode->next = current->next;
			current->next = newNode;
			break;
		}
	}

	// newNode->data > list-1, so place it at the tail
	if(newNode->data > current->data) current->next = newNode;
}

void SortedInsert(struct node** headRef, struct node* newNode) {
	struct node* current = *headRef;

	if(*headRef == NULL || newNode->data <= (*headRef)->data) {
		newNode->next = *headRef;
		*headRef = newNode;
	}
	else {
		while(current->next != NULL && newNode->data > current->next->data) {
			current = current->next;
		}
		newNode->next = current->next;
		current->next = newNode;
	}
}

void InsertSort(struct node **headRef) {
	struct node* sortedList = NULL;
	struct node* current;
	struct node* newNode;

	for(current = *headRef; current != NULL; current = current->next) {
		newNode = malloc(sizeof(struct node));
		newNode->data = current->data;
		SortedInsert(&sortedList, newNode);;
	}
	DeleteList(&(*headRef));
	*headRef = sortedList;
}

int main() {
	struct node* list = NULL;

	Append(&list, 56);
	Append(&list, 2);
	Append(&list, 9);

	InsertSort(&list);
	TraverseList(list);

	return 0;
}