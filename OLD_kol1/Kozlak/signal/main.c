#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Prawidłowe wywołanie %s liczba\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    pid_t child;
    int status;

    if ((child = fork()) < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (child == 0)
    {
        sleep(2);
        exit(EXIT_SUCCESS);
    }
    else
    {
        /*
        1. Proces macierzysty usypia na liczbę sekund będącą argumentem programu

        2. Proces macierzysty pobiera status  zakończenia potomka child, nie zawieszając swojej pracy.

        3. Jeśli proces się nie zakończył, wysyła do dziecka sygnał zakończenia.

        4. Jeśli wysłanie sygnału się nie powiodło, proces zwróci błąd.

        5. Jeśli się powiodło, wypisuje komunikat sukcesu zakończenia procesu potomka
        z numerem jego PID i sposobem zakończenia (Proces xx zakończony przez exit albo sygnałem).
        */

        sleep(atoi(argv[1])); // 1.

        int childPid = waitpid(child, &status, WNOHANG); // 2.

        if (childPid != child) // 3.
        {
            if (kill(child, SIGKILL) == 0) // 3, 5.
            {
                waitpid(child, &status, NULL);
                printf("sucessfully killed a child\npid: %d\tstatus: %d\n", child, status);
            }
            else // 4.
            {
                perror("killing a child was unsucessfull");
            }
        }
        else
        {
            // nie sprecyzowano w zadaniu
        }
    }
    return 0;
}
