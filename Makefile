CC=gcc
PROG=HvcGtk


all: 
	@if [ ! -h m31_hvc_api ]; \
	then \
		echo "Create link!"; \
		ln -s `find $(HOME) -iname m31_hvc_api`; \
	fi; 
	$(CC) -o $(PROG) $(PROG).c `pkg-config --libs gtk+-3.0` \
    `pkg-config --cflags gtk+-3.0` \
    -lm31_hvc_api

clean:
	$(RM) $(PROG)
