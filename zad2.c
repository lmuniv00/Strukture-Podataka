#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME 25

struct _Element;
typedef struct _Element* Position;
typedef struct _Element{
	char name[MAX_NAME];
	char surname[MAX_NAME];
	int BirthYear;
	Position next;
}Element;

Position CreateElement(char* name, char* surname, int BirthYear);
int AddToBeginning(Position head, Position current);
int AddToEnd(Position head, Position current);
int PrintList(Position head);
int FindBySurname(Position head, char* surname);
int DeleteBySurname(Position head, char* surname, int input);

int main(void) {
	Element head = { .name = { 0 }, .surname = { 0 }, .BirthYear = 0, .next = NULL};
	Position current = NULL;
	char newname[MAX_NAME] = { 0 };
	char newsurname[MAX_NAME] = { 0 };
	int status = 1, Choice, birthyear, input = 0;
	printf("1 -> Add element to beggining of list\n2 -> Add element to end of list\n");
	printf("3 -> Print list\n4 -> Find element by surname\n5 -> Delete element\n");
	printf("6 -> Exit program\n");
	while(status) {
		printf("\nYour choice: ");
		scanf("%d", &Choice);
		switch (Choice) {
			case 1:
				printf("Enter element name: ");
				scanf(" %s", newname);
				printf("Enter element surname: ");
				scanf(" %s", newsurname);
				printf("Enter element birth year: ");
				scanf("%d", &birthyear);
				current = CreateElement(newname, newsurname, birthyear);
				AddToBeginning(&head, current);
				break;
			case 2:
				printf("Enter element name: ");
				scanf(" %s", newname);
				printf("Enter element surname: ");
				scanf(" %s", newsurname);
				printf("Enter element birth year: ");
				scanf("%d", &birthyear);
				current = CreateElement(newname, newsurname, birthyear);
				AddToEnd(&head, current);
				break;
			case 3:
				PrintList(&head);
				break;
			case 4:
				printf("Enter element surname you wish to find: ");
				scanf(" %s", newsurname);
				FindBySurname(&head, newsurname);
				break;
			case 5:
				printf("Enter element surname you wish to delete: ");
				scanf(" %s", newsurname);
				printf("1 -> Delete all with %s surname\n", newsurname);
				printf("2 -> Delete only first with %s surname\n", newsurname);
				scanf("%d", &input);
				if(input != 1 && input != 2) {
					printf("Wrong input! Try again...\n");
					break;
				}
				DeleteBySurname(&head, newsurname, input);
				break;
			case 6:
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
Position CreateElement(char* name, char* surname, int BirthYear) {
	Position NewElement = NULL;
	NewElement = (Position)malloc(sizeof(Element));
	if(!NewElement) {
		perror("Cannot allocate memory!\n");
		return NewElement;
	}
	strcpy(NewElement->name, name);
	strcpy(NewElement->surname, surname);
	NewElement->BirthYear = BirthYear;
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
		printf("Name: %s\nSurname: %s\nBirth year: %d\n\n", tmp->name, tmp->surname, tmp->BirthYear);
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
				if(!tmp2->next)
					return EXIT_SUCCESS;
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
				return EXIT_SUCCESS;
			}
			tmp1 = tmp1->next;
			tmp2 = tmp2->next;
		}
	return EXIT_SUCCESS;
}