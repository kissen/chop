#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

static char *argv0;

/**
 * Chop stdin to stdout.
 *
 * @param width Columns to keep. If set to zero, all input is forward (like
 * cat.)
 */
static void chop(unsigned short width) {
	int c;
	unsigned long col = 0;

	while ((c = getchar()) != EOF) {
		if (col < width || c == '\n' || width == 0) {
			putchar(c);
			col += 1;
		}

		if (c == '\n') {
			col = 0;
		}
	}

	if (ferror(stdin)) {
		const int error = errno;
		fprintf(stderr, "%s: getchar: %s\n", argv0, strerror(error));
		exit(1);
	}
}

static unsigned short get_terminal_width(void) {
	struct winsize w;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
		if (errno == ENOTTY) {
			fprintf(stderr, "%s: warning: not a tty, not chopping\n", argv0);
			return 0;
		}

		perror("ioctl");
		exit(1);
	}

	return w.ws_col;
}

int main(int argc, char **argv) {
	(void)argc;
	argv0 = *argv;

	const unsigned short width = get_terminal_width();
	chop(width);
}
