#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct _Node;
typedef struct _Node* Position;
typedef struct _Node{
	int num;
	Position left;
	Position right;
}Node;

Position CreateNewElement(int number);
Position Insert(Position element, Position current);
int Print(Position current, FILE* fp);
int Replace(Position current);

int main(void) {
  	time_t t;
  	srand((unsigned) time(&t));
  	int v = 11 + rand() % 79;
	int head, status = 1, Choice, number, n;
	Node root = { .num = v, .left = NULL, .right = NULL};
	Position current = &root;
	Position q = NULL;
  	FILE* fp = NULL;
	fp = fopen("tree.txt", "w");
	printf("1 -> Create new element\n2 -> Print current tree\n"
	"3 -> Replace all elements with sum\n4 -> Exit program\n");
	while(status) {
		printf("Your choice: ");
		scanf("%d", &Choice);
		switch(Choice) {
			case (1):
				printf("Please enter desired size of tree: ");
				scanf("%d", &number);
        			for(int i=0; i<number; i++) {
          				n = 11 + rand() % 79;
				  	q = CreateNewElement(n);
				  	current = Insert(q, current);
        			}
				break;
			case (2):
        			fprintf(fp, "Numbers are:\n");
				printf("\nTree printed!\n");
				Print(current, fp);
        			printf("\n");
				break;
			case (3):
        			fprintf(fp, "\nSums of branches are:\n");
				printf("\nElements replaced with their sums!\n");
				Replace(current);
        			Print(current, fp);
        			printf("\n");
				break;
			case (4):
				printf("Exiting program...\n");
				status--;
				break;
			default:
				printf("Wrong input! Try again...\n");
				break;
		}
	}
  	fclose(fp);
	return EXIT_SUCCESS;
}
Position CreateNewElement(int number) {
	Position element = NULL;
	element = (Position)malloc(sizeof(Node));
	if(!element) {
		perror("Can't allocate memory!\n");
		return NULL;
	}
	element->num = number;
	element->left = NULL;
	element->right = NULL;
	return element;
}
Position Insert(Position element, Position current) {
	if(!current)
		return element;
	else if(current->num > element->num)
		current->right = Insert(element, current->right);
	else
		current->left = Insert(element, current->left);
	return current;
}
int Print(Position current, FILE* fp) {
	if(!current)
		return EXIT_SUCCESS;
	printf("%d ", current->num);
  	fprintf(fp, "%d ", current->num);
	Print(current->left, fp);
	Print(current->right, fp);
	return EXIT_SUCCESS;
}
int Replace(Position current) {
	int tmp = 0;
	if(current->left == NULL && current->right == NULL) {
		tmp = current->num;
		current->num = 0;
		return tmp;
	}
	else if(current->left == NULL) {
		tmp = current->num;
		current->num = Replace(current->right);
		return current->num + tmp;
	}
	else if(current->right == NULL) {
		tmp = current->num;
		current->num = Replace(current->left);
		return current->num + tmp;
	}
	else {
		tmp = current->num;
		current->num = Replace(current->left) + Replace(current->right);
		return current->num + tmp;
	}
}
