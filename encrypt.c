#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
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
    for (int i = 0; i < SIZE - 1; i++)
    {
        buffer[i] = (char)aleatorio();
    }
    buffer[7] = mensaje;
    write(fd, buffer, sizeof(buffer));
    // no hace falta print porque puede escribir
    //  sobre el archivo salida estandar
}

int main(int argc, char *argv[])
{
    srand(1);
    int fd = STDOUT_FILENO; // fd <- 1
    if (argc > 3)
    {
        exit(EXIT_FAILURE);
    }
    if (argc == 1) // casos echo -n "hola" | bin/encript
    {
        char buffer[1024];                                                    // un kb
        ssize_t bytes_read;                                                   // los bytes leidos
        while ((bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0) // lee bloques de hasta 1024 bytes
        {                                                                     // si > 0 es porque queda algo por leer
            for (int i = 0; i < bytes_read; i++)                              // recorre los bytes leidos
            {
                if (buffer[i] != '\n')         // en el ejemplo del readme hay echo -n "hola"
                {                              // aunque queda igual que echo "hola"
                    encriptado(fd, buffer[i]); // encriptado normal
                }
            }
        }
        exit(EXIT_SUCCESS); // nada mas que hacer salir
    }
    char *mensaje = argv[argc - 1]; // porque? el mensaje es el ultimo
    if (argc == 3)
    {
        fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, PERMS);
        if (fd == -1) // ocurrio algo
        {
            exit(EXIT_FAILURE);
        }
    }
    while (*mensaje) // procesa el mensaje
    {
        encriptado(fd, *mensaje);
        mensaje++;
    }
    if (fd != STDOUT_FILENO) // cierra si no es por salida estandar
    {
        close(fd);
    }
    exit(EXIT_SUCCESS);
}
