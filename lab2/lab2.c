#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STR_LEN 128

struct _node;
typedef struct _node Node;
Node* createElement(void);
bool addToStart(Node* el, Node* n);
bool addToEnd(Node* el, Node* n);
char* inputLastName(void);
void printHelp(void);
void printList(Node* n);
Node* find(char* x, Node* n);
Node* findPrev(char* x, Node* n);
bool delete(Node* n);
void deleteAll(Node* n);

typedef struct _node
{
	char firstName[MAX_STR_LEN];
	char lastName[MAX_STR_LEN];
	int yearOfBirth;
	Node* next;
} Node;

int main(void) {
	char command[11] = { 0 };
	Node* head = (Node*)malloc(sizeof(Node));
	head->next = NULL;

	printf("Linked List Addresser\n\n");
	printHelp();

	while (true)
	{
		printf(" > ");
		scanf(" %s", command);
		if (strcmp(command, "addtostart") == 0 || strcmp(command, "as") == 0)
		{
			if (!addToStart(createElement(), head))
			{
				printf("Person could not be added\n");
			}
		}
		else if (strcmp(command, "addtoend") == 0 || strcmp(command, "ae") == 0)
		{
			if (!addToEnd(createElement(), head))
			{
				printf("Person could not be added\n");
			}
		}
		else if (strcmp(command, "print") == 0 || strcmp(command, "p") == 0)
		{
			printList(head);
		}
		else if (strcmp(command, "find") == 0 || strcmp(command, "f") == 0)
		{
			if (!find(inputLastName(), head))
			{
				printf("The person could not be found\n");
			}
		}
		else if (strcmp(command, "delete") == 0 || strcmp(command, "d") == 0)
		{
			if (!delete(inputLastName(), head))
			{
				printf("The person could not be found\n");
			}
		}
		else if (strcmp(command, "help") == 0 || strcmp(command, "h") == 0)
		{
			printHelp();
		}
		else if (strcmp(command, "quit") == 0 || strcmp(command, "q") == 0)
		{
			printf("Quitting application...");
			// oslobadjanje prostora
			deleteAll(head);
			break;
		}
		else
		{
			printf("Command not recognized! Please try again\n");
		}
	}
	return EXIT_SUCCESS;
}

Node* createElement(void)
{
	char firstName[MAX_STR_LEN] = { 0 };
	char lastName[MAX_STR_LEN] = { 0 };
	int yearOfBirth = 0;
	Node* new = (Node*)malloc(sizeof(Node));
	if (new == NULL) return NULL;

	printf("First name: ");
	scanf(" %s", firstName);
	printf("Last name: ");
	scanf(" %s", lastName);
	printf("Year of birth: ");
	scanf(" %d", &yearOfBirth);

	strcpy(new->firstName, firstName);
	strcpy(new->lastName, lastName);
	new->yearOfBirth = yearOfBirth;
	new->next = NULL;

	return new;
}

bool addToStart(Node* el, Node* n)
{
	if (!el) return false;

	el->next = n->next;
	n->next = el;

	return true;
}

bool addToEnd(Node* el, Node* n)
{
	if (!el) return false;

	while (n->next != NULL)
	{
		n = n->next;
	}

	el->next = NULL;
	n->next = el;

	return true;
}

char* inputLastName()
{
	char lastName[MAX_STR_LEN] = { 0 };
	printf("Last name: ");
	scanf(" %s", lastName);
	return &lastName;
}

void printHelp(void)
{
	printf("Usage:\n\n"
		"\taddtostart, as \tAdds a person to the start of the list\n"
		"\taddtoend, ae \tAdds a person to the end of the list\n"
		"\tprint, p \tPrints all elevents of the list\n"
		"\tfind, f \tSearches for a person in the list\n"
		"\tdelete, d \tDelets a person from the list\n"
		"\thelp, h \tPrints this help message\n"
		"\tquit, q \tQuits the application\n\n");
}

void printList(Node* n)
{
	n = n->next; // preskacemo head
	while (n != NULL)
	{
		printf(" %s %s %d\n",n->firstName, n->lastName, n->yearOfBirth);
		n = n->next;
	}
}

Node* find(char* x, Node* n)
{
	n = n->next; // preskacemo head
	while (n != NULL && strcmp(n->lastName, x) != 0)
	{
		n = n->next;
	}
	if (n == NULL) return NULL;

	printf("FOUND: %s %s %d", n->firstName, n->lastName, n->yearOfBirth);

	return n;
}

Node* findPrev(char* x, Node* n)
{
	while (n->next != NULL && (strcmp(n->next->lastName, x) != 0))
	{
		n = n->next;
	}
	if (n->next == NULL) return NULL;
	return n;
}

bool delete(char* x, Node* n)
{
	Node* prev = NULL;
	prev = findPrev(x, n);
	if (prev == NULL) return false;

	n = prev->next;
	prev->next = prev->next->next;
	free(n);
	return true;
}

void deleteAll(Node* n)
{
	Node* temp = NULL;

	while ((temp = n) != NULL)
	{
		n = n->next;
		free(temp);
	}
}