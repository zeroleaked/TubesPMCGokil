#include<stdio.h>
#include<stdlib.h>

void AddTimeFromFile(
    char *filepath,
    double time_start,
    double time_end)
{
    FILE *fptr;
    fptr = fopen(filepath, "r");

    if(fptr == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    while(fscanf(fptr, "%lf %lf", &time_start, &time_end)!=2);
    {
        printf("%lf \n", time_start);
        printf("%lf \n", time_end);
    }
}

int main()
{
    char *file = "timefile.txt";
    double start;
    double end;

    AddTimeFromFile(file, start, end);
}
