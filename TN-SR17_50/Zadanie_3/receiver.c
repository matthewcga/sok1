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

    char *val_str;

    FILE *fifo = fopen(PIPE, "r");
    if (fifo == NULL)
        exit(EXIT_FAILURE);

    char buf[128];
    while (fgets(buf, _SC_LINE_MAX, fifo) != NULL)
    {   
        val = atoi(buf);
    }

    printf("%d square is: %d\n", val, val * val);
    return 0;
}
