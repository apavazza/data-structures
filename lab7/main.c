/**
* Directory emulator
*
* @author Amadeo Pavazza
* @author Petar Zadric
*/

#define _CRT_SECURE_NO_WARNINGS
#define MAX_STR_LEN 1024

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Stack.h"
#include "Directory.h"

bool menu(Directory* root, Stack* head);
void printHelp(void);

int main(void)
{
	bool status = false;
	Stack* head = (Stack*)malloc(sizeof(Stack));
	Directory* root = (Directory*)malloc(sizeof(Directory));
	if (!head || !root)
	{
		printf("Application could not be started\n");
		return EXIT_FAILURE;
	}
	head->el = NULL;
	head->next = NULL;
	root->sibling = NULL;
	root->child = NULL;
	strcpy(root->name, "C:");

	status = menu(root, head);

	deleteAllDir(root);
	deleteAllStack(head);

	if (!status)
	{
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

/**
* Provides command line user interface.
* @param root	Address of the root directory.
* @param head	Address of the stack's head.
* @return		Returns true if completed successfully, otherwise false.
*/
bool menu(Directory* root, Stack* head)
{
	char command[MAX_STR_LEN] = { 0 };
	char name[MAX_STR_LEN] = { 0 };
	char path[MAX_STR_LEN] = { 0 };
	Directory* current = root;
	updatePath(current, head, path);
	printf("Directory emulator\n\n");
	printHelp();
	while (true)
	{
		printf(" %s> ", path);
		scanf_s(" %s", &command, MAX_STR_LEN);
		if (strcmp(command, "md") == 0)
		{
			printf("Directory name: ");
			scanf_s(" %s", &name, MAX_STR_LEN);
			md(current, name);
		}
		else if (strcmp(command, "cd") == 0)
		{
			printf("Directory name: ");
			scanf_s(" %s", &name, MAX_STR_LEN);
			current = cd_dir(current, head, name);
			updatePath(current, head, path);
		}
		else if (strcmp(command, "cd..") == 0)
		{
			current = cd_previous(current, head);
			updatePath(current, head, path);
		}
		else if (strcmp(command, "dir") == 0)
		{
			dir(current, head, path);
		}
		else if (strcmp(command, "exit") == 0)
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

/**
* Prints the help message.
*/
void printHelp(void)
{
	printf("Usage:\n\n"
		"\tmd \tMake a directory\n"
		"\tcd \tChange directory\n"
		"\tcd.. \tMove to a previous directory\n"
		"\tdir \tPrint directory contents\n"
		"\thelp \tDisplays this help message\n"
		"\texit \tExit application\n");
}