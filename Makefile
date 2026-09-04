.PHONY: build run

setup:
	meson setup build

build:
	meson compile -C build

run: build
	./build/lirium

all: setup build run
