#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int pdesk[2];
	if (pipe(pdesk) == -1)
	{
		perror("PIPE");
		return 1;
	}

	switch (fork())
	{
	case -1:
		perror("FORK");
		return 2;
	case 0:
		dup2(pdesk[1], STDOUT_FILENO);
		execvp("ls", argv);
		perror("EXECVP ls");
		exit(1);
	default:
	{
		/*
		1. Zamknij deskryptor do zapisu,
		2. Skopiuj deskyptor końca do odczytu tego potoku na deskryptor wejścia standardowego,
		3. Wykonaj  tr "a-z" "A-Z", w przypadku błędu obsłuż go i wyjdź, zwracając 3.
		*/

		close(pdesk[1]); // 1.

		dup2(pdesk[0], STDIN_FILENO); // 2.

		if (execlp("tr", "tr", "[a-z]", "[A-Z]") < 0) // 3.
		{
			perror("EXECVP tr");
			return 3;
		}

		// odczyt i wypisanie z ls
		char buf[2048];
		read(pdesk[0], buf, sizeof(buf));
		printf("%s\n", buf);
	}
	}
	return 0;
}
