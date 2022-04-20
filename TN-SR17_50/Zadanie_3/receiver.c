#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define PIPE "./squareFIFO"

int main()
{
    int val = 0;
    /***********************************
     * odczytaj z potoku nazwanego PIPE zapisana tam wartosc i przypisz ja do zmiennej val
     * posprzataj
     ************************************/

    FILE *fifo = fopen(PIPE, "r");
    if (fifo == NULL)
        exit(EXIT_FAILURE);

    char buf[128];
    while (fgets(buf, _SC_LINE_MAX, fifo) != NULL)
    {   
        val = atoi(buf);
        // printf("val: %d", val);
    }
    fflush(fifo);
    fclose(fifo);

    printf("%d square is: %d\n", val, val * val);
    // remove(PIPE);
    return 0;
}
