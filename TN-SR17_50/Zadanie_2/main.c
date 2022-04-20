#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/*
 * Funkcja 'read_end' powinna:
 *  - otworzyc plik o nazwie przekazanej w argumencie
 *    'file_name' w trybie tylko do odczytu,
 *  - przeczytac ostatnie 8 bajtow tego pliku i zapisac
 *    wynik w argumencie 'result'.
 */

void read_end(char *file_name, char *result)
{
    int fd = open(file_name, O_RDONLY);
    lseek(fd, 8, SEEK_END);
    read(fd, result, sizeof(char) * 8);
    return result;
}

int main(int argc, char *argv[])
{
    int result[2];

    if (argc < 2)
        return -1;
    read_end(argv[1], (char *)result);
    printf("magic number: %d\n", (result[0] ^ result[1]) % 1000);
    return 0;
}
