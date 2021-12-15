#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE (20)

struct _Tree;
typedef struct _Tree* Root;
typedef struct _Tree{
	char* name;
	Root child;
	Root sibling;
}Tree;
struct _Stack;
typedef struct _Stack* Position;
typedef struct _Stack{
	Root directory;
	Position next;
	Position prev;
}Stack;

Root MakeDirectory(Root cFile);
Root cd(Root cFile, Position head);
Root FindByName(char* name, Root cFile);
int Push(Position head, Root directory);
Root Pop(Position head);
Root Back(Root cFile, Position head);
int Dir(Root cFile);

int main(void) {
	Root root;
  	root = (Root)malloc(sizeof(Tree));
  	root->child = NULL;
  	root->sibling = NULL;
  	root->name = "C:";
	Position head;
  	head = (Position)malloc(sizeof(Stack));
  	head->directory = NULL;
  	head->next = NULL;
  	head->prev = NULL;
  	int status = 1, choice;
  	printf("1 -> md <filename>\n");
	printf("2 -> cd <filename>\n");
	printf("3 -> cd..\n");
	printf("4 -> dir\n");
	printf("5 -> EXIT\n");
  	while(status) {
   		scanf("%d", &choice);
    		Root cFile = root;
    		switch (choice) {
      			case (1):
        			cFile = MakeDirectory(cFile);
        			break;
      			case (2):
        			cFile = cd(cFile, head);
        			break;
     			case (3):
        			cFile = Back(cFile, head);
        			break;
      			case (4):
        			Dir(cFile);
        			break;
      			case (5):
        			status--;
        			break;
      			default:
        			printf("Wrong input! Try again.\n");
    		}
  	}
  	return EXIT_SUCCESS;
}
Root MakeDirectory(Root cFile) {
	Root directory = NULL;
  	directory = (Root)malloc(sizeof(Tree));
	if (!directory) {
		perror("Can't allocate memory!");
    		return directory;
  	}
  	char name[MAX_SIZE] = { 0 };
  	printf("Enter the name of the directory: ");
  	scanf(" %s", name);
  	directory->name = name;
	directory->sibling = NULL;
	directory->child = NULL;
  	return directory;
}
Root cd(Root cFile, Position head) {
	Root sFile = NULL;
	char DirectoryName[MAX_SIZE] = { 0 };
  	printf("Enter the name of the directory: ");
	scanf(" %s", DirectoryName);
	if (!cFile->child) {
		perror("Mentioned file doesn't exist!\n");
		return cFile;
	}
	sFile = FindByName(DirectoryName, cFile);
	if (!sFile) {
		perror("Cannot find mentioned directory!\n");
		return cFile;
	}
	Push(head, cFile);
	return sFile;
}
Root FindByName(char* name, Root cFile) {
	if(!cFile->child) {
    		perror("Directory is empty!\n");
    		return cFile;
  	}
	cFile = cFile->child;
	while (strcmp(name, cFile->name) != 0 && cFile->sibling !=NULL)
		cFile = cFile->sibling;
	if (!strcmp(name, cFile->name)) {
    		printf("File not found!\n");
    		return EXIT_SUCCESS;
  	}
  	else
		return cFile;
}
int Push(Position head, Root directory) {
	Position q = NULL;
  	q = (Position)malloc(sizeof(Stack));
	q->next = head->next;
	q->prev = head;
	if (head->next != NULL)
		head = q;
	head->next = q;
	q->directory = directory;
  	free(q);
	return EXIT_SUCCESS;
}
Root Pop(Position head) {
	Position q = NULL;
  	q = (Position)malloc(sizeof(Stack));
	Root p;
	if (head->next == NULL)
		return EXIT_SUCCESS;
	q = head->next;
	p = q->directory;
	head->next = head->next->next;
	if(head->next!=NULL)
		head->next->prev = head;
	free(q);
	return p;
}
Root Back(Root cFile, Position head) {
	Root sFile;
	sFile = Pop(head);
	if (sFile == NULL)
		printf("Cannot leave root directory!\n");
	return cFile;
}
int Dir(Root cFile) {
	if (cFile->child == NULL) {
		printf("Empty directory!\n");
		return EXIT_SUCCESS;
	}
	cFile = cFile->child;
	printf("Directories: \n");
	printf("\t- %s\n", cFile->name);
	while (cFile->sibling != NULL) {
		printf("\t- %s\n", cFile->sibling->name);
		cFile = cFile->sibling;
	}	
	return EXIT_SUCCESS;
}