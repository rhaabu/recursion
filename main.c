#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void sisestus(double *X, double *E);
double *push(double * A, int *L, double value);
double *arvutaja(double *A, double *X, double *E, int samm, int *L);
int factorial(int f);
int checkFile(FILE *fp, char *filename);
void valjastus(double *A, int L);

int main()
{
    int L = 0;
    double X, E;
    double *A = NULL;
    sisestus(&X, &E);
    A = (double *)push(A, &L, 1.0);
    A = (double *)arvutaja(A, &X, &E, 3, &L);
    valjastus(A, L);
    free(A);
    return 0;
}

void sisestus(double *X, double *E)// X ja E sisestus vastavalt tingimustele.
{
    printf("Sisestage reaalarv X (|X| < 1)\n");
    scanf("%lf", X);
    while(*X <= -1 || *X >= 1)
    {
        printf("Sisestage reaalarv X (|X| < 1)\n");
        scanf("%lf", X);
    }

    printf("Sisestage reaalarv E (0 < E < 1)\n");
    scanf("%lf", E);
    while(*E <= 0 || *E >= 1)
    {
        printf("Sisestage reaalarv E (0 < E < 1)\n");
        scanf("%lf", E);
    }
}

double *push(double * A, int *L, double value)// Lisab massiivi A dünaamiliselt mälu eraldades.
{
    double *temp = (double*)realloc(A, sizeof(double) * (*L+1));
    if(temp == NULL)
    {
        printf("Ei onnestunud malu eraldada\n");
        return;
    }
    A = temp;
    *(A+(*L)) = value;
    *L = *L + 1;
    return A;
}

double *arvutaja(double *A, double *X, double *E, int samm, int *L)// arvutab järgmise liikme väärtuse ja seejärel lisab selle massiivi A kasutades push funktsiooni.
{
    double value;
    if(*L % 2 == 0)
    {
        value = pow(*X, samm)/factorial(samm);
    } else
    {
        value = pow(-(*X), samm)/factorial(samm);
    }
    if(!(fabs(value - A[*L-1]) <= *E || *L == 15))
    {
        A = (double*)push(A, L, value);
        samm += 2;
        A = (double*)arvutaja(A, X, E, samm, L);
    }
    return A;
}

int factorial(int f) // arvutab faktoriaali
{
    if ( f == 0 )
        return 1;
    return(f * factorial(f - 1));
}

int checkFile(FILE *fp, char *filename) // Faili kontrolli funktsioon
{
   fp = fopen (filename, "r");

    if (fp != NULL)
    {
        fclose (fp);
    }
   return (fp != NULL);
}

void valjastus(double *A, int L) // väljastab massiivi A faili F.txt.
{
    int fileExist, i;
    char *outputName = "F.txt";
    FILE *output = fopen(outputName, "w");

    fileExist = checkFile(output, outputName);

    if(fileExist == 1)
    {
        fprintf(output, "Massiivi elementide arv: %d\n", L);
        for(i=0;i<L;i++)
        {
            fprintf(output, "A[%d] = %f\n", i, A[i]);
        }
    }

    fclose(output);
}
