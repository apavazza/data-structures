/**
* Directory library
*
* @author Amadeo Pavazza
* @author Petar Zadric
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Directory.h"
#include "Stack.h"

/**
* Makes a directory
* @param current	Current working directory.
* @param name		Name of the new directory.
* @return			Returns true if completed successfully, otherwise false.
*/
bool md(Directory* current, char* name)
{
	Directory* new = NULL;
	Directory* temp = NULL;

	if (!current->child) // current directory does not have a child
	{
		new = allocateDirectory(name);
		current->child = new;
		return true;
	}

	temp = current->child; // checking whether the directory already exists
	while (temp)
	{
		if (strcmp(temp->name, name) == 0)
		{
			printf("Directory with the name '%s' already exists\n", name);
			return false;
		}
		temp = temp->sibling;
	}

	new = allocateDirectory(name);
	if (strcmp(current->child->name, name) > 0) // checking whether the first child should be moved
	{
		new->sibling = current->child;
		current->child = new;
	}
	else // otherwise inserting the child
	{
		current = current->child;
		while (current->sibling && strcmp(current->sibling->name, new->name) < 0)
		{
			current = current->sibling;
		}
		new->sibling = current->sibling;
		current->sibling = new;
		return true;
	}
	return false;
}

/**
* Allocates memory for a directory.
* @param name	Name of the new directory.
* @return		Returns the address of the new directory.
*/
Directory* allocateDirectory(char* name)
{
	Directory* new = (Directory*)malloc(sizeof(Directory));
	if (!new) return NULL;
	strcpy(new->name, name);
	new->child = NULL;
	new->sibling = NULL;
	return new;
}

/**
Changes the current working directory.
@param current	Current working directory.
@param head		Head of stack.
@param name		Name of the directory which is to be entered.
@return			Returns the address of the new working directory.
*/
Directory* cd_dir(Directory* current, Stack* head, char* name)
{
	Directory* temp = current;
	if (temp->child)
	{
		if (strcmp(temp->child->name, name) == 0)
		{
			push(current, head);
			return temp->child;
		}
		temp = temp->child->sibling;
		while (temp)
		{
			if (strcmp(temp->name, name) == 0)
			{
				push(current, head);
				return temp;
			}
			temp = temp->sibling;
		}
	}
	printf("Directory not found\n");
	return current;
}

/**
* Changes the current working directory to its parent directory.
* @param current	Current working directory.
* @param head		Head of stack.
* @return			Returns the address of the new working directory.
*/
Directory* cd_previous(Directory* current, Stack* head)
{
	Directory* previous = NULL;
	previous = pop(head);
	if (!previous) return current;
	return previous;
}

/**
* Displays the contents of the current working directory.
* @param current	Current working directory.
* @return			Returns true if completed successfully, otherwise false.
*/
bool dir(Directory* current, Stack* head, char* path)
{
	printf(" Directory of: %s\n", path);

	if (!current->child)
	{
		return true;
	}
	else // directory has a child
	{
		current = current->child;
		while (current)
		{
			printf("\t%s\n", current->name);
			current = current->sibling;
		}
	}
	return true;
}

/**
* Recursively deletes all directories starting from the provided directory.
* @param dir	Directory from which to start deleting.
*/
void deleteAllDir(Directory* dir)
{
	if (!dir) return;
	if (dir->sibling) deleteAllDir(dir->sibling);
	if (dir->child) deleteAllDir(dir->child);

	free(dir);
}

/**
* Provides current path as a string.
* @param current	Current working directory.
* @param head		Head of stack.
* @param path		Variable in which to save the path.
*/
void updatePath(Directory* current, Stack* head, char* path)
{
	char path_temp[MAX_STR_LEN] = { 0 };
	strcpy(path, "");

	while (head->next)
	{
		snprintf(path_temp, MAX_STR_LEN, "%s\\%s", head->next->el->name, path);
		strcpy(path, path_temp);
		head = head->next;
	}

	strcat(path, current->name);
}