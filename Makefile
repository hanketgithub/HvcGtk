CC=gcc
PROG=HvcGtk


all: 
	echo "Create link!"
	$(CC) -o $(PROG) $(PROG).c handler.c apiVENC.c `pkg-config --libs gtk+-3.0` \
    `pkg-config --cflags gtk+-3.0` \
    -lvega330x_venc

clean:
	$(RM) $(PROG)
