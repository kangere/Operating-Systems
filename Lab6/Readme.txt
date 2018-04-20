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

lab 02:
	-created function readString that reads string from IO input
	-Created function readInt (converts string to int and outputs it) and writeInt (converts int to 		string and prints it)
	-Created mod and div functions the perform modulus and division function respectively
	-Implemented madLibs code to main function

lab 03:
	-Created function readsector that reads sector from floppy disk
	-Created function writeSector that writes data to a sector in the floppy disk
	-Created function clearScreen that clears the screen and sets the foreground and bckground colour of the screen.
	-Added this functions to the handleInterrupt21 function and added the appropriate cases for them
	-Tested the code and made sure it was compiling and working as expected

lab 04:
	-Created Function readFile() that reads file from floppya.img
	-Created function writeFile() that writes file to floppya.img
	-Created function deleteFile() that deletes file from directory
	-Run tests in main to ensure functions work as supposed to

lab 05:
	-Created readFile function
	-Created stop function
	-tested functions

lab 06:
	-Created shell.c
	-Added commands to shell.c to allow for a basic shell program
	
