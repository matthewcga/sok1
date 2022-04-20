#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define PIPE "./squareFIFO"

int main(int argc, char *argv[])
{

  if (argc != 2)
  {
    printf("Not a suitable number of program parameters\n");
    return (1);
  }

  // utworz potok nazwany pod sciezka reprezentowana przez PIPE
  // zakladajac ze parametrem wywolania programu jest liczba calkowita
  // zapisz te wartosc jako int do potoku i posprzataj

  char* num = argv[1];

  FILE *pipe_ptr = fopen(PIPE, "w");
  if (pipe_ptr == NULL)
    exit(EXIT_FAILURE);

  fwrite(num, strlen(num), sizeof(char), pipe_ptr);
  fflush(pipe_ptr);

  return 0;
}
