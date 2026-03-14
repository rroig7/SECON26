CC      = gcc
CFLAGS  = -Wall -Wextra -O2
LDFLAGS = -llgpio -lm

SRCS = start-off-strip.c      \
       start-off-strip.h      \
       main.c

ldr-start: $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f ldr-start ldr_calibration
