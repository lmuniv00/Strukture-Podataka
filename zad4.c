#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAX_SIZE (50)
#define MAX_LINE (1024)

struct _Element;
typedef struct _Element* Position;
typedef struct _Element {
	int coefficient;
	int exponent;
	Position next;
} Element;

int ReadFile(Position head1, Position head2, char* fileName);
int StringToList(Position head, char* buffer);
Position CreateElement(int coefficient, int exponent);
int InsertSorted(Position head, Position newElement);
int MergeAfter(Position position, Position newElement);
int InsertAfter(Position position, Position newElement);
int DeleteAfter(Position position);
int PrintPoly(char* name, Position first);
int ResultAdd(Position Addition, Position head1, Position head2);
int CreateAndInsertAfter(int coefficient, int exponent, Position position);
int ResultMultiply(Position Multiplication, Position head1, Position head2);

int main() {
	
	Element head1 = { .coefficient = 0, .exponent = 0, .next = NULL };
	Element head2 = { .coefficient = 0, .exponent = 0, .next = NULL };
	Element Addition = { .coefficient = 0, .exponent = 0, .next = NULL };
	Element Multiplication = { .coefficient = 0, .exponent = 0, .next = NULL };
	char fileName[MAX_SIZE];
    printf("Enter file name: ");
	scanf(" %s", fileName);
	ReadFile(&head1, &head2, fileName);
  PrintPoly("First polinome: ", head1.next);
	PrintPoly("Second polinome: ", head2.next);
	ResultAdd(&Addition, &head1, &head2);
	ResultMultiply(&Multiplication, &head1, &head2);
  PrintPoly("Result of addition is: ", Addition.next);
	PrintPoly("Result of multiplication is: ", Multiplication.next);
  return EXIT_SUCCESS;
}
int ReadFile(Position head1, Position head2, char* fileName) {
	FILE* file = NULL;
	char buffer[MAX_LINE];
	file = fopen(fileName, "r");
  if(!file) {
    perror("Error!");
    return -1;
  }
  fgets(buffer, MAX_LINE, file);
  StringToList(head1, buffer);
  fgets(buffer, MAX_LINE, file);
  StringToList(head2, buffer);
  fclose(file);
	return EXIT_SUCCESS;
}
int StringToList(Position head, char* buffer) {
  char* current = buffer;
  int coefficient = 0;
  int exponent = 0;
  int bytes = 0;
  Position newElement;
  while(strlen(current) > 0) {
    if(sscanf(current, " %d %d %n", &coefficient, &exponent, &bytes) != 2) {
      perror("File not good!\n");
      return -1;
    }
    newElement = CreateElement(coefficient, exponent);
    if(!newElement)
      return EXIT_FAILURE;
    InsertSorted(head, newElement);
    current += bytes;
  }
  return EXIT_SUCCESS;
}
Position CreateElement(int coefficient, int exponent) {
  Position element = NULL;
  element = (Position)malloc(sizeof(Element));
  if(!element) {
    perror("Can't allocate memory!\n");
    return element;
  }
  element->coefficient = coefficient;
  element->exponent = exponent;
  element->next = NULL;
  return element;
}
int InsertSorted(Position head, Position newElement) {
  Position tmp = head;
  while((tmp->next->exponent && tmp->next != NULL) < newElement->exponent)
    tmp = tmp->next;
  MergeAfter(tmp, newElement);
}
int MergeAfter(Position position, Position newElement) {
  if (position->next == NULL || position->next->exponent != newElement->exponent)
    InsertAfter(position, newElement);
  else {
    int addition = position->next->coefficient + newElement->coefficient;
    if(addition != 0)
      position->next->coefficient = addition;
    else
      DeleteAfter(position);
    free(newElement);
  }
  return EXIT_SUCCESS;
}
int InsertAfter(Position position, Position newElement) {
	newElement->next = position->next;
	position->next = newElement;
	return EXIT_SUCCESS;
}
int DeleteAfter(Position position)
{
	Position toDelete = NULL;
	toDelete = position->next;
	position->next = toDelete->next;
	free(toDelete);
	return EXIT_SUCCESS;
}
int PrintPoly(char* name, Position first) {
	printf(" %s = ", name);
	if (first) {
		if (first->exponent < 0) {
			if (first->coefficient == 1) {
				printf("x^(%d)", first->exponent);
			}
			else {
				printf("%dx^(%d)", first->coefficient, first->exponent);
			}
		}
		else {
			if (first->coefficient == 1) {
				printf("x^%d", first->exponent);
			}
			else {
				printf("%dx^%d", first->coefficient, first->exponent);
			}
		}
		first = first->next;
	}
	for (; first != NULL; first = first->next) {
		if (first->coefficient < 0) {
			if (first->exponent < 0) {
				printf(" - %dx^(%d)", abs(first->coefficient), first->exponent);
			}
			else {
				printf(" - %dx^%d", abs(first->coefficient), first->exponent);
			}
		}
		else {
			if (first->exponent < 0) {
				if (first->coefficient == 1) {
					printf(" + x^(%d)", first->exponent);
				}
				else {
					printf(" + %dx^(%d)", first->coefficient, first->exponent);
				}
			}
			else {
				if (first->coefficient == 1) {
					printf(" + x^%d", first->exponent);
				}
				else {
					printf(" + %dx^%d", first->coefficient, first->exponent);
				}
			}
		}
	}
	printf("\n");
	return EXIT_SUCCESS;
}
int ResultAdd(Position Addition, Position head1, Position head2) {
  Position i = head1->next;
	Position j = head2->next;
	Position k = Addition;
	Position tmp = NULL;
	while (i != NULL && j != NULL) {
		if (i->exponent == j->exponent) {
			CreateAndInsertAfter(i->coefficient + j->coefficient, i->exponent, k);
			i = i->next;
			j = j->next;
		}
		else if (i->exponent < j->exponent) {
			CreateAndInsertAfter(i->coefficient, i->exponent, k);
			i = i->next;
		}
		else {
			CreateAndInsertAfter(j->coefficient, j->exponent, k);
			j = j->next;
		}
	}
	if (i == NULL) {
		tmp = j;
	}
	else {
		tmp = i;
	}
	while (tmp != NULL) {
		CreateAndInsertAfter(tmp->coefficient, tmp->exponent, k);
		tmp = tmp->next;
	}
	return EXIT_SUCCESS;
}
int CreateAndInsertAfter(int coefficient, int exponent, Position position) {
	Position newElement = CreateElement(coefficient, exponent);
	if (!newElement) {
		return EXIT_FAILURE;
	}
	InsertAfter(position, newElement);
	position = position->next;
	return EXIT_SUCCESS;
}
int ResultMultiply(Position Multiplication, Position head1, Position head2) {
	Position i = NULL;
	Position j = NULL;
	for (i = head1->next; i != NULL; i = i->next) {
		for (j = head2->next; j != NULL; j = j->next) {
			Position newElement = CreateElement(i->coefficient * j->coefficient, i->exponent + j->exponent);
			if (!newElement)
				return EXIT_FAILURE;
			InsertSorted(Multiplication, newElement);
		}
	}
	return EXIT_SUCCESS;
}
int FreeMemory(Position head) {
	Position tmp = head;
	while (tmp->next) {
		DeleteAfter(tmp);
	}
	return EXIT_SUCCESS;
}
