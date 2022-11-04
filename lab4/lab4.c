#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STR_LEN 128
#define MAX_LINE 1024

struct _node;
typedef struct _node Node;
bool menu(Node* head1, Node* head2, Node* head3);
bool loadPolynomials(const char* filename, Node* h1, Node* h2, Node* h3);
bool split(char* pol, Node* n);
Node* find(int exponent, Node* n);
Node* createElement(int coefficient, int exponent);
bool add(Node* h1, Node* h2, Node* h3);
bool insertSorted(Node* el, Node* n);
void printPolynomial(Node* n);
bool delete(Node* n);
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
	Node* head3 = (Node*)malloc(sizeof(Node));
	bool menu_ret = false;
	if (!head1 || !head2 || !head3)
	{
		printf("Application could not be started\n");
		return EXIT_FAILURE;
	}
	head1->next = NULL;
	head2->next = NULL;
	head3->next = NULL;

	menu_ret = menu(head1, head2, head3);
	
	// oslobadjanje prostora
	deleteAll(head1);
	deleteAll(head2);
	deleteAll(head3);

	if (menu_ret) return EXIT_SUCCESS;
	return EXIT_FAILURE;
}

bool menu(Node* head1, Node* head2, Node* head3)
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

			if (!loadPolynomials(filename, head1, head2, head3))
			{
				printf("Polynomials could not be loaded! Please try again\n");
			}
		}
		else if (strcmp(command, "add") == 0 || strcmp(command, "a") == 0)
		{
			add(head1, head2, head3);
		}
		else if (strcmp(command, "multiply") == 0 || strcmp(command, "m") == 0)
		{
			printf("Not yet implemented!\n");
		}
		else if (strcmp(command, "print") == 0 || strcmp(command, "p") == 0)
		{
			printPolynomial(head1);
			printPolynomial(head2);
			printPolynomial(head3);
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

bool loadPolynomials(const char* filename, Node* h1, Node* h2, Node* h3)
{
	char polynomial1[MAX_STR_LEN] = { 0 };
	char polynomial2[MAX_STR_LEN] = { 0 };
	FILE* f = NULL;
	f = fopen(filename, "r");
	if (!f) return false;

	deleteAll(h1->next); // brisemo stare polinome ako postoje
	deleteAll(h2->next);
	deleteAll(h3->next);
	h1->next = NULL;
	h2->next = NULL;
	h3->next = NULL;

	fgets(polynomial1, MAX_LINE, f);
	fgets(polynomial2, MAX_LINE, f);
	
	fclose(f);

	if (split(polynomial1, h1) && split(polynomial2, h2)) return true;
	return false;
}

bool split(char* pol, Node* n)
{
	int c = 0;
	int e = 0;
	int num = 0;
	int numOfVars = 0;
	Node* temp = NULL;
	while (strlen(pol) > 0)
	{
		numOfVars = sscanf(pol, " %d %d %n", &c, &e, &num);
		pol += num;
		if (numOfVars == 2)
		{
			if (temp = find(e, n)) // eksponent je vec u listi
			{
				temp->coefficient += c;
				if (temp->coefficient == 0)
				{
					delete(temp);
				}
			}
			else
			{
				insertSorted(createElement(c, e), n);
			}
		}
		else
		{
			printf("Wrong polynomial format\n");
			return false;
		}
	}
	return true;
}

Node* find(int exponent, Node* n)
{
	while (n->next != NULL && (exponent >= n->exponent)) //popraviti
	{
		n = n->next;
		
		
	}

	if (exponent == n->exponent)
	{
		return n;
	}
	return NULL;
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

	// lista je prazna
	if (n->next == NULL)
	{
		el->next = NULL;
		n->next = el;
		return true;
	}

	// lista nije prazna
	while (n->next != NULL && (el->exponent <= n->exponent))
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
	if (n == NULL)
	{
		printf("EMPTY\n");
		return;
	}

	while (n)
	{
		printf("%dx^%d", n->coefficient, n->exponent);
		if (n->next) printf("+");
		n = n->next;
	}
	printf("\n");
}

bool add(Node* h1, Node* h2, Node* h3)
{
	Node* temp = NULL;
	if (!h1->next || !h2->next)
	{
		printf("You first need to load the polynomilas\n"
			"Type help for more information\n");
	}

	deleteAll(h3->next); // brisemo stari rezultanti polinom ako postoji
	h3->next = NULL;

	while (h1 != NULL && h2 != NULL)
	{
		if (h1->exponent == h2->exponent)
		{
			insertSorted(createElement(h1->coefficient + h2->coefficient, h1->exponent), h3);
			h1 = h1->next;
			h2 = h2->next;
		}
		else if (h1->exponent > h2->exponent)
		{
			insertSorted(createElement(h1->coefficient, h1->exponent), h3);
			h1 = h1->next;
		}
		else
		{
			insertSorted(createElement(h2->coefficient, h2->exponent), h3);
		}
	}
	if (h1 != NULL) temp = h1;
	else temp = h2;
	while (temp != NULL)
	{
		insertSorted(createElement(temp->coefficient, temp->exponent), h3);
		temp = temp->next;
	}
	return true;
}

Node* findPrev(Node* n)
{
	Node* prev = NULL;
	while (prev->next != NULL && prev->next->exponent != n->exponent)
	{
		prev = prev->next;
	}
	if (prev->next == NULL) return NULL;
	return prev;
}

bool delete(Node* n)
{
	Node* prev = NULL;
	prev = findPrev(n);
	if (prev == NULL) return false;

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