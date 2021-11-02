#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include<ctype.h>
#define MAX 1024

typedef struct _Person {
	char name[MAX];
	char surname[MAX];
	int birthYear;
	struct _Person* next;
}Person;

int MainMenu(Person*);
int BeginningInsert(Person*);
int PrintList(Person*);
int InsertEnd(Person*);
int Delete(Person*, Person*);
int AddAfterElement(Person*, Person*);
int AddInfrontElement(Person*, Person*);
int Sort(Person*);
int ReadFile(Person*);
int WriteFile(Person*);
Person* FindLast(Person*);
Person* FindSurname(Person*, char*);
Person* FindBefore(Person*, Person*);

int main()
{
	Person* head;
	head = (Person*)malloc(sizeof(Person));
	head->next = NULL;
	int status = 0;
	do {
		status = MainMenu(head);
	} while (!status);
	return 0;
}

int MainMenu(Person* head)
{
	int Choice;
	
	char surname[MAX];
	Person* find_surname = NULL;
	find_surname = (Person*)malloc(sizeof(Person));
	
	char delete[MAX];
	Person* delete_el = NULL;
	delete_el = (Person*)malloc(sizeof(Person));

	char after[MAX];
	Person* add_after = NULL;
	add_after = (Person*)malloc(sizeof(Person));

	char front[MAX];
	Person* add_front = NULL;
	add_front = (Person*)malloc(sizeof(Person));
	
	printf("██████████████████████████████████\n");
	printf("1 - Insert element at beginning\n");
	printf("2 - Insert element at end\n");
	printf("3 - Print list\n");
	printf("4 - Find surname\n");
	printf("5 - Delete surname\n");
	printf("6 - Add element after\n");
	printf("7 - Add element before\n");
	printf("8 - Sort\n");
	printf("9 - Read file\n");
	printf("10 - Write file\n");
	printf("11 - Turn off program\n");
	printf("██████████████████████████████████\n");

	while (1) {

		printf("\nChoose option based on number\nTo see Main Menu again choose 0\n");
		scanf(" %d", &Choice);

		switch (Choice) {
		case (1): BeginningInsert(head);
			break;

		case (2): InsertEnd(head);
			break;

		case (3): PrintList(head);
			break;

		case(4): printf("\n\nWhat surname do you need? ");
			scanf("%s", surname);
			find_surname = FindSurname(head, surname);
			printf("\nElement you searched:\nName: %s\nSurname: %s\nBirth year: %d\n", find_surname->name, find_surname->surname, find_surname->birthYear);
			break;

		case(5): printf("\n\nWhich surname do you wish to delete? ");
			scanf("%s", delete);
			delete_el = FindSurname(head, delete);
			Delete(head, delete_el);
			break;

		case (6): printf("\nAfter what surname do you wish to add element? ");
			scanf("%s", after);
			add_after = FindSurname(head, after);
			AddAfterElement(head, add_after);
			break;

		case(7): printf("\nIn front of what surname do you wish to add element? ");
			scanf("%s", front);
			add_front = FindSurname(head, front);
			AddInfrontElement(head, add_front);
			break;

		case(8): Sort(head);
			break;

		case(9): ReadFile(head);
			break;

		case(10): WriteFile(head);
			break;

		case(0):
			return 0;

		case (11):
			return 1;

		default: printf("\n\nWrong input! Try again.");
		}
	}

	return 0;
}

int BeginningInsert(Person* head)
{
	Person* p;
	p = (Person*)malloc(sizeof(Person));
	p->next = head->next;
	head->next = p;
	printf("Insert name: ");
	scanf("%s", p->name);
	printf("Insert surname: ");
	scanf("%s", p->surname);
	printf("Insert birth year: ");
	scanf("%d", &p->birthYear);
	printf("\n");
	return EXIT_SUCCESS;
}

int PrintList(Person* head)
{
	Person* p = head->next;
	printf("\n█████████████████████████████████\n");
	while (p != NULL) {
		printf("\tName: %s", p->name);
		printf("\n\tSurname: %s", p->surname);
		printf("\n\tBirth year: %d\n", p->birthYear);
		printf("\n");
		p = p->next;
	}
	printf("█████████████████████████████████");
	return EXIT_SUCCESS;
}

