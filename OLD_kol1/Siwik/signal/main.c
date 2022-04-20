#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void sighandler(int sig, siginfo_t *info, void *ucontext)
{
    printf("received %d\n", info->si_value.sival_int);
}

int main(int argc, char *argv[])
{

    if (argc != 3)
    {
        printf("Not a suitable number of program parameters\n");
        return 1;
    }

    struct sigaction action;
    action.sa_flags = SA_SIGINFO;
    action.sa_sigaction = sighandler;
    sigaction(SIGUSR1, &action, NULL);
    sigaction(SIGRTMIN + 1, &action, NULL);

    int child = fork();
    if (child == 0)
    {
        // zablokuj wszystkie sygnaly za wyjatkiem SIGUSR1
        // zdefiniuj obsluge SIGUSR1 w taki sposob zeby proces potomny wydrukowal
        // na konsole przekazana przez rodzica wraz z sygnalem SIGUSR1 wartosc

        sigset_t mask;
        sigfillset(&mask);                     // maska na wszystko
        sigdelset(&mask, SIGUSR1);             // exclude
        sigdelset(&mask, SIGRTMIN + 1);        // exclude
        sigprocmask(SIG_SETMASK, &mask, NULL); // naloz maske
    }
    else
    {
        // wyslij do procesu potomnego sygnal przekazany jako argv[2]
        // wraz z wartoscia przekazana jako argv[1]

        union sigval val;
        val.sival_int = atoi(argv[1]);
        sigqueue(child, atoi(argv[2]), val);
    }

    return 0;
}
