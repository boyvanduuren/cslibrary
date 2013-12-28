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

// I wrote this one my self. Because of the malloc()
// in the for loop, this one needs twice as many
// memory allocations as the example solution
void UnoptimizedInsertSort(struct node **headRef) {
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

// Example solution from the book
void InsertSort(struct node** headRef) {
	struct node* sortedList = NULL;
	struct node* current = *headRef;
	struct node* next;

	while(current != NULL) {
		next = current->next;
		SortedInsert(&sortedList, current);
		current = next;
	}

	*headRef = sortedList;
}

void AppendList(struct node** aRef, struct node** bRef) {
	struct node* aRefLocal = *aRef;

	// Exception for empty aRef, just point it to bRef
	if(*aRef == NULL) {
		*aRef = *bRef;
	}
	else {
		// Find last node in aRef
		while(aRefLocal->next != NULL)
			aRefLocal = aRefLocal->next;

		aRefLocal->next = *bRef;
		*bRef = NULL;
	}
}

// FrontBackSplit using a slow and fast pointer
// to determine where to split the list
void FrontBackSplit(struct node* source,
				struct node** frontRef, struct node** backRef) {
	struct node* slowPtr = source;
	struct node* fastPtr = source;

	while(fastPtr->next != NULL) {
		if(fastPtr->next->next != NULL) {
			fastPtr = fastPtr->next->next;
			slowPtr = slowPtr->next;
		}
		else if(fastPtr->next->next == NULL)
			fastPtr = fastPtr->next;
	}

	// Special case for list of 1
	if(fastPtr->data == 1) {
		*frontRef = source;
		*backRef = NULL;
	}
	else {
		*frontRef = source;
		*backRef = slowPtr->next;
		// Split list in half by pointing slowPtr->next to NULL
		slowPtr->next = NULL;
	}

}

// Remove duplicates from a sorted list
void RemoveDuplicates(struct node* head) {
	struct node* current = head;
	struct node* previous = NULL;

	while(current) {
		if(previous == NULL) {
			previous = current;
		}
		else {
			if(previous->data == current->data)
				previous->next = current->next;
			else
				previous = current;

			current = current->next;
		}
	}
}

void MoveNode(struct node** destRef, struct node** sourceRef) {
	assert(*sourceRef != NULL);

	struct node* next = (*sourceRef)->next;
	(*sourceRef)->next = *destRef;
	*destRef = *sourceRef;
	*sourceRef = next;
}

// My own solution to the AlternatingSplit problem
void AlternatingSplit(struct node* source,
				struct node** aRef, struct node** bRef) {
	int count = 0;

	while(source) {
		count++;
		if(count % 2)
			Append(&(*aRef), source->data);
		else
			Append(&(*bRef), source->data);

		source = source->next;
	}
}

// The PDF's solution, slightly rewritten
void AlternatingSplitBook(struct node* source,
				struct node** aRef, struct node** bRef) {
	struct node* current = source;

	while(current != NULL) {
		MoveNode(&(*aRef), &current);
		if(current != NULL)
			MoveNode(&(*bRef), &current);
	}
}

struct node* LongShuffleMerge(struct node* a, struct node* b) {
	struct node* current_a = a;
	struct node* current_b = b;
	struct node* list = NULL;
        struct node* tail = NULL;

	while(current_a) {
		if (!tail) {
			MoveNode(&list, &current_a);
			tail = list;
			if (current_b) {
				MoveNode(&(tail->next), &current_b);
				tail = tail->next;
			}
		}

		if (tail) {
			MoveNode(&(tail->next), &current_a);
			tail = tail->next;
			if(current_b) {
				MoveNode(&(tail->next), &current_b);
				tail = tail->next;
			}
		}
	}
	return list;
}

struct node* ShuffleMerge(struct node* a, struct node* b) {
	struct node dummy;
	struct node* tail = &dummy;

	dummy.next = NULL;

	
	while (1) {
		if (a) {
			MoveNode(&(tail->next), &a);
			tail = tail->next;
		}
		if (b) {
			MoveNode(&(tail->next), &b);
			tail = tail->next;
		}
		if (!b) {
			tail->next = a;
			break;
		}
	}

	return dummy.next;
}

struct node* SortedMerge(struct node* a, struct node* b) {
	struct node dummy;
	struct node *tail = &dummy;

	dummy.next = NULL;

	while (1) {
		if (!a) {
			tail->next = b;
			break;
		}
		else if (!b) {
			tail->next = a;
			break;
		}
		else {
			if (a->data < b->data)
				MoveNode(&(tail->next), &a);
			else if (b->data < a->data)
				MoveNode(&(tail->next), &b);
			tail = tail->next;
		}
	}
	return dummy.next;
}

void MergeSort(struct node** headRef) {
	struct node* head = *headRef;
	struct node* front;
	struct node* back;

	if (!head || !head->next)
		return;

	FrontBackSplit(*headRef, &front, &back);

	MergeSort(&front);
	MergeSort(&back);

	*headRef = SortedMerge(front, back);
}

// This was my first solution for the problem
// It works, but doesn't traverse each list just once
// which means it's not a good solution
struct node* BadSortedIntersect(struct node* a, struct node* b) {
	struct node* result = NULL;

	while (a) {
		while (b) {
			if (a->data == b->data) {
				Push(&result, a->data);
				break;
			}
			b = b->next;
		}
		a = a->next;
	}
	return result;
}

struct node* SortedIntersect(struct node* a, struct node* b) {
	struct node dummy;
	struct node* tail = &dummy;

	dummy.next = NULL;

	while(a && b) {
		if (a->data == b->data) {
			Push(&(tail->next), a->data);
			tail = tail->next;
			a = a->next;
			b = b->next;
		}
		else if (a->data < b->data)
			a = a->next;
		else if (b->data < a->data)
			b = b->next;
	}
	return dummy.next;
}

int main() {
	struct node *a = NULL;
	struct node *b = NULL;

	Append(&a, 1);
	Append(&a, 3);
	Append(&a, 5);
	Append(&a, 31);
	Append(&a, 313);

	Append(&b, 1);
	Append(&b, 3);
	Append(&b, 313);
	Append(&b, 7771);

	struct node* intersect = SortedIntersect(a, b);
	TraverseList(intersect);

	return 0;
}
