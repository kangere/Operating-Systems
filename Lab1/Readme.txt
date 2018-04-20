BlackDos OS

Author: Paul Murage

Class: Operating System

lab 01:
	-Assembled bootlader code in order to output machine readable code
	-Made an image file that is filled with zeros named floppya.img
	-Copied bootload output to the Floppya.img file
	-Created a script file called CompileOs.sh that holds repetitively used commands
	-Downloaded kernel.c and kernel.asm files
	-Wrote code in kernel.c file to enable printString() function to print to string
	-Compiled and tested the kernel.c code t ensure it was working
	-Added functionality to printString() to enable it to also print to the printer
	-uncommented code in handleInterrupt21() function to put display functionaly in this function
	-Compiled and tested code to ensure it works
	-Added more repetitively used commands in compileOs.sh
	