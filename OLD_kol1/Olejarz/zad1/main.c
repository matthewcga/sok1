#include <errno.h>
#include <dirent.h>
#include <stdio.h>

#include <string.h> // strcmp()

int main(int argc, char *argv[])
{
    DIR *katalog;
    if (argc != 2)
    {
        printf("Wywołanie %s ścieżka", argv[0]);
        return 1;
    }
    struct dirent *pozycja;

    /*
    Otwórz katalog
    w przypadku błędu otwarcia zwróć błąd funkcji otwierającej i zwrócć 1.
    Wyświetl zawartość katalogu katalog, pomijając "." i ".."
    Jeśli podczas tej operacji wartość errno zostanie ustawiona zwróć błąd funkcji czytającej oraz wartość 2.
    */

    katalog = opendir(argv[1]);
    errno = 0;

    if (katalog == NULL)
    {
        perror("opendir() error");
        return 1;
    }
    else
    {
        while ((pozycja = readdir(katalog)) != NULL)
        {
            if (errno != 0)
            {
                perror("error reading directory");
                return 2;
            }
            else if (!strcmp(pozycja->d_name, ".") || !strcmp(pozycja->d_name, ".."))
                continue;
            else
                printf("%s\n", pozycja->d_name);
        }
    }

    closedir(katalog);
    return 0;
}
