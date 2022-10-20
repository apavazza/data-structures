#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STR_LEN 128

bool addToStart(Person x, Node* n);
void printList(Node* n);
bool addToEnd(Person x, Node* n);
Node* find(Person x, Node* n);
Node* findPrev(Person x, Node* n);
bool delete(Person x, Node* n);

typedef struct _person
{
	char firstName[MAX_STR_LEN];
	char lastName[MAX_STR_LEN];
	char yearOfBirth[4];
} Person;

typedef struct _node
{
	Person el;
	Node* next;
} Node;

bool addToStart(Person x, Node* n)
{
	Node* new = (Node* )malloc(sizeof(Node));
	if (new == NULL) return false;

	new->el = x;
	new->next = n->next;
	n->next = new;

	return true;
}

void printList(Node* n)
{
	n = n->next; // preskacemo head
	while (n != NULL)
	{
		printf("%s %s\n", n->el.firstName, n->el.lastName);
		n = n->next;
	}
}

bool addToEnd(Person x, Node* n)
{
	Node* new = (Node*)malloc(sizeof(Node));
	if (new == NULL) return false;

	while (n->next != NULL)
	{
		n = n->next;
	}
	
	new->el = x;
	new->next = NULL;
	n->next = new;

	return true;
}

Node* find(Person x, Node* n)
{
	n = n->next; // preskacemo head
	while (n != NULL && n->el.lastName != x.lastName)
	{
		n = n->next;
	}

	return n;
}

Node* findPrev(Person x, Node* n)
{
	while (n->next != NULL && n->next->el.lastName != x.lastName)
	{
		n = n->next;
	}

	return n;
}

bool delete(Person x, Node* n)
{
	Node* prev = NULL;
	prev = findPrev(x, n);
	if (prev == NULL) return false;

	n = prev->next;
	prev->next = prev->next->next;
	free(n);
	return true;
}

int main(void) {
	Node* head = (Node*)malloc(sizeof(Node));
	head->next = NULL;
}