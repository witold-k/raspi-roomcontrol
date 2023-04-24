MAKEFLAGS += --no-print-directory

clean:

build:
	make -C ../../bitbake raspi-roomcontrol


.PHONY:  build clean
.SILENT: build clean
.DEFAULT_GOAL := build
