/**
* Stack library
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
* Pushes a directory onto a stack.
* @param dir		Directory to push onto a stack.
* @param head		Head of the list (stack) on which to push.
* @return			Returns true if completed successfully, otherwise false.
*/
bool push(Directory* dir, Stack* head)
{
	Stack* new = (Stack*)malloc(sizeof(Stack));
	if (!new) return false;

	new->next = head->next;
	head->next = new;
	new->el = dir;

	return true;
}

/**
* Pops a directory from a stack.
* @param head		Head of the list (stack) from which to pop the directory.
* @return			Returns true if completed successfully, otherwise false.
*/
Directory* pop(Stack* head)
{
	Stack* popped = head->next;
	Directory* dir = NULL;

	if (popped)
	{
		dir = popped->el;

		// delete the popped Node
		head->next = head->next->next;
		free(popped);

		return dir;
	}
	return NULL;
}

/**
* Deletes all nodes from the stack provided onward.
* @param n		Stack from which to start deleting.
*/
void deleteAllStack(Stack* n)
{
	Stack* temp = NULL;

	while ((temp = n) != NULL)
	{
		n = n->next;
		free(temp);
	}
}