#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_COUNT 20
char buffer[MAX_COUNT];

int main(int argc, char* argv[]) {
	int fd = open(argv[1], O_RDONLY, MAX_COUNT);

	if (fd == -1) {
		perror("Unable to open file");
		exit(EXIT_FAILURE);
	}

	ssize_t br;
	ssize_t bw;

	while((br = read(fd, buffer, MAX_COUNT)) > 0) {
		bw = write(STDOUT_FILENO, buffer, br);
		if (bw != br) {
			perror("Unable to write");
			close(fd);
			exit(EXIT_FAILURE);
		}
	}
	if (br == -1) {
		perror("Unable to read file");
		close(fd);
		exit(EXIT_FAILURE);
	}

	close(fd);
	exit(EXIT_SUCCESS);
}
