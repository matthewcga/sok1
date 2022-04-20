#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Not a suitable number of program parameters\n");
        exit(1);
    }

    int toChildFD[2], toParentFD[2];

    pipe(toChildFD);
    pipe(toParentFD);

    int val1, val2, val3 = 0;

    pid_t pid;

    // rodzic ma przekazac dziecku wartosc i ma otrzymac jej kwadrat

    if ((pid = fork()) == 0)
    {
        close(toChildFD[1]);
        read(toChildFD[0], &val2, sizeof(int));

        val2 = val2 * val2;

        close(toParentFD[0]);
        write(toParentFD[1], &val2, sizeof(int));
    }
    else
    {
        val1 = atoi(argv[1]);

        close(toChildFD[0]);
        write(toChildFD[1], &val1, sizeof(int));

        sleep(1);

        close(toParentFD[1]);
        read(toParentFD[0], &val3, sizeof(int));

        printf("%d square is: %d\n", val1, val3);
    }
    return 0;
}
