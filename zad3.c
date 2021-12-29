#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME 25
#define MAX_SIZE 1024

struct _Element;
typedef struct _Element* Position;
typedef struct _Element{
	char name[MAX_NAME];
	char surname[MAX_NAME];
	int BirthYear;
	Position next;
}Element;

Position CreateElement();
int AddToBeginning(Position head, Position current);
int AddToEnd(Position head, Position current);
int PrintList(Position head);
int FindBySurname(Position head, char* surname);
int DeleteBySurname(Position head, char* surname, int input);
Position FindElement(Position head, char* surname);
int AddAfter(Position head, char* surname);
int AddInFront(Position head, char* surname);
int WriteInFile(Position head);
int ReadFromFile();

int main(void) {
	Element head = { .name = { 0 }, .surname = { 0 }, .BirthYear = 0, .next = NULL};
	Position current = NULL;
	char surname[MAX_NAME] = { 0 };
	int status = 1, Choice, input = 0;
	printf("1 -> Add element to beggining of list\n2 -> Add element to end of list\n");
	printf("3 -> Print list\n4 -> Find element by surname\n5 -> Delete element\n");
	printf("6 -> Add after surname\n7 -> Add before surname\n");
	printf("8 -> Write in file\n9 -> Read from file\n10 -> Exit program\n");
	while(status) {
		printf("\nYour choice: ");
		scanf("%d", &Choice);
		switch (Choice) {
			case 1:
				current = CreateElement();
				AddToBeginning(&head, current);
				break;
			case 2:
				current = CreateElement();
				AddToEnd(&head, current);
				break;
			case 3:
				PrintList(&head);
				break;
			case 4:
				printf("Enter element surname you wish to find: ");
				scanf(" %s", surname);
				FindBySurname(&head, surname);
				break;
			case 5:
				printf("Enter element surname you wish to delete: ");
				scanf(" %s", surname);
				printf("1 -> Delete all with %s surname\n", surname);
				printf("2 -> Delete only first with %s surname\n", surname);
				scanf("%d", &input);
				if(input != 1 && input != 2) {
					printf("Wrong input! Try again...\n");
					break;
				}
				DeleteBySurname(&head, surname, input);
				break;
			case 6:
				printf("Add after which surname: ");
				scanf(" %s", surname);
				AddAfter(&head, surname);
				break;
			case 7:
				printf("Add before which surname: ");
				scanf(" %s", surname);
				AddInFront(&head, surname);
				break;
			case 8:
				WriteInFile(&head);
				printf("Text file written!\n");
				break;
			case 9:
				printf("File read!");
				ReadFromFile();
				break;
			case 10:
				status--;
				printf("Exiting program...\n");
				break;
			default:
				printf("Wrong input! Please select valid input...\n");
				break;
		}
	}
	return EXIT_SUCCESS;
}
Position CreateElement() {
	Position NewElement = NULL;
	NewElement = (Position)malloc(sizeof(Element));
	if(!NewElement) {
		perror("Cannot allocate memory!\n");
		return NewElement;
	}
	char name[MAX_NAME] = { 0 };
	int birthyear;
	printf("Enter element name: ");
	scanf(" %s", name);
	strcpy(NewElement->name, name);
	printf("Enter element surname: ");
	scanf(" %s", name);
	strcpy(NewElement->surname, name);
	printf("Enter element birth year: ");
	scanf("%d", &birthyear);
	NewElement->BirthYear = birthyear;
	NewElement->next = NULL;
	return NewElement;
}
int AddToBeginning(Position head, Position current) {
	if(head->next == NULL)
		head->next = current;
	else {
		Position tmp = head->next;
		head->next = current;
		current->next = tmp;
	}
	return EXIT_SUCCESS;
}
int AddToEnd(Position head, Position current) {
	Position tmp = head;
	while(tmp->next)
		tmp = tmp->next;
	tmp->next = current;
	return EXIT_SUCCESS;
}
int PrintList(Position head) {
	Position tmp = head->next;
	if(!head->next) {
		printf("Empty list!\n");
		return EXIT_SUCCESS;
	}
	while(tmp) {
		printf("\nName: %s\nSurname: %s\nBirth year: %d\n", tmp->name, tmp->surname, tmp->BirthYear);
		tmp = tmp->next;
	}
	return EXIT_SUCCESS;
}
int FindBySurname(Position head, char* surname) {
	int number = 0;
	Position tmp = head->next;
	while(tmp) {
		if(!strcmp(tmp->surname, surname)) {
			printf("Name: %s\nSurname: %s\nBirth year: %d\n\n", tmp->name, tmp->surname, tmp->BirthYear);
			number++;
		}
		tmp = tmp->next;
	}
	if(!number)
	    printf("Surname doesn't exist!\n");
	else
	    printf("Found a total of %d elements.\n", number);
	return EXIT_SUCCESS;
}
int DeleteBySurname(Position head, char* surname, int input) {
	Position tmp1 = head->next;
	Position tmp2 = head;
	if(input == 1)
		while(tmp1) {
			while(!strcmp(tmp1->surname, surname)) {
				tmp2->next = tmp1->next;
				free(tmp1);
				if(!tmp2->next) {
					printf("Elements deleted successfully!\n");
					return EXIT_SUCCESS;
				}
				tmp1 = tmp2->next;
			}
			tmp1 = tmp1->next;
			tmp2 = tmp2->next;
		}
	else if(input == 2)
		while(tmp1) {
			if(!strcmp(tmp1->surname, surname)) {
				tmp2->next = tmp1->next;
				free(tmp1);
				printf("Elements deleted successfully!\n");
				return EXIT_SUCCESS;
			}
			tmp1 = tmp1->next;
			tmp2 = tmp2->next;
		}
	return EXIT_SUCCESS;
}
Position FindElement(Position head, char* surname) {
	Position tmp = head;
	while(tmp) {
	if(!strcmp(tmp->surname, surname))
			return tmp;
		tmp = tmp->next;
	}
	if(!tmp)
		printf("Surname doesn't exist!\n");
	return tmp;
}
int AddAfter(Position head, char* surname) {
	Position current = FindElement(head, surname);
	if(!current) {
		printf("Please input existing surname...\n");
		return EXIT_FAILURE;
	}
	Position tmp = head;
	Position NewElement = CreateElement();
	while(tmp) {
		if(tmp == current) {
			tmp = current->next;
			current->next = NewElement;	
			NewElement->next = tmp;
			return EXIT_SUCCESS;
		}
		tmp = tmp->next;
	}
}
int AddInFront(Position head, char* surname) {
	Position current = FindElement(head, surname);
	if(!current) {
		printf("Please input existing surname...\n");
		return EXIT_FAILURE;
	}
	Position tmp = head;
	Position NewElement = CreateElement();
	while(tmp) {
		if(tmp->next == current) {
			tmp->next = NewElement;
			NewElement->next = current;
			return EXIT_SUCCESS;
		}
		tmp = tmp->next;	
	}
}
int WriteInFile(Position head) {
	Position tmp = head->next;
	FILE* fp = NULL;
	fp = fopen("elements.txt", "w");
	while(tmp) {
		fprintf(fp, "\n%s\t %s\t %d", tmp->name, tmp->surname, tmp->BirthYear);
		tmp = tmp->next;
	}
	fclose(fp);
	return EXIT_SUCCESS;
}
int ReadFromFile() {
	char name[MAX_NAME] = { 0 };
	char surname[MAX_NAME] = { 0 };
	int BirthYear;
	FILE* fp = NULL;
	fp = fopen("elements.txt", "r");
	if(!fp) {
		perror("Cannot open file!\n");
		return EXIT_SUCCESS;
	}
	while(!feof(fp)) {
		fscanf(fp, "%s %s %d", name, surname, &BirthYear);	
		printf("\n%s\t %s\t %d", name, surname, BirthYear);
	}
	fclose(fp);
	return EXIT_SUCCESS;
}