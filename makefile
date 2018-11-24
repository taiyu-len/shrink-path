CFLAGS=-Wall -Wextra -Os
PREFIX?=/usr/local

shrink-path: shrink-path.c

clean:
	rm shrink-path.o shrink-path

install: shrink-file
	@echo :: installing 'shrink-path' to $(PREFIX)/bin/
	sudo install -m 755 shrink-path $(PREFIX)/bin/shrink-path

.PHONY: clean install
