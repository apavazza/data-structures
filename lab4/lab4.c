#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STR_LEN 128

struct _node;
typedef struct _node Node;
bool menu(Node* head1, Node* head2);
bool loadPolynomials(const char* filename, Node* h1, Node* h2);
bool split(char* pol, Node* n);
Node* createElement(int coefficient, int exponent);
bool insertSorted(Node* el, Node* n);
void printPolynomial(Node* n);
void deleteAll(Node* n);
void printHelp(void);

typedef struct _node
{
	int coefficient;
	int exponent;
	Node* next;
} Node;


int main(void) {
	Node* head1 = (Node*)malloc(sizeof(Node));
	Node* head2 = (Node*)malloc(sizeof(Node));
	if (!head1 || !head2)
	{
		printf("Application could not be started\n");
		return EXIT_FAILURE;
	}
	head1->next = NULL;
	head2->next = NULL;

	if (menu(head1, head2))
	{
		// oslobadjanje prostora
		deleteAll(head1);
		deleteAll(head2);
		return EXIT_SUCCESS;
	}
	else
	{
		// oslobadjanje prostora
		deleteAll(head1);
		deleteAll(head2);
		return EXIT_FAILURE;
	}
}

bool menu(Node* head1, Node* head2)
{
	char filename[MAX_STR_LEN] = { 0 };
	char command[MAX_STR_LEN] = { 0 };
	printHelp();
	while (true)
	{
		printf(" > ");
		scanf(" %s", command);
		if (strcmp(command, "load") == 0 || strcmp(command, "l") == 0)
		{
			printf("File name: ");
			scanf(" %s", filename);

			if (!loadPolynomials(filename, head1, head2))
			{
				printf("Polynomials could not be loaded\n");
				return false;
			}
		}
		else if (strcmp(command, "add") == 0 || strcmp(command, "a") == 0)
		{
			printf("Not yet implemented!\n");
		}
		else if (strcmp(command, "multiply") == 0 || strcmp(command, "m") == 0)
		{
			printf("Not yet implemented!\n");
		}
		else if (strcmp(command, "print") == 0 || strcmp(command, "p") == 0)
		{
			printPolynomial(head1);
			printPolynomial(head2);
		}
		else if (strcmp(command, "help") == 0 || strcmp(command, "h") == 0)
		{
			printHelp();
		}
		else if (strcmp(command, "quit") == 0 || strcmp(command, "q") == 0)
		{
			printf("Quitting application...");
			return true;
		}
		else
		{
			printf("Command not recognized! Please try again\n");
		}
	}
}

bool loadPolynomials(const char* filename, Node* h1, Node* h2)
{
	char polynomial1[MAX_STR_LEN] = { 0 };
	char polynomial2[MAX_STR_LEN] = { 0 };
	FILE* f = NULL;
	f = fopen(filename, "r");
	if (!f) return false;

	deleteAll(h1->next); // brisemo stare polinome ako postoje
	deleteAll(h2->next);
	h1->next = NULL;
	h2->next = NULL;

	fgets(polynomial1, 100, f);
	fgets(polynomial2, 100, f);
	
	fclose(f);

	if (split(polynomial1, h1) && split(polynomial2, h2)) return true;
	return false;
}

bool split(char* pol, Node* n)
{
	int i = 0;
	char prev[MAX_STR_LEN] = { 0 };
	char* token = strtok(pol, " ");
	for (i; strcmp(token, "\n") != 0; i++)
	{
		strcpy(prev, token);
		token = strtok(NULL, " ");
		if (i % 2 == 0) // ako je parno
		{
			insertSorted(createElement(atoi(prev), atoi(token)), n);
		}
	}
	if (i % 2 == 0) return true;
	return false;
}

Node* createElement(int coefficient, int exponent)
{
	Node* new = (Node*)malloc(sizeof(Node));
	if (!new) return NULL;

	new->coefficient = coefficient;
	new->exponent = exponent;
	new->next = NULL;
	
	return new;
}

bool insertSorted(Node* el, Node* n)
{
	if (!el) return false;

	if (n->next == NULL) // lista je prazna
	{
		el->next = NULL;
		n->next = el;
		return true;
	}

	// lista nije prazna
	while (n->next != NULL && (el->exponent < n->exponent))
	{
		n = n->next;
	}

	el->next = n->next;
	n->next = el;

	return true;
}

void printPolynomial(Node* n)
{
	n = n->next; // head preskacemo
	while (n)
	{
		printf("%dx^%d+", n->coefficient, n->exponent);
		n = n->next;
	}
	printf("\n");
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

void printHelp(void)
{
	printf("Usage:\n\n"
		"\tload, l \tLoad polynomias\n"
		"\tprint, p \tPrint polynomilas\n"
		"\tadd, a \t\tAdd polynomials\n"
		"\tmultiply, m \tMultiply polynomials\n"
		"\thelp, h \tDisplays this help message\n"
		"\tquit, q \tQuit application\n");
}