#include "declarations.h"
#include <stdio.h>
#include <stdlib.h>

Position CreateStackElement(double number) {
	Position newElement = NULL;
	newElement = (Position)malloc(sizeof(StackElement));
	if (!newElement) {
		perror("Can't allocate memory!\n");
		return NULL;
	}
	newElement->number = number;
	newElement->next = NULL;
	return newElement;
}
int InsertAfter(Position position, Position newElement) {
	newElement->next = position->next;
	position->next = newElement;
	return EXIT_SUCCESS;
}
int Push(Position head, double number) {
	Position newElement = NULL;
	newElement = CreateStackElement(number);
	if (!newElement)
		return -1;
	InsertAfter(head, newElement);
	return EXIT_SUCCESS;
}
int DeleteAfter(Position position) {
	Position temp = position->next;
	if (!temp)
		return EXIT_SUCCESS;
	position->next = temp->next;
	free(temp);
	return EXIT_SUCCESS;
}
int Pop(double* destination, Position head) {
	Position first = head->next;
	if (!first) {
		perror("Postfix not valid! Please check your file!\n");
		return -1;
	}
	*destination = first->number;
	DeleteAfter(head);
	return EXIT_SUCCESS;
}
int PerformOperation(Position head, char operation) {
	double operand2 = 0;
	double operand1 = 0;
	double result = 0;
	int status1 = EXIT_SUCCESS;
	int status2 = EXIT_SUCCESS;
	status2 = Pop(&operand2, head);
	if (status2 != EXIT_SUCCESS)
		return -1;
	status1 = Pop(&operand1, head);
	if (status1 != EXIT_SUCCESS)
		return -2;
	switch (operation) {
	case '+': {
		result = operand1 + operand2;
		break;
	}
	case '-': {
		result = operand1 - operand2;
		break;
	}
	case '*': {
		result = operand1 * operand2;
		break;
	}
	case '/': {
		if (operand2 == 0) {
			printf("Cannot divide with 0!\n");
			return -3;
		}
		result = operand1 / operand2;
		break;
	}
	default:
		printf("This operator is not supported yet!\n");
		return -4;
	}
	Push(head, result);
	return EXIT_SUCCESS;
}
int CalculatePostfixFile(double* destination, char* fileName) {
	FILE* file = NULL;
	int fileLength = 0;
	char* buffer = NULL;
	char* currentBuffer = NULL;
	int numBytes = 0;
	char operation = 0;
	int number = 0;
	int status = 0;
	StackElement head = { .next = NULL, .number = 0 };
	file = fopen(fileName, "rb");
	if (!file) {
		perror("Can't open file!\n");
		return -1;
	}
	fseek(file, 0, SEEK_END);
	fileLength = ftell(file);
	buffer = (char*)calloc(fileLength + 1, sizeof(char));
	if (!buffer) {
		perror("Can't allocate memory!\n");
		return NULL;
	}
	rewind(file);
	fread(buffer, sizeof(char), fileLength, file);
	printf("|%s|\n", buffer);
	fclose(file);
	currentBuffer = buffer;
	while (strlen(currentBuffer > 0)) {
		status = sscanf(currentBuffer, " %lf %n", &number, &numBytes);
		if (status == 1) {
			status = Push(&head, number);
			if (status != EXIT_SUCCESS) {
				free(buffer);
				DeleteAll(&head);
				return -3;
			}
			currentBuffer += numBytes;
		}
		else {
			sscanf(currentBuffer, " %c %n", &operation, &numBytes);
			status = PerformOperation(&head, operation);
			if (status != EXIT_SUCCESS) {
				free(buffer);
				DeleteAll(&head);
				return -1;
			}
			currentBuffer += numBytes;
		}
	}
	free(buffer);
	status = Pop(resultDestination, &head);
	if (status != EXIT_SUCCESS) {
		DeleteAll(&head);
		return -5;
	}
	if (head.next) {
		printf("Postfix not valid! Please check your file!\n");
		DeleteAll(&head);
		return -6;
	}
	return EXIT_SUCCESS;
}
int DeleteAll(Position head) {
	while (head->next)
		DeleteAfter(head);
	return EXIT_SUCCESS;
}
