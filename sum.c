#include <stdio.h>
#include <stdlib.h>

int suma_total = 0;

void suma_elemento(int elemento)
{
    suma_total += elemento;
}

void sumar(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++)
    {
        suma_elemento(atoi(argv[i]));
    }
}

void imprimir()
{
    printf("%d\n", suma_total);
}

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        sumar(argc, argv);
    }
    else
    {
        int numero;
        while (scanf("%d", &numero) == 1)
        {
            suma_elemento(numero);
        }
    }
    imprimir();
    exit(EXIT_SUCCESS);
}
