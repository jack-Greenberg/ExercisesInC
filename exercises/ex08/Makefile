CC=gcc
CFLAGS=$$(pkg-config --cflags --libs gio-2.0 glib-2.0)
TARGET=ex_compile
DEPS=ex_compile.c
SRC=ex_compile.c

all: $(DEPS)
	$(CC) -o $(TARGET) $(SRC) $(CFLAGS)

.PHONY: clean
clean:
	rm $(TARGET)

word_count: word_count.c
	$(CC) -o word_count word_count.c $(CFLAGS)
