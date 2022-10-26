#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STR_LEN 128

struct _node;
typedef struct _node Node;
Node* createElement(void);
Node* createElementWithInfo(const char* firstName, const char* lastName, int yearOfBirth);
bool addToStart(Node* el, Node* n);
bool addToEnd(Node* el, Node* n);
bool addBefore(const char* refLastName, Node* el, Node* n);
bool addAfter(const char* refLastName, Node* el, Node* n);
const char* inputLastName(char* lastName);
void printHelp(void);
void printList(Node* n);
Node* find(const char* x, Node* n);
Node* findPrev(const char* x, Node* n);
bool delete(const char* x, Node* n);
void deleteAll(Node* n);
const char* inputFileName(char* filename);
bool save(const char* filename, Node* n);
bool load(const char* filename, Node* n);
void sort(Node* n);

typedef struct _node
{
	char firstName[MAX_STR_LEN];
	char lastName[MAX_STR_LEN];
	int yearOfBirth;
	Node* next;
} Node;

int main(void) {
	char command[11] = { 0 };
	char temp_str[MAX_STR_LEN] = { 0 };
	Node* head = (Node*)malloc(sizeof(Node));
	Node* temp = NULL;
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
		else if (strcmp(command, "addbefore") == 0 || strcmp(command, "ab") == 0)
		{
			if (!addBefore(inputLastName(temp_str), createElement(), head))
			{
				printf("Person could not be added\n");
			}
		}
		else if (strcmp(command, "addafter") == 0 || strcmp(command, "aa") == 0)
		{
			if (!addAfter(inputLastName(temp_str), createElement(), head))
			{
				printf("Person could not be added\n");
			}
		}
		else if (strcmp(command, "sort") == 0 || strcmp(command, "so") == 0)
		{
			sort(head);
		}
		else if (strcmp(command, "print") == 0 || strcmp(command, "p") == 0)
		{
			printList(head);
		}
		else if (strcmp(command, "find") == 0 || strcmp(command, "f") == 0)
		{
			if (temp = find(inputLastName(temp_str), head))
			{
				printf("FOUND: %s %s %d\n", temp->firstName, temp->lastName, temp->yearOfBirth);
			}
			else
			{
				printf("Person with the last name %s could not be found\n", temp_str);
			}
		}
		else if (strcmp(command, "delete") == 0 || strcmp(command, "d") == 0)
		{
			if (!delete(inputLastName(temp_str), head))
			{
				printf("Person with the last name %s could not be found\n", temp_str);
			}
		}
		else if (strcmp(command, "save") == 0 || strcmp(command, "s") == 0)
		{
			if (!save(inputFileName(temp_str), head))
			{
				printf("File %s could not be opened\n", temp_str);
			}
		}
		else if (strcmp(command, "load") == 0 || strcmp(command, "l") == 0)
		{
			if (!load(inputFileName(temp_str), head))
			{
				printf("File %s could not be opened\n", temp_str);
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

Node* createElementWithInfo(const char* firstName, const char* lastName, int yearOfBirth)
{
	Node* new = (Node*)malloc(sizeof(Node));
	if (new == NULL) return NULL;

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

bool addBefore(const char* refLastName, Node* el, Node* n)
{
	Node* temp = NULL;
	if (!el) return false;

	temp = findPrev(refLastName, n);
	if (!temp) return false;

	el->next = temp->next;
	temp->next = el;
	return true;
}

bool addAfter(const char* refLastName, Node* el, Node* n)
{
	Node* temp = NULL;
	if (!el) return false;

	temp = find(refLastName, n);
	if (!temp) return false;

	el->next = temp->next;
	temp->next = el;
	return true;
}

const char* inputLastName(char* lastName)
{
	printf("Reference last name: ");
	scanf(" %s", lastName);

	return lastName;
}

void printHelp(void)
{
	printf("Usage:\n\n"
		"\taddtostart, as \tAdds a person to the start of the list\n"
		"\taddtoend, ae \tAdds a person to the end of the list\n"
		"\taddbefore, ab \tAdds a person before a specific person\n"
		"\taddafter, aa \tAdds a person after a specific person\n"
		"\tsort, so \tSort the list by last name\n"
		"\tprint, p \tPrints all elevents of the list\n"
		"\tfind, f \tSearches for a person in the list\n"
		"\tdelete, d \tDelets a person from the list\n"
		"\tsave, s \tSave the list to a file\n"
		"\tload, l \tLoad a list from a file\n"
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

Node* find(const char* x, Node* n)
{
	n = n->next; // preskacemo head
	while (n != NULL && strcmp(n->lastName, x) != 0)
	{
		n = n->next;
	}
	if (n == NULL) return NULL;

	return n;
}

Node* findPrev(const char* x, Node* n)
{
	while (n->next != NULL && (strcmp(n->next->lastName, x) != 0))
	{
		n = n->next;
	}
	if (n->next == NULL) return NULL;
	return n;
}

bool delete(const char* x, Node* n)
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

const char* inputFileName(char* filename)
{
	printf("File name: ");
	scanf(" %s", filename);

	return filename;
}

bool save(const char* filename, Node* n)
{
	FILE* f = NULL;
	f = fopen(filename, "w");
	if (!f) return false;

	n = n->next; // preskacemo head
	while (n != NULL)
	{
		fprintf(f, "%s %s %d\n", n->firstName, n->lastName, n->yearOfBirth);
		n = n->next;
	}

	fclose(f);
	return true;
}

bool load(const char* filename, Node* n)
{
	FILE* f = NULL;
	char firstName[MAX_STR_LEN] = { 0 };
	char lastName[MAX_STR_LEN] = { 0 };
	int yearOfBirth = 0;

	f = fopen(filename, "r");
	if (!f) return false;

	deleteAll(n->next);
	n->next = NULL;

	while (!feof(f))
	{
		fscanf(f, "%s %s %d\n", firstName, lastName, &yearOfBirth);
		addToEnd(createElementWithInfo(firstName, lastName, yearOfBirth), n);
	}

	fclose(f);
	return true;
}

void sort(Node* n)
{
	Node* j, * prev_j, * temp, * end;

	end = NULL;
	while (n->next != end)
	{
		prev_j = n;
		j = n->next;
		while (j->next != end)
		{
			if (strcmp(j->lastName, j->next->lastName) > 0)
			{
				temp = j->next;
				prev_j->next = temp;
				j->next = temp->next;
				temp->next = j;

				j = temp;
			}
			prev_j = j;
			j = j->next;
		}
		end = j;
	}
}