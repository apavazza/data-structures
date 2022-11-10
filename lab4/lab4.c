/**
* Polynomial calculator.
* Supports addition and multiplication.
* 
* @author Amadeo Pavazza
* @author Petar Zadric
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STR_LEN 128
#define MAX_LINE_LEN 1024

struct _node;
typedef struct _node Node;
bool menu(Node* head1, Node* head2, Node* head3);
bool loadPolynomials(const char* filename, Node* h1, Node* h2, Node* h3);
bool processPolynomial(char* pol, Node* n);
Node* createElement(int coefficient, int exponent);
bool insertSorted(Node* el, Node* n);
bool add(Node* h1, Node* h2, Node* h3);
bool multiply(Node* h1, Node* h2, Node* h3);
Node* find(int exponent, Node* n);
Node* findPrev(Node* x, Node* n);
bool delete(Node* x, Node* n);
void deleteAll(Node* n);
void printPolynomial(Node* n);
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
	
	// free memory
	deleteAll(head1);
	deleteAll(head2);
	deleteAll(head3);

	if (menu_ret) return EXIT_SUCCESS;
	return EXIT_FAILURE;
}

/**
* Provides command line user interface.
* @param head1	Head of the first list.
* @param head2	Head of the second list.
* @param head3	Head of the third list.
* @return		Returns true if completed successfully, otherwise false.
*/
bool menu(Node* head1, Node* head2, Node* head3)
{
	char filename[MAX_STR_LEN] = { 0 };
	char command[MAX_STR_LEN] = { 0 };
	printf("Polynomial calculator\n\n");
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
			if (add(head1, head2, head3))
			{
				printf("P3 = P1 + P2 = ");
				printPolynomial(head3);
			}
			else
			{
				printf("An error occured\n");
			}
		}
		else if (strcmp(command, "multiply") == 0 || strcmp(command, "m") == 0)
		{
			if (multiply(head1, head2, head3))
			{
				printf("P3 = P1 * P2 = ");
				printPolynomial(head3);
			}
			else
			{
				printf("An error occured\n");
			}
		}
		else if (strcmp(command, "print") == 0 || strcmp(command, "p") == 0)
		{
			printf("P1 = ");
			printPolynomial(head1);
			printf("P2 = ");
			printPolynomial(head2);
			printf("P3 = ");
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

/**
* Loads polynomials into memory.
* @param filename	Name of the file from which to read the polynomials.
* @param h1			Head of the first list.
* @param h2			Head of the second list.
* @param h3			Head of the third list.
* @return			Returns true if completed successfully, otherwise false.
*/
bool loadPolynomials(const char* filename, Node* h1, Node* h2, Node* h3)
{
	char polynomial1[MAX_STR_LEN] = { 0 };
	char polynomial2[MAX_STR_LEN] = { 0 };
	FILE* f = NULL;
	f = fopen(filename, "r");
	if (!f) return false;

	deleteAll(h1->next); // delete old polynomials if they exist
	deleteAll(h2->next);
	deleteAll(h3->next);
	h1->next = NULL;
	h2->next = NULL;
	h3->next = NULL;

	fgets(polynomial1, MAX_LINE_LEN, f);
	fgets(polynomial2, MAX_LINE_LEN, f);
	
	fclose(f);

	if (processPolynomial(polynomial1, h1) && processPolynomial(polynomial2, h2)) return true;
	return false;
}

/**
* Parses polynomials from a string into nodes in a linked list.
* @param pol	Polynomial as a string.
* @param n		Head of a list in which to insert the polynomial.
* @return		Returns true if completed successfully, otherwise false.
*/
bool processPolynomial(char* pol, Node* n)
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
			temp = find(e, n);
			if (temp != NULL) // exponent is already in the list
			{
				temp->coefficient += c;
				if (temp->coefficient == 0) // sum of coefficients is 0 so we need to delete this element
				{
					delete(temp, n);
				}
			}
			else if (c != 0) // exponent is not in the list; if coefficient is 0 we don't need to add this element
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

/**
* Creates an element (Node).
* @param coefficient	Coefficient of a node.
* @param exponent		Exponent of a node.
* @return new			The address of a newly created node.
*/
Node* createElement(int coefficient, int exponent)
{
	Node* new = (Node*)malloc(sizeof(Node));
	if (!new) return NULL;

	new->coefficient = coefficient;
	new->exponent = exponent;
	new->next = NULL;
	
	return new;
}

/**
* Inserts an element into a list.
* The elements are sorted by exponent from the lowest to the highest.
* @param el		Address of the node which is to be inserted.
* @param n		Head of a list in which to insert the element.
* @return		Returns true if completed successfully, otherwise false.
*/
bool insertSorted(Node* el, Node* n)
{
	if (!el) return false;

	// list is empty
	if (n->next == NULL)
	{
		el->next = NULL;
		n->next = el;
		return true;
	}

	// list is not empty
	while (n->next != NULL && (n->next->exponent <= el->exponent))
	{	
		n = n->next;
	}

	el->next = n->next;
	n->next = el;

	return true;
}

/**
* Adds two polynomials.
* @param h1		Head of the first list, containing the first polynomial.
* @param h2		Head of the second list, containing the second polynomial.
* @param h3		Head of the third list, in which to save the result.
* @return		Returns true if completed successfully.
*/
bool add(Node* h1, Node* h2, Node* h3)
{
	Node* temp = NULL;

	h1 = h1->next; // skip head nodes
	h2 = h2->next;

	deleteAll(h3->next); // delete the old result if it exists
	h3->next = NULL;

	while (h1 != NULL && h2 != NULL)
	{
		if (h1->exponent == h2->exponent)
		{
			insertSorted(createElement(h1->coefficient + h2->coefficient, h1->exponent), h3);
			h1 = h1->next;
			h2 = h2->next;
		}
		else if (h1->exponent < h2->exponent)
		{
			insertSorted(createElement(h1->coefficient, h1->exponent), h3);
			h1 = h1->next;
		}
		else
		{
			insertSorted(createElement(h2->coefficient, h2->exponent), h3);
			h2 = h2->next;
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

/**
* Multiplies two polynomials.
* @param h1		Head of the first list, containing the first polynomial.
* @param h2		Head of the second list, containing the second polynomial.
* @param h3		Head of the third list, in which to save the result.
* @return		Returns true if completed successfully.
*/
bool multiply(Node* h1, Node* h2, Node* h3)
{
	Node* h2_orig = h2;
	Node* temp = NULL;

	deleteAll(h3->next); // delete the old result if it exists
	h3->next = NULL;

	while (h1 = h1->next)
	{
		while (h2 = h2->next)
		{
			temp = find(h1->exponent + h2->exponent, h3);
			if (temp) // the exponent is already in the list
			{
				temp->coefficient += h1->coefficient * h2->coefficient;
			}
			else // the exponent is not in the list
			{
				insertSorted(createElement(h1->coefficient * h2->coefficient, h1->exponent + h2->exponent), h3);
			}
		}
		h2 = h2_orig;
	}
	return true;
}

/**
* Searches for the previous node of a given node.
* @param x	Node of which we need the previous node.
* @param n	Head of a list.
* @return	If found returns previous node of node x, otherwise NULL.
*/
Node* findPrev(Node* x, Node* n)
{
	while (n->next != NULL && n->next->exponent != x->exponent)
	{
		n = n->next;
	}
	if (n->next == NULL) return NULL;
	return n;
}

/**
* Searches for a node with the given exponent.
* @param exponent	Exponent for which to search.
* @param n			Head of a list.
* @return			If found returns node's address, otherwise NULL.
*/
Node* find(int exponent, Node* n)
{
	n = n->next; // skip head node

	while (n != NULL && (exponent != n->exponent))
	{
		n = n->next;
	}

	if (n == NULL) return NULL;
	return n;
}

/**
* Deletes a node from a list.
* @param x	Node which is to be deleted.
* @param n	Head of a list from which to delete.
* @return	Returns true if completed successfully, otherwise false.
*/
bool delete(Node* x, Node* n)
{
	Node* prev = NULL;
	prev = findPrev(x, n);
	if (prev == NULL) return false;

	prev->next = prev->next->next;
	free(x);
	return true;
}

/**
* Deletes all nodes from a list.
* @param	Head of a list.
*/
void deleteAll(Node* n)
{
	Node* temp = NULL;

	while ((temp = n) != NULL)
	{
		n = n->next;
		free(temp);
	}
}

/**
* Prints a polynomial on standard output.
* @param n	Head of a list.
*/
void printPolynomial(Node* n)
{
	n = n->next; // skip head node
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

/**
* Prints the help message.
*/
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