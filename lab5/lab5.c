/**
* Calculator
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
bool loadExpression(Node* head);
Node* createElement(int num);
bool push(Node* el, Node* n);

typedef struct _node
{
	int num;
	Node* next;
} Node;

int main(void)
{
	Node* head = (Node*)malloc(sizeof(Node));
	if (!head)
	{
		printf("Application could not be started\n");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

bool loadExpression(Node* head)
{
	char filename[MAX_STR_LEN] = { 0 };
	char* buffer = malloc(MAX_LINE_LEN * sizeof(char));
	int num = 0;
	char operator;
	int temp = 0;
	int numOfBytes = 0;
	FILE* f = NULL;
	printf("Please type in the file name: ");
	scanf(" %s", filename);
	f = fopen(filename, "r");
	if (!f)
	{
		printf("File %s could not be opened\n");
		return false;
	}

	fgets(buffer, MAX_LINE_LEN, f);

	while (strlen(buffer) > 0)
	{
		temp = sscanf(buffer, " %d %n", &num, &numOfBytes);
		if (temp == 1)
		{
			push(createElement(num), head);
		}
		else {
			sscanf(buffer, " %c %n", operator, &numOfBytes);
			calculate(operator, head);
		}
		buffer += numOfBytes;
	}
	free(buffer);
	return true;
}

bool push(int num, Node* n)
{
	Node* new = (Node*)malloc(sizeof(Node));
	if (new == NULL) return false;

	new->next = n->next;
	n->next = new;

	return true;
}

bool calculate(char operator, Node* head)
{
	int* firstOperand = NULL;
	int* secondOperand = NULL;
	int* result = NULL;

	secondOperand = pop(head);
	firstOperand = pop(head);

	if (!firstOperand || !secondOperand)
	{
		printf("Invalid mathematical expression\n");
		return false;
	}

	switch (operator)
	{
	case '+':
		result = *firstOperand + *secondOperand;
		break;
	case '-':
		result = *firstOperand - *secondOperand;
		break;
	case '*':
		result = *firstOperand * *secondOperand;
		break;
	case '/':
		if (*secondOperand == 0) result = NULL;
		else result = *firstOperand / *secondOperand;
		break;
	default:
		printf("Invalid operator\n");
		return false;
	}
	
	if (result) push(*result, head);
	return true;
}

int* pop(Node* head)
{

	
}