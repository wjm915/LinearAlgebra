MEMMGNT_DIR = /home/billy/code.d/c.d/memMgt.d
MEMMGNT_OBJ = $(MEMMGNT_DIR)/memMgt.o


main: 	main.c
	gcc -g main.c $(MEMMGNT_OBJ) -o main


