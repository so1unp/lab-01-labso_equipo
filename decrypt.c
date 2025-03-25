#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#define BUFFER_SIZE 1024 // bloque de lectura

void desencriptar(int fd)
{
    unsigned char buffer[8]; // Buffer para 8 bytes
    ssize_t bytes_leidos;
    while ((bytes_leidos = read(fd, buffer, sizeof(buffer))) > 0)
    {
        if (bytes_leidos != 8)
        {
            printf("Error");
            exit(EXIT_FAILURE);
        }
        write(STDOUT_FILENO, &buffer[sizeof(buffer) - 1], 1);
    }
}

int main(int argc, char *argv[])
{
    // fd = file descriptor
    // si no hay argumentos entrada estandar sino abre archivo
    int fd = (argc == 1) ? STDIN_FILENO : open(argv[1], O_RDONLY);
    if (fd < 0) // ocurrido a1lgun incoveniente
    {
        perror("Error");
        return 1;
    }
    desencriptar(fd);
    if (fd != STDIN_FILENO) // la descripcion de archivo no es una salida estandar
        close(fd);          // cerrar archivo
    exit(EXIT_SUCCESS);
}