TARGETS = crc8_sample crc16_sample crc32_sample
#CFLAGS = -Wall -Werror -std=c99
CFLAGS = -Wall -std=c99

.PHONY : all clean 

all : $(TARGETS)

crc8_sample : crc8_sample.o misc_functions.o crc8.o
	$(CC) $(CFLAGS) -o $@ $^

crc16_sample : crc16_sample.o misc_functions.o crc16.o
	$(CC) $(CFLAGS) -o $@ $^

crc32_sample : crc32_sample.o misc_functions.o
	$(CC) $(CFLAGS) -o $@ $^

%.o : %.c Makefile
	$(CC) -c $(CFLAGS) -o $@ $<

clean :
	rm -f $(TARGETS) *.o
