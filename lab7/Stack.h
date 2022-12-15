/**
* Stack library
*
* @author Amadeo Pavazza
* @author Petar Zadric
*/

#pragma once

struct _stack;
typedef struct _stack Stack;
struct _directory;
typedef struct _directory Directory;
bool push(Directory* dir, Stack* head);
Directory* pop(Stack* head);
void deleteAllStack(Stack* n);

typedef struct _stack {
	Directory* el;
	Stack* next;
} Stack;