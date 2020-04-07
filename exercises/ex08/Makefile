CC=gcc
CFLAGS=$$(pkg-config --cflags --libs glib-2.0)
TARGET=ex_compile
DEPS=ex_compile.c
SRC=ex_compile.c

all: $(DEPS)
	$(CC) -o $(TARGET) $(SRC) $(CFLAGS)

.PHONY: clean
clean:
	rm $(TARGET)

