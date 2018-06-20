CFLAGS  = -Wall -g
OUT_DIR = out

arilog:
	gcc	$(CFLAGS) -o $(OUT_DIR)/arilog arilog.c

all:arilog

.PHONY: all
