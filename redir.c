#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
  bool hasInput = false;
  bool hasOutput = false;
  bool is1stCMD= true;
  bool isLastCMD = true;

  if (strcmp(argv[1], "-") != 0)
  {
    hasInput = true;
  }

  if (strcmp(argv[3], "-") != 0)
  {
    hasOutput = true;
  }

  pid_t pid = fork();
  if (pid == 0) {
		if (hasInput && is1stCMD) {
			int fdin = open(argv[1], O_RDONLY, 0644);
			dup2(fdin, STDIN_FILENO);
			close(fdin);
		}

		if (hasOutput && isLastCMD) {
			int fdout = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			dup2(fdout, STDOUT_FILENO);
			close(fdout);
		}
	}

	return 0;
}
