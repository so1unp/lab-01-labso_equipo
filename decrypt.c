#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

void desencriptar(int fd)
{
    char buffer[127];
    ssize_t bytes_leidos;
    while ((bytes_leidos = read(fd, buffer, sizeof(buffer))) > 0)
    {
        write(STDOUT_FILENO, buffer, (size_t)bytes_leidos);
    }
}

int main(int argc, char *argv[])
{
    // fd = file descriptor
    // si no hay argumentos entrada estandar sino abre archivo
    int fd = (argc == 1) ? STDIN_FILENO : open(argv[1], O_RDONLY);
    if (fd < 0) // ocurrido algun incoveniente
    {
        perror("Error");
        return 1;
    }
    desencriptar(fd);
    if (fd != STDIN_FILENO) // la descripcion de archivo no es una salida estandar
        close(fd); // cerrar archivo
    exit(EXIT_SUCCESS);
}