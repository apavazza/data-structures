/**
* Postfix Expression Calculator
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
bool loadFromFile(char* buffer);
bool processExpression(char* expression, int* result, Node* head);
bool calculate(char operator, Node* head);
bool push(int num, Node* head);
bool pop(int* num, Node* head);
void deleteAll(Node* n);

typedef struct _node
{
	int num;
	Node* next;
} Node;

int main(void)
{
	char expression[MAX_LINE_LEN] = { 0 };
	int result = 0;
	Node* head = (Node*)malloc(sizeof(Node));
	head->next = NULL;
	bool prExp_ret = false;
	if (!head)
	{
		printf("Application could not be started\n");
		return EXIT_FAILURE;
	}

	printf("Postfix Expression Calculator\n\n");
	while (!loadFromFile(expression));
	prExp_ret = processExpression(expression, &result, head);
	deleteAll(head);

	if (prExp_ret)
	{
		// print the final result
		printf("Result = %d", result);
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}

/**
* Loads an expression from a file.
* @param buffer		Variable in which to save the loaded expression.
* @return			Returns true if completed successfully, otherwise false.
*/
bool loadFromFile(char* buffer)
{
	char filename[MAX_STR_LEN] = { 0 };
	FILE* f = NULL;

	printf("Please type in the file name: ");
	scanf_s(" %s", &filename, MAX_STR_LEN);
	f = fopen(filename, "r");
	if (!f)
	{
		printf("ERROR: File %s could not be opened! Please try again\n", filename);
		return false;
	}

	fgets(buffer, MAX_LINE_LEN, f);

	return true;
}

/**
* Processes a mathematical expression.
* @param expression	Expression which to process.
* @param result		Variable in which to save the result.
* @param head		Head of the list (stack) used for calculation.
* @return			Returns true if completed successfully, otherwise false.
*/
bool processExpression(char* expression, int* result, Node* head)
{
	int num = 0;
	char operator = 0;
	int temp = 0;
	int numOfBytes = 0;

	while (strlen(expression) > 0)
	{
		temp = sscanf(expression, " %d %n", &num, &numOfBytes);
		if (temp == 1)
		{
			if (!push(num, head))
			{
				printf("ERROR: Out of memory\n");
				return false;
			}
		}
		else {
			sscanf(expression, " %c %n", &operator, &numOfBytes);
			if (!calculate(operator, head)) return false;
		}
		expression += numOfBytes;
	}

	// pop the final result
	pop(result, head);

	// check whether the stack is empty
	if (head->next)
	{
		printf("ERROR: Invalid mathematical expression\n");
		return false;
	}
	
	return true;
}

/**
* Calculates a chosen mathematical operation.
* @param operator	Specifies which mathematical operation to execute.
* @param head		Head of the list (stack) used for calculation.
* @return			Returns true if completed successfully, otherwise false.
*/
bool calculate(char operator, Node* head)
{
	int firstOperand = 0;
	int secondOperand = 0;
	int result = 0;

	if (!pop(&secondOperand, head) || !pop(&firstOperand, head))
	{
		printf("ERROR: Invalid mathematical expression\n");
		return false;
	}

	switch (operator)
	{
	case '+':
		result = firstOperand + secondOperand;
		break;
	case '-':
		result = firstOperand - secondOperand;
		break;
	case '*':
		result = firstOperand * secondOperand;
		break;
	case '/':
		if (secondOperand == 0)
		{
			printf("ERROR: Division by zero\n");
			return false;
		}
		result = firstOperand / secondOperand;
		break;
	default:
		printf("ERROR:Invalid operator\n");
		return false;
	}

	// push the result onto the stack
	if (push(result, head))
	{
		return true;
	}
	else
	{
		printf("ERROR: Out of memory\n");
		return false;
	}
}

/**
* Pushes a number onto a stack.
* @param num		Number to push onto a stack.
* @param head		Head of the list (stack) on which to push.
* @return			Returns true if completed successfully, otherwise false.
*/
bool push(int num, Node* head)
{
	Node* new = (Node*)malloc(sizeof(Node));
	if (new == NULL) return false;

	new->next = head->next;
	head->next = new;
	new->num = num;

	return true;
}

/**
* Pops a number from a stack.
* @param num		Variable in which to save the popped number.
* @param head		Head of the list (stack) from which to pop the number.
* @return			Returns true if completed successfully, otherwise false.
*/
bool pop(int* num, Node* head)
{
	Node* popped = head->next;

	if (popped)
	{
		*num = popped->num;

		// delete the popped node
		head->next = head->next->next;
		free(popped);

		return true;
	}
	return false;
}

/**
* Deletes all nodes from the node provided onward.
* @param n			Node from which to start deleting.
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