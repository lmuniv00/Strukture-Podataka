#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_NAME 25
#define MAX_SIZE 1024

struct _Element;
typedef struct _Element* Position;
typedef struct _Element{
	int coefficient;
	int exponent;
	Position next;
}Element;

int ReadFile(char* fileName, Position head1, Position head2);
int MakeList(char* buffer, Position head1);
Position CreateElement(int coefficient, int exponent);
int InsertSorted(Position NewElement, Position head);
int BeautifyList(Position head);
int Delete(Position head, Position current);
int Print(Position head);
int Addition(Position head1, Position head2, Position function);
int FreeMemory(Position head);
int Multiplication(Position head1, Position head2, Position function);

int main(void) {
	Element head1 = { .coefficient = 0, .exponent = 0, .next = NULL};
	Element head2 = { .coefficient = 0, .exponent = 0, .next = NULL};
	Element function = { .coefficient = 0, .exponent = 0, .next = NULL};
	char name[MAX_NAME] = { 0 };
	printf("Enter file name: ");
	scanf(" %s", name);
	ReadFile(name, &head1, &head2);
	printf("First polynome: ");
	Print(&head1);
	printf("Second polynome: ");
	Print(&head2);
	printf("Addition result is: ");
	Addition(&head1, &head2, &function);
	FreeMemory(&function);
	printf("Multiplication result is: ");
	Multiplication(&head1, &head2, &function);
	FreeMemory(&head1);
	FreeMemory(&head2);
	FreeMemory(&function);
	return EXIT_SUCCESS;
}
int ReadFile(char* fileName, Position head1, Position head2) {
	char buffer[MAX_SIZE] = { 0 };
	FILE* fp = NULL;
	fp = fopen(fileName, "r");
	if(!fp) {
		perror("File doesn't exist\n");
		return EXIT_FAILURE;
	}
	fgets(buffer, MAX_SIZE, fp);
	MakeList(buffer, head1);
	fgets(buffer, MAX_SIZE, fp);
	MakeList(buffer, head2);
	fclose(fp);
	return EXIT_SUCCESS;
}
int MakeList(char* buffer, Position head) {
	int coefficient = 0, exponent = 0, bytes = 0;
	char* current = buffer;
	Position NewElement = NULL;
	while(strlen(current) > 0) {
		if(sscanf(current, " %d %d %n", &coefficient, &exponent, &bytes) != 2) {
			printf("File line is not written correctly!\n");
			return EXIT_FAILURE;
		}
		NewElement = CreateElement(coefficient, exponent);
		if(!NewElement) {
			perror("Element can't be created!\n");
			return EXIT_FAILURE;
		}
		InsertSorted(NewElement, head);
		current += bytes;
	}
	BeautifyList(head);
	return EXIT_SUCCESS;
}
Position CreateElement(int coefficient, int exponent) {
	Position element = NULL;
	element = (Position)malloc(sizeof(Element));
	if(!element) {
		perror("Cannot allocate memory!\n");
		return element;
	}
	element->coefficient = coefficient;
	element->exponent = exponent;
	element->next = NULL;
	return element;
}
int InsertSorted(Position NewElement, Position head) {
	if(!head->next) {
		head->next = NewElement;
		return EXIT_SUCCESS;
	}
	Position tmp = head->next;
	Position current = head;
	while(tmp) {
		if(NewElement->exponent > tmp->exponent) {
			while(current->next != tmp)
				current = current->next;
			current->next = NewElement;
			NewElement->next = tmp;
			return EXIT_SUCCESS;
		}
		if(!tmp->next) {
			tmp->next = NewElement;
			return EXIT_SUCCESS;
		}
		tmp = tmp->next;
	}
}
int BeautifyList(Position head) {
	Position tmp = head->next;
	Position current = NULL;
	while(tmp) {
		current = tmp->next;
		while(current) {
			if(current->exponent == tmp->exponent) {
				tmp->coefficient += current->coefficient;
				Delete(head, current);
				current = tmp;
			}
			current = current->next;
		}
		tmp = tmp->next;
	}
	tmp = head->next;
	current = head;
	while(tmp) {
		if(!tmp->coefficient) {
			while(current->next != tmp)
				current = current->next;
			current->next = tmp->next;
			free(tmp);
		}
		tmp = tmp->next;
	}
	return EXIT_SUCCESS;
}
int Delete(Position head, Position current) {
	Position tmp = head->next;
	Position delete = current;
	while(tmp->next != delete)
		tmp = tmp->next;
	tmp->next = delete->next;
	free(delete);
	return EXIT_SUCCESS;
}
int Print(Position head) {
	Position tmp = head->next;
	while(tmp) {
		if(tmp->coefficient < 0)
			printf(" - ");
		if(tmp->coefficient != 1 && tmp->coefficient != -1)
			printf("%d", abs(tmp->coefficient));
		if(tmp->exponent < 0)
			printf("x^(%d)", tmp->exponent);
		else if(tmp->exponent > 0) {
			if(tmp->exponent == 1)
				printf("x");
			else
				printf("x^%d", tmp->exponent);
		}
		if(tmp->next && tmp->next->coefficient > 0)
			printf(" + ");
		tmp = tmp->next;
	}
	printf("\n");
	return EXIT_SUCCESS;
}
int Addition(Position head1, Position head2, Position function) {
	Position tmp1 = head1->next;
	Position tmp2 = head2->next;
	Position current = NULL;
	while(tmp1) {
		current = CreateElement(tmp1->coefficient, tmp1->exponent);
		InsertSorted(current, function);
		tmp1 = tmp1->next;
	}
	while(tmp2) {
		current = CreateElement(tmp2->coefficient, tmp2->exponent);
		InsertSorted(current, function);
		tmp2 = tmp2->next;
	}
	BeautifyList(function);
	Print(function);
	return EXIT_SUCCESS;
}
int FreeMemory(Position head) {
	Position current = head;
	Position delete = NULL;
	while(current->next) {
		delete = current->next;
		current->next = delete->next;
		free(delete);
	}
	return EXIT_SUCCESS;
}
int Multiplication(Position head1, Position head2, Position function) {
	Position tmp1 = head1->next;
	Position tmp2 = NULL;
	Position current = NULL;
	while(tmp1) {
		tmp2 = head2->next;
		while(tmp2) {
			current = CreateElement(tmp1->coefficient * tmp2->coefficient, tmp1->exponent + tmp2->exponent);
			InsertSorted(current, function);
			tmp2 = tmp2->next;
		}
		tmp1 = tmp1->next;
	}
	BeautifyList(function);
	Print(function);
	return EXIT_SUCCESS;
}