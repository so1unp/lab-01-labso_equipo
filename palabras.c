#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <stdbool.h>

void handler()
{
    exit(0);
}

int main(int argc, char *argv[])
{
    char c;
    signal(SIGINT, handler);

    // Bandera que indica si el caracter que se imprimió anteriormente fue una nueva linea
    bool new_line_printed = false;

    while ((c = getchar()) != EOF)
    {
        // '\t' para verificar si es TAB
        if ((c == ' ' || c == '\t' ||c == '\n'))
        {
            // Imprimir una linea nueva sólo si la anterior no fue una nueva linea
            if (!new_line_printed)
            {
                putchar('\n');
                // Se acaba de imprimir una nueva linea
                new_line_printed = true;
            }
        }
        else
        {
            putchar(c);
            // Se acaba de imprimir un caracter
            new_line_printed = false;
        }
        if (c == '\n')
        {
            continue;
        }
    }

    exit(EXIT_SUCCESS);
}
