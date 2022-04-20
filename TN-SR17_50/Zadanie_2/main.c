#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>


/*
 * Funkcja 'read_end' powinna:
 *  - otworzyc plik o nazwie przekazanej w argumencie
 *    'file_name' w trybie tylko do odczytu,
 *  - przeczytac ostatnie 8 bajtow tego pliku i zapisac
 *    wynik w argumencie 'result'.
 */
void read_end(char *file_name, char *result){
    int File = open(file_name, O_RDONLY);
    if (lseek(File, -8, SEEK_END) == -1) {
        exit(1);
    }
    read(File, result, 8);
    close(File);
}


int main(int argc, char *argv[]) {
    int result[2];

    if (argc < 2) return -1;
    read_end(argv[1], (char *) result);
    printf("magic number: %d\n", (result[0] ^ result[1]) % 1000);
    return 0;
}
