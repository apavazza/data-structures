#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_POINTS 30
#define MAX_STR_LEN 128
#define FAILED_TO_OPEN (-1)

typedef struct _student Student;
int numOfStudents(char filename[MAX_STR_LEN]);
Student* loadStudents(char filename[MAX_STR_LEN], int n);
float relPoints(float absPoints);
void printStudents(int n, Student* studentArray);

typedef struct _student
{
    char firstName[MAX_STR_LEN];
    char lastName[MAX_STR_LEN];
    float points;
} Student;

int numOfStudents(char filename[MAX_STR_LEN])
{
    // otvaranje datoteke
    FILE* f = NULL;
    f = fopen(filename, "r");
    if (!f)
    {
        printf("File %s could not be opened\n", filename);
        return FAILED_TO_OPEN;
    }

    // brojanje
    int n = 0;
    char buffer[1024];
    while (!feof(f))
    {
        fgets(buffer, 1024, f);
        if (strcmp(buffer, "\n") != 0) {
            n++;
        }
    }

    // zatvaranje datoteke
    fclose(f);

    return n;
}

Student* loadStudents(char filename[MAX_STR_LEN], int n)
{
    // otvaranje datoteke
    FILE* f = NULL;
    f = fopen(filename, "r");
    if (!f)
    {
        printf("File %s could not be opened\n", filename);
        return NULL;
    }

    // alociranje prostora
    Student* studentArray = (Student*)malloc(n * sizeof(Student));

    for (size_t i = 0; i < n; i++)
    {
        fscanf(f, "%s %s %f", studentArray[i].firstName, studentArray[i].lastName, &studentArray[i].points);
    }

    // zatvaranje datoteke
    fclose(f);

    return studentArray;
}

float relPoints(float absPoints)
{
    return absPoints / MAX_POINTS * 100;
}

void printStudents(int n, Student* studentArray)
{
    for (size_t i = 0; i < n; i++)
    {
        printf("%s %s %.1f %.2f\n", studentArray[i].firstName, studentArray[i].lastName, studentArray[i].points, relPoints(studentArray[i].points));
    }
}

int main(void)
{
    char filename[MAX_STR_LEN];
    printf("Please type in the filename: ");
    scanf(" %s", filename);

    // brojanje zapisa
    int n = numOfStudents(filename);
    if (n == FAILED_TO_OPEN)
    {
        return EXIT_FAILURE;
    }

    // ucitavanje zapisa
    Student* studentArray = NULL;
    studentArray = loadStudents(filename, n);

    if (studentArray == NULL)
    {
        return EXIT_FAILURE;
    }

    // ispis studenata
    printStudents(n, studentArray);

    // oslobadjanje prostora
    free(studentArray);

    return EXIT_SUCCESS;
}