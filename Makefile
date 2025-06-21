CC := gcc
CFLAGS := -Wall -fPIC -O2
LDFLAGS := -shared
TARGET := nodelay.so
SRC := nodelay.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(TARGET)

