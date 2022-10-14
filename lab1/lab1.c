#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BR_BODOVA 30
#define MAX_STR_LEN 128
#define FAILED_TO_OPEN (-1)


typedef struct
{
    char ime[MAX_STR_LEN];
    char prezime[MAX_STR_LEN];
    float bodovi;
} Student;

int numOfStudents(char fileName[MAX_STR_LEN])
{
    // otvaranje datoteke
    FILE* f = NULL;
    f = fopen(fileName, "r");
    if (!f)
    {
        printf("Datoteku nije moguce otvoriti\n");
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

Student* loadStudents(char fileName[MAX_STR_LEN], int n, Student* studentArray)
{
    // otvaranje datoteke
    FILE* f = NULL;
    f = fopen(fileName, "r");
    if (!f)
    {
        printf("Datoteku nije moguce otvoriti\n");
        return NULL;
    }

    for (size_t i = 0; i < n; i++)
    {
        fscanf(f, "%s %s %f", studentArray[i].ime, studentArray[i].prezime, &studentArray[i].bodovi);
    }

    // zatvaranje datoteke
    fclose(f);

    return studentArray;
}

float relBodovi(float apsBodovi)
{
    return apsBodovi / MAX_BR_BODOVA * 100;
}

void printStudents(int n, Student* studentArray)
{
    for (size_t i = 0; i < n; i++)
    {
        printf("%s %s %.1f %.2f\n", studentArray[i].ime, studentArray[i].prezime, studentArray[i].bodovi, relBodovi(studentArray[i].bodovi));
    }
}

int main()
{
    char fileName[MAX_STR_LEN];
    printf("Molim upisati naziv datoteke: ");
    scanf(" %s", fileName);

    // brojanje zapisa
    int n = numOfStudents(fileName);
    if (n == FAILED_TO_OPEN) {
        return EXIT_FAILURE;
    }

    // alociranje prostora
    Student* studentArray = (Student*)malloc(n * sizeof(Student));

    // ucitavanje zapisa
    studentArray = loadStudents(fileName, n, studentArray);

    if (studentArray == NULL) {
        return EXIT_FAILURE;
    }

    // ispis studenata
    printStudents(n, studentArray);

    // oslobadjanje prostora
    free(studentArray);

    return EXIT_SUCCESS;
}