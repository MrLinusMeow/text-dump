#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define null '\0'

int main(int argc, char **argv) {
	for(int i = 1; argv[i] != '\0'; ++i) {
		char *errMsg = "\033[1;31m[ERROR] \033[0;1m";
		int fd = open(argv[i], O_RDWR, 0000);
		if (fd == -1) {
			fprintf(stderr, "%s%s:\033[0m ", errMsg, argv[i]);
			perror(null);
			continue;
		}
		char buf[BUFSIZ+1];
		ssize_t n = 0;
		while ((n = read(fd, buf, BUFSIZ)) > 0) {
			buf[n] = null;
			if ((write(STDOUT_FILENO, buf, n)) == -1) {
				fprintf(stderr, "%s%s:\033[0m ", errMsg, argv[i]);
				perror(null);
				break;
			}        
		}
		if (n == -1) {
			fprintf(stderr, "%s%s:\033[0m ", errMsg, argv[i]);
			perror(null);
			continue;
		}
		if (close(fd) == -1) {
			fprintf(stderr, "%s%s:\033[0m ", errMsg, argv[i]);
			perror(null);
			continue;
		}
	}
	exit(0);
}
