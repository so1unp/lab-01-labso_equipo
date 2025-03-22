#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#define PERMS 0666 /*lectura y escritura para propietario, grupo y otros*/

unsigned char aleatorio()
{
    return (unsigned char)(rand() % 256); // retorna valor 0-255
}

int main(int argc, char *argv[])
{
    srand(1); // revisar
    int fd = STDOUT_FILENO;  // Por defecto, salida estándar
    const char *output_file = NULL;

    if (argc > 2)
    {
        output_file = argv[1];
        fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, PERMS);
        if (fd == -1)
        {
            perror("Error al abrir el archivo");
            exit(EXIT_FAILURE);
        }
    }

    // FILE *output = (fd == -1) ? stdout : fdopen(fd, "w");
    // if (output == NULL)
    // {
    //     perror("Error al abrir el archivo");
    //     if (fd != -1)
    //     close(fd);
    //     exit(EXIT_FAILURE);
    // }
    
    char *mensaje = argv[argc - 1];
    char buffer[8];
    while (*mensaje)
    {
        for (int i = 0; i < 7; i++)
        {
            buffer[i] = (char) aleatorio();
            // fputc(aleatorio(), output); // Escribir el carácter aleatorio
        }
        // Imprimir el carácter original
        buffer[7] = *mensaje;
        // fputc(*mensaje, output);
        write(fd, buffer,  8);
        mensaje++;
    }

    // si fd mantiene el valor de salida estandar
    if (fd != STDOUT_FILENO) { 
        close(fd);
    }

    exit(EXIT_SUCCESS);
}
