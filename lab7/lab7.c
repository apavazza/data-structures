/**
* Directory emulator
* 
*/

#define _CRT_SECURE_NO_WARNINGS
#define MAX_STR_LEN 128

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct _directory;
typedef struct _directory Directory;
struct _stack;
typedef struct _stack Stack;

typedef struct _directory {
	char name[MAX_STR_LEN];
	Directory* sibling;
	Directory* child;
} Directory;

typedef struct _stack {
	Directory* el;
	Stack* next;
} Stack;

int main(void)
{
	bool status = false;
	Stack* head = (Stack*)malloc(sizeof(Stack));
	Directory* root = (Directory*)malloc(sizeof(Directory));

	status = menu();

	deleteAllDir(root);
	deleteAllStack(head);

	if (!menu)
	{
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

bool menu(void)
{
	char command[MAX_STR_LEN] = { 0 };
	printf("Directory emulator\n\n");
	printHelp();
	while (true)
	{
		printf(" > ");
		scanf_s("%s", &command, MAX_STR_LEN);
		if (strcmp(command, "md") == 0)
		{
			md(Directory* current, char name[MAX_STR_LEN]);
		}
		else if (strcmp(command, "cd dir") == 0)
		{
			
		}
		else if (strcmp(command, "cd ..") == 0)
		{

		}
		else if (strcmp(command, "dir") == 0)
		{
			dir(Directory* current);
		}
		else if (strcmp(command, "exit") == 0 )
		{
			return true;
		}
		else if (strcmp(command, "help") == 0)
		{
			printHelp();
		}
		else
		{
			printf("Command not recognized! Please try again\n");
		}
	}
}