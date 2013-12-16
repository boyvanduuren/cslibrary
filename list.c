#include <stdio.h>
#include <stdlib.h>

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

struct node* GetN(struct node* head, int n) {
	struct node* current = head;
	int i;

	for(i = 0; i < n; i++) {
		if(current->next == NULL) return current;
		current = current->next;
	}
	return current;
}

void Insert(struct node* head, int position, int data) {
	struct node* before = GetN(head, position);
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

int main() {
	struct node* head = BuildDummy();
	TraverseList(head);

	return 0;
}