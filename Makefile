CC = cc

CFLAGS  = -g -Wall  -I/usr/local/include 

TARGET = udp-server udp-client 

all: $(TARGET)
	
udp-server: udp-server.c
	$(CC) $(CFLAGS) -o udp-server udp-server.c 

udp-client: udp-client.c
	$(CC) $(CFLAGS) -o udp-client udp-client.c 

clean:
	$(RM) $(TARGET)