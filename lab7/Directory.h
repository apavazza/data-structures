/**
* Directory library
*
* @author Amadeo Pavazza
* @author Petar Zadric
*/

#pragma once
#define MAX_STR_LEN 1024

struct _stack;
typedef struct _stack Stack;
struct _directory;
typedef struct _directory Directory;
bool md(Directory* current, char* name);
Directory* allocateDirectory(char* name);
Directory* cd_dir(Directory* current, Stack* head, char* name);
Directory* cd_previous(Directory* current, Stack* head);
bool dir(Directory* current, Stack* head, char* path);
void deleteAllDir(Directory* dir);
void updatePath(Directory* current, Stack* head, char* path);

typedef struct _directory {
	char name[MAX_STR_LEN];
	Directory* sibling;
	Directory* child;
} Directory;