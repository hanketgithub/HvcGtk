CC=gcc
PROG=HvcGtk


all: 
	echo "Create link!"
	$(CC) -o $(PROG) $(PROG).c `pkg-config --libs gtk+-3.0` \
    `pkg-config --cflags gtk+-3.0` \
    -lm31_hvc_api

clean:
	$(RM) $(PROG)
