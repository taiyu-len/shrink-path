#include <unistd.h> // read, write, _exit
#include <limits.h> // NAME_MAX
#include <errno.h>  // errno
#include <string.h> // strchr

static char *shrink_path(char *path);
static char *read_str(void);
static void write_str(char *begin, char *end);
static void write_errno(int value);

int main(int argc, char **argv) {
	char *path;
	char *last;
	if (argc == 1) {
		path = read_str();
	} else {
		path = argv[1];
	}
	last = shrink_path(path);
	write_str(path, last);
	return 0;
}

char *shrink_path(char * const path) {
	char *src = path;
	char *tgt;
	char *rec;
	int len, dot;
	// skip to first '/'
	while (*src && *src != '/') {
		++src;
	}

	tgt = rec = src;
	len = dot = 0;
	while (*src) {
		// either reset length at start of new subdir,
		// or increase length for each letter in subdir.
		if (*src == '/') {
			len = dot = 0;
		} else {
			++len;
		}
		// if the first character is a '.', set dot variable.
		if (len == 1 && *src == '.') {
			dot = 1;
		}
		// write src onto tgt if len < 1 + dot
		// save next src into rec, for writing rest of folder name
		// if its the last subdir
		if (len <= 1 + dot) {
			*tgt = *src;
			++tgt;
			rec = src + 1;
		}
		++src;
	}

	// move rest of last directory onto target.
	//    tgt v     v rec
	// ~/f/b/s????/subdir
	while (*rec) {
		*tgt = *rec;
		++tgt;
		++rec;
	}

	// write final byte
	*tgt = '\0';

	// returns end of new string
	return tgt;
}

char *read_str(void) {
	static char buffer[NAME_MAX + 1];
	char *last;
	int bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer));
	if (bytes_read == -1) {
		write_errno(errno);
		_exit(1);
	}
	buffer[bytes_read] = '\0';
	last = strchr(buffer, '\n');
	if (last) {
		*last = '\0';
	}
	return buffer;
}

void write_str(char *first, char *last) {
	while (first != last) {
		int written = write(STDOUT_FILENO, first, last-first);
		if (written == -1) {
			write_errno(errno);
			_exit(1);
		}
		first += written;
	};
}

void write_errno(int value) {
	char *err = strerror(value);
	char *end = err + strlen(err);
	write(STDERR_FILENO, err, end-err);
}
