#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

int main()
{
    pid_t child;
    int status, retval;
    if ((child = fork()) < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (child == 0)
    {
        sleep(5);
        exit(EXIT_SUCCESS);
    }
    else
    {
        /*
        1. Proces macierzysty pobiera status zakończenie potomka child, nie zawieszając swojej pracy.

        2. Jeśli proces się nie zakończył, wysyła do dziecka sygnał SIGKILL.

        3. Jeśli wysłanie sygnału się powiodło,
        wypisuje komunikat sukcesu zakończenia procesu potomka z numerem jego PID i statusem zakończenia.

        4. Jeśli wysłanie sygnału się nie powiodło, ponownie oczekuje na zakończenie procesu child,
        tym razem zawieszając pracę do czasu zakończenia sygnału
        */

        retval = waitpid(child, &status, WNOHANG); // 1.

        if (retval != child) // 2.
        {

            if (kill(child, SIGKILL) == 0) // 3.
            {
                status = waitpid(child, &status, NULL);
                printf("sucessfully killed a child\npid: %d\tstatus: %d\n", child, status);
            }
            else // 4.
            {
                printf("killing a child was unsucessfull\nawaiting...\n");
                status = waitpid(child, &status, NULL);
                printf("child process ended\npid: %d\tstatus: %d\n", child, status);
            }
        }
        else
        {
            // brak w poleceniu
        }
    }
    exit(EXIT_SUCCESS);
}
