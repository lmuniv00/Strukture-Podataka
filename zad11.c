#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME 24
#define MAX_SIZE 1024

struct _City;
typedef struct _City* Position;
typedef struct _City {
	char name[MAX_NAME];
	int population;
	Position left;
	Position right;
}City;
struct _List;
typedef struct _List* Pointer;
typedef struct _List {
	char country[MAX_NAME];
	Pointer next;
	Position tree;
}List;
struct _Table;
typedef struct _Table* Sign;
typedef struct _Table {
    int key;
    Sign nextto;
    Pointer beneath;
}Table;

Pointer CountryCreate(char country[]);
int CountrySort(Pointer head, Pointer current);
int Cities(Pointer country, char cityfile[]);
int CreateCity(char cityname[], int population, Pointer country);
void InsertSorted(Position current, Position element);
void Print(Pointer head);
void PrintCities(Position tree);
Pointer FindCountry(Pointer head, char countryname[]);
void PrintCertainCities(Position tree, int num);
Sign CreateTableElement(int key);
Sign FindTableElement(int key, Sign head);

int main(void) {
	Pointer current = NULL;
	char buffer[MAX_SIZE] = { 0 };
	char filename[MAX_NAME] = { 0 };
	char country[MAX_NAME] = { 0 };
	char cityfile[MAX_NAME] = { 0 };
	Sign head = CreateTableElement(0);
	Sign tmp = head;
	for(int i=1; i<11; i++) {
	    tmp->nextto = CreateTableElement(i);
	    tmp = tmp->nextto;
	}
	printf("Enter file name: ");
	scanf(" %s", filename);
	FILE* fp = NULL;
	fp = fopen(filename, "r");
	if(!fp) {
	    perror("Cannot open file!\n");
	    return EXIT_FAILURE;
	}
	while (!feof(fp)) {
	    Sign TablePosition = NULL;
	    int CountryKey = 0;
		fgets(buffer, MAX_SIZE, fp);
		char* line = buffer;
		if(sscanf(line, " %s %s", country, cityfile) != 2) {
		    printf("File line not written correctly!\n");
		    return EXIT_FAILURE;
		}
		sscanf(line, " %s %s", country, cityfile);
		current = CountryCreate(country);
		for(int i=0; i<5; i++)
		    CountryKey += current->country[i];
		TablePosition = FindTableElement(CountryKey % 11, head);
		if(!TablePosition->beneath)
		    TablePosition->beneath = current;
		else
		    CountrySort(TablePosition->beneath, current);
		Cities(current, cityfile);
	}
	fclose(fp);
	tmp = NULL; 
	printf("Countries:\tCities:\n");
	for(int i=0; i<11; i++) {
	    tmp = FindTableElement(i, head);
	    if(tmp->beneath)
	        Print(tmp->beneath);
    }
	/*int choice, status = 1, num;
	char countryname[MAX_NAME] = { 0 };
	Position city = NULL;
	current = NULL;
	printf("\n1 -> Select country\n2 -> List cities\n3 -> Exit program\n");
	while(status) {
		printf("\nYour choice: ");
		scanf("%d", &choice);
		switch (choice) {
			case 1:
				printf("\nEnter the name of desired country: ");
				scanf(" %s", countryname);
				current = FindCountry(&head, countryname);
				if(!current)
					printf("\nCountry doesn't exist!");
				else
					printf("\nCountry found!");
				break;
			case 2:
				if(!current) {
					printf("Country not selected!\n");
					break;
				}
				printf("\nInsert population number: ");
				scanf("%d", &num);
				printf("\nCities with bigger population than %d are:\n", num);
				PrintCertainCities(current->tree, num);
				break;
			case 3:
				status--;
				printf("\nExiting program...");
				break;
			default:
				printf("\nWrong input! Please select valid input.\n");
				break;
		}
	}*/
	return EXIT_SUCCESS;
}
Pointer CountryCreate(char country[]) {
	Pointer newElement = NULL;
	newElement = (Pointer)malloc(sizeof(List));
	if (!newElement) {
		perror("Can't allocate memory!\n");
		return newElement;
	}
	strcpy(newElement->country, country);
	newElement->next = NULL;
	newElement->tree = NULL;
	return newElement;
}
int CountrySort(Pointer head, Pointer current) {
	if(!head->next) {
		head->next = current;
		return EXIT_SUCCESS;
	}
	Pointer tmp = head;
	while(tmp) {
		if(strcmp(tmp->country, current->country) > 0) {
			Pointer tmp2 = head;
			while(tmp2->next != tmp)
				tmp2 = tmp2->next;
			tmp2->next = current;
			current->next = tmp;
			return EXIT_SUCCESS;
		}
		else if(!tmp->next) {
			tmp->next = current;
			return EXIT_SUCCESS;
		}
		tmp = tmp->next;
	}
}
int Cities(Pointer country, char cityfile[]) {
	char buffer[MAX_SIZE] = { 0 };
	char cityname[MAX_NAME] = { 0 };
	int population;
	Position element = NULL;
	FILE* fp = NULL;
	fp = fopen(cityfile, "r");
	if(!fp) {
		perror("Cannot open file!\n");
		return EXIT_FAILURE;
	}
	while(!feof(fp)) {
		fgets(buffer, MAX_SIZE, fp);
		char* line = buffer;
		if(sscanf(line, " %s %d", cityname, &population) != 2) {
			printf("File line not written correctly!\n");
			return EXIT_FAILURE;
		}
		sscanf(line, " %s %d", cityname, &population);
		CreateCity(cityname, population, country);
	}
	fclose(fp);
	return EXIT_SUCCESS;
}
int CreateCity(char cityname[], int population, Pointer country) {
	Position newElement = NULL;
	newElement = (Position)malloc(sizeof(City));
	if(!newElement) {
		perror("Cannot allocate memory!\n");
		return EXIT_FAILURE;
	}
	strcpy(newElement->name, cityname);
	newElement->population = population;
	newElement->left = NULL;
	newElement->right = NULL;
	if(!country->tree)
		country->tree = newElement;
	else
		InsertSorted(country->tree, newElement);
	return EXIT_SUCCESS;
}
void InsertSorted(Position current, Position element) {
	if(current->population < element->population && !current->right)
		current->right = element;
	else if(current->population > element->population && !current->left)
		current->left = element;
	else if(current->population < element->population)
		InsertSorted(current->right, element);
	else if(current->population > element->population)
		InsertSorted(current->left, element);
}
void Print(Pointer head) {
	Pointer tmp = head;
	while(tmp) {
		printf("%s\t", tmp->country);
		PrintCities(tmp->tree);
		printf("\n");
		tmp = tmp->next;
	}
}
void PrintCities(Position tree) {
	if(!tree)
		return;
	PrintCities(tree->right);
	printf("%s (%d)\t", tree->name, tree->population);
	PrintCities(tree->left);
}
Pointer FindCountry(Pointer head, char countryname[]) {
	Pointer tmp = head->next;
	while(tmp) {
		if(!strcmp(tmp->country, countryname))
			return tmp;
		tmp = tmp->next;
	}
	return tmp;
}
void PrintCertainCities(Position tree, int num) {
	if(!tree)
		return;
	PrintCertainCities(tree->right, num);
	if(tree->population < num)
		return;
	printf("%s (%d)\t", tree->name, tree->population);
	if(tree->population > num)
		PrintCertainCities(tree->left, num);
}
Sign CreateTableElement(int key) {
    Sign newElement = NULL;
    newElement = (Sign)malloc(sizeof(Table));
    if(!newElement) {
        perror("Cannot allocate memory!\n");
        return newElement;
    }
    newElement->key = key;
    newElement->nextto = NULL;
    newElement->beneath = NULL;
    return newElement;
}
Sign FindTableElement(int key, Sign head) {
    Sign tmp = head;
    while(key != tmp->key)
        tmp = tmp->nextto;
    return tmp;
}