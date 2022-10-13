#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BR_BODOVA 30

typedef struct
{
    char ime[20];
    char prezime[20];
    float bodovi;
} Student;

float relBodovi(float apsBodovi)
{
    return apsBodovi / MAX_BR_BODOVA * 100;
}

int main()
{
    // otvaranje datoteke
    FILE* f = fopen("studenti.txt", "r");
    if (!f)
    {
        printf("Datoteku nije moguce otvoriti\n");
        exit(1);
    }

    // brojanje zapisa
    int n = 1;
    while (!feof(f))
    {
        if (fgetc(f) == '\n')
        {
            n++;
        }
    }

    // alociranje prostora
    Student* nizStudenata = (Student*)malloc(n * sizeof(Student));

    // ucitavanje zapisa
    fseek(f, 0, SEEK_SET); // vracamo pokazivac na pocetak datoteke

    for (size_t i = 0; !feof(f); i++)
    {
        fscanf(f, "%s %s %f", nizStudenata[i].ime, nizStudenata[i].prezime, &nizStudenata[i].bodovi);
    }

    // zatvaranje datoteke
    fclose(f);

    // ispis studenata
    for (size_t i = 0; i < n; i++)
    {
        printf("%s %s %.2f %.2f\n", nizStudenata[i].ime, nizStudenata[i].prezime, nizStudenata[i].bodovi, relBodovi(nizStudenata[i].bodovi));
    }

    return 0;
}