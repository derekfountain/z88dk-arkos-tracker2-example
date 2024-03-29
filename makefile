# You need rasm.exe in your PATH
#
RASM=rasm.exe

all : arkos.tap

at2_wrapper.o rasmoutput.sym : at2_wrapper.rasm
	$(RASM) at2_wrapper.rasm -ob at2_wrapper.o -sc "defc %s = %d"

rasm_wrapper.o : rasm_wrapper.asm at2_wrapper.o rasmoutput.sym
	zcc +zx -vn -c -compiler sdcc -clib=sdcc_iy -c rasm_wrapper.asm -o rasm_wrapper.o	
	
main.o : main.c
	zcc +zx -vn -c -compiler sdcc -clib=sdcc_iy -c main.c -o main.o --std-c99 --c-code-in-asm --list

# Create the map for the glue step
#
arkos.map : main.o rasm_wrapper.o
	zcc +zx -vn -clib=sdcc_iy -startup=31 -o arkos main.o rasm_wrapper.o --std-c99 -m

# The map file is used to glue together the binary files. appmake uses implied names.
#
arkos__.bin : arkos.map
	z88dk-appmake +glue -b arkos --filler 0xDF

# The glued together file is used to create a TAP
#
arkos.tap : arkos__.bin
	z88dk-appmake +zx -b arkos__.bin --org 32768 --blockname arkos -o arkos.tap

.PHONY: clean
clean :
	rm -f *.o *.tap *.sym *.bin *.map *.lis *~
