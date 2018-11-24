CFLAGS=-Wall -Wextra -Os
PREFIX?=/usr/local

shrink-file: shrink-file.o

clean:
	rm shrink-file.o shrink-file

install: shrink-file
	@echo :: installing 'shrink-file' to $(PREFIX)/bin/
	sudo install -m 755 shrink-file $(PREFIX)/bin/shrink-file

.PHONY: clean install
