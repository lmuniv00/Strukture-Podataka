#include <stdio.h>
#include <stdlib.h>
#define NAME_SIZE 25
#define MAX_SIZE 1024

struct _Student;
typedef struct _Student* Position;
typedef struct _Student{
	int points;
	char name[NAME_SIZE];
	char surname[NAME_SIZE];
}Student;

int ReadFile(char name[]);
Position CreateStudent(char name[], int StudentNumber);
int MaxPoints(Position students, int StudentNumber);
double RelativePoints(int points, int max);

int main(void) {
	Position st = NULL;
	int line = 0, max = 0;
	char datname[MAX_SIZE] = "studentgrades.txt";
	line = ReadFile(datname);
	st = CreateStudent(datname, line);
	max = MaxPoints(st, line);
	for(int i=0; i<line; i++)
		printf("%s %s %d %.2lf\n", st[i].name, st[i].surname, st[i].points, RelativePoints(st[i].points, max));
	return EXIT_SUCCESS;
}
int ReadFile(char name[]) {
	int StudentNumber = 0;
	char buffer[MAX_SIZE] = { 0 };
	FILE* fp = NULL;
	fp = fopen(name, "r");
	if(!fp) {
		perror("Cannot open file!\n");
		return EXIT_FAILURE;
	}
	while(!feof(fp)) {
		fgets(buffer, 1024, fp);
		StudentNumber++;
	}
	fclose(fp);
	return StudentNumber;
}
Position CreateStudent(char name[], int StudentNumber) {
	Position ne = NULL;
	ne = (Position)malloc(StudentNumber*sizeof(Student));
	if(!ne) {
		perror("Cannot allocate memory!\n");
		return EXIT_SUCCESS;
	}
	int i = 0;
	FILE* fp = NULL;
	fp = fopen(name, "r");
	if(!fp) {
		perror("Cannot open file!\n");
		return EXIT_SUCCESS;
	}
	while(!feof(fp)) {
		fscanf(fp, "%s %s %d\n", ne[i].name, ne[i].surname, &ne[i].points);
		i++;
	}
	fclose(fp);
	return ne;
}
int MaxPoints(Position students, int StudentNumber) {
	int max = 0;
	for(int i=0; i<StudentNumber; i++)
		if(students[i].points > max)
			max = students[i].points;
	return max;
}
double RelativePoints(int points, int max) {
	return (double)points/(double)max*100;
}