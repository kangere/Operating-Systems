echo "making image file with zeros"
dd if=/dev/zero of=floppya.img bs=512 count=2880
echo "copying bootload to floppya.img"
dd if=bootload of=floppya.img bs=512 count=1 conv=notrunc
dd if=map of=floppya.img bs=512 count=1 seek=256 conv=notrunc
dd if=config of=floppya.img bs=512 count=1 seek=258 conv=notrunc
echo "Checking contents of floppya.img"
hexdump -C floppya.img
echo "Compiling kernel"
bcc -ansi -c -o kernel.o kernel.c
as86 kernel.asm -o kernel_asm.o
ld86 -o kernel -d kernel.o kernel_asm.o

echo "Compiling Shell.c and linking blackdos.asm to it"
bcc -ansi -c -o shell.o shell.c
#as86 blackdos.asm -o blackdos_asm.o
ld86 -o Shell -d shell.o bdos_asm.o

echo "copying kernel to floppya.img"
dd if=kernel of=floppya.img bs=512 conv=notrunc seek=259

echo "load shell to disk image"
./loadFile Shell

echo "load manual to disk image"
./loadFile Manual

echo "load spc02 for testing delete"
./loadFile spc02

echo "load kitty1"
./loadFile kitty1

echo "load kitty2"
./loadFile kitty2