int InsertEnd(Person* head)
{
	Person* s;
	s = (Person*)malloc(sizeof(Person));
	Person* p;
	p = (Person*)malloc(sizeof(Person));
	p = FindLast(head);
	s->next = NULL;
	p->next = s;

	printf("Insert name: ");
	scanf("%s", s->name);
	printf("Insert surname: ");
	scanf("%s", s->surname);
	printf("Insert birth year: ");
	scanf("%d", &s->birthYear);
	printf("\n");

	return EXIT_SUCCESS;
}

Person* FindLast(Person* head)
{
	Person* p = head;
	while (p != NULL && p->next != NULL)
		p = p->next;
	return p;
}

Person* FindSurname(Person* head, char* surname)
{
	Person* P = head->next;
	while (P != NULL && strcmp(P->surname, surname))
		P = P->next;
	return P;
}

Person* FindBefore(Person* head, Person* element)
{
	Person* P;
	P = head;
	while (P != NULL && P->next != element)
		P = P->next;
	return P;
}

int Delete(Person* head, Person* element)
{
	Person* P = NULL;
	Person* q = NULL;
	P = (Person*)malloc(sizeof(Person));
	q = (Person*)malloc(sizeof(Person));
	q = element;
	P = FindBefore(head, element);
	P->next = q->next;
	free(q);
	return EXIT_SUCCESS;
}

int AddAfterElement(Person* head, Person* element)
{
	Person* new;
	new = (Person*)malloc(sizeof(Person));
	printf("Insert name: ");
	scanf("%s", new->name);
	printf("Insert surname: ");
	scanf("%s", new->surname);
	printf("Insert birth year: ");
	scanf("%d", &new->birthYear);
	printf("\n");
	new->next = element->next;
	element->next = new;
	return 0;
}

int AddInfrontElement(Person* head, Person* element)
{
	Person* new;
	new = (Person*)malloc(sizeof(Person));
	Person *P = NULL;
	P = (Person*)malloc(sizeof(Person));
	P = FindBefore(head, element);
	P->next = new;
	new->next = element;
	printf("Insert name: ");
	scanf("%s", new->name);
	printf("Insert surname: ");
	scanf("%s", new->surname);
	printf("Insert birth year: ");
	scanf("%d", &new->birthYear);
	printf("\n");
	return EXIT_SUCCESS;
}

int Sort(Person * head)
{
	Person * p = head;
	Person * q = NULL;
	Person * bef_q = NULL;
	Person * last = NULL;
	while (p->next != last)
	{
		bef_q = p;
		q = bef_q->next;
		while (q->next != last)
		{
			if (strcmp(q->surname, q->next->surname) > 0)
			{
				bef_q->next = q->next->next;
				bef_q->next->next = q;
				q = bef_q->next;
			}
			bef_q = q;
			q = q->next;
		}
		last = q;
	}
	return EXIT_SUCCESS;
}

int ReadFile(Person* head)
{
	Person* q;
	Person* p = FindLast(head);
	FILE* fp = NULL;
	fp = fopen("file.txt", "r");
	int num = 0;
	int i = 0;
	char buffer[MAX] = { 0 };
	if (fp == NULL) {
		printf("Can't open file!\n");
		return -1;
	}
	while (fgets(buffer, MAX, fp)) {
		num++;
	}
	rewind(fp);
	for(i=0; i<num; i++) {
		q = (Person*)malloc(sizeof(Person));
		q->next = NULL;
		p->next = q;
		p = p->next;
		fscanf(fp, "%s %s %d", q->name, q->surname, &q->birthYear);		
	}
	fclose(fp);
	return EXIT_SUCCESS;
}

int WriteFile(Person* head)
{
	Person* q = NULL;
	q = (Person*)malloc(sizeof(Person));
	q = head->next;
	FILE* fp = NULL;
	fp = fopen("file.txt", "w");
	if (fp == NULL) {
		printf("Can't open file!\n");
		return -1;
	}
	while (q != NULL) {
		fprintf(fp, "Name: %s \tSurname: %s \tBirth year: %d\n", q->name, q->surname, q->birthYear);
		q = q->next;
	}
	fclose(fp);
	return EXIT_SUCCESS;
}
