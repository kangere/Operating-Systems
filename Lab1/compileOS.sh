#echo "making image file with zeros"
#dd if=/dev/zero of=floppya.img bs=512 count=2880
#echo "copying bootload to floppya.img"
#dd if=bootload of=floppya.img bs=512 count=1 conv=notrunc
#echo"Checking contents of floppya.img"
#hexdump -C floppya.img
echo "Compiling kernel"
bcc -ansi -c -o kernel.o kernel.c
as86 kernel.asm -o kernel_asm.o
ld86 -o kernel -d kernel.o kernel_asm.o
echo "copying kernel to floppya.img"
dd if=kernel of=floppya.img bs=512 conv=notrunc seek=259