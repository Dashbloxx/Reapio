CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -ldiscord -lcurl

SRCDIR = source
SRCS = $(wildcard $(SRCDIR)/*.c)

reapio: $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f reapio