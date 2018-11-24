#include <unistd.h>
int main(int argc, char **argv) {

	if (argc != 2) {
		return 1;
	}

	char *path = argv[1];
	char *src = path;

	// skip to first '/'
	while (*src && *src != '/') {
		++src;
	}

	int len, dot;
	char *tgt = src, *rec = src;
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
	do {
		int written = write(STDOUT_FILENO, path, tgt-path);
		if (written == -1) return 1;
		path += written;
	} while (tgt - path);
	return 0;
}
