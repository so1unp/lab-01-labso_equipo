#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#define PERMS 0666 /*lectura y escritura para propietario, grupo y otros*/
#define SIZE 8     // 7 bytes previos + 1 byte del mensaje
/** retorna un char con valor de 0 a 255*/
unsigned char aleatorio()
{
    return (unsigned char)(rand() % 256);
}
void encriptado(int fd, char mensaje)
{
    char buffer[SIZE];
    for (int i = 0; i < SIZE-1; i++)
    {
        buffer[i] = (char)aleatorio();
    }
    buffer[7] = mensaje;
    write(fd, buffer, SIZE);
}

int main(int argc, char *argv[])
{
    srand(1); // revisar
    int fd = STDOUT_FILENO; // 1  
    char *mensaje = argv[argc - 1];
    if (argc > 2)
    {
        fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, PERMS);
        if (fd == -1) // ocurrio algo
        {
            exit(EXIT_FAILURE);
        }
    }
    if (argc == 1)
    {
        exit(EXIT_FAILURE);
    }
    while (*mensaje)
    {
        encriptado(fd, *mensaje);
        mensaje++;
    }
    // si fd no mantiene el valor de salida estandar
    if (fd != STDOUT_FILENO) 
    {
        close(fd);
    }
    exit(EXIT_SUCCESS);
}
