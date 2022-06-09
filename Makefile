CFLAGS += -Wall -Wextra -Werror -O3 -std=c11 -pedantic

chop: chop.c

install: chop
	install chop /usr/bin/

clean:
	rm -f chop

.PHONY: install clean
