#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void handler()
{
    exit(0);
}

int main(int argc, char *argv[])
{
    char c;
    signal(SIGINT, handler);
    while (1)
    {
        while ((c = getchar()) != EOF)
        {
            if (c == ' ' || c == '\n')
            {
                putchar('\n');
            }
            else
            {
                putchar(c);
            }
            if (c == '\n')
            {
                break;
            }
        }
    }
    exit(EXIT_SUCCESS);
}
