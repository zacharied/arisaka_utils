CC = gcc
CFLAGS = -Wall -g

# For programs to be called by Arisaka scripts.
OUT_ARI = out_ari

# For programs to be run by the user.
OUT_BIN = out_bin

TARGET_ARI_BIN ?= ${ARISAKA_BIN}/arisaka
TARGET_BIN ?= ~/bin

define shell_note
	sed -i '2i # This script is generated from ari_utils. Do not edit it.' $(1)
endef

all: arilog ariview

install:
	cp $(wildcard $(OUT_ARI)/*) $(TARGET_ARI_BIN)
	cp $(wildcard $(OUT_BIN)/*) $(TARGET_BIN)

arilog:
	$(CC) $(CFLAGS) -o $(OUT_ARI)/arilog arilog.c

ariview:
	cp ariview.sh $(OUT_BIN)/ariview
	@$(call shell_note,$(OUT_BIN)/ariview)
	chmod +x $(OUT_BIN)/ariview

.PHONY: all install
