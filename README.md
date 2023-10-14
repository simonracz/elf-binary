# elf-binary
Code created during recording the [Writing a Linux ELF Binary by Hand](https://youtu.be/JM9jX2aqkog) video.

We write a 164 bytes long x86-64 ELF binary. A proper hello world executable.

# Requirements
Just a C compiler.

# Build
```
gcc -std=c17 -o main ./main.c
gcc -std=c17 -static -o main ./main.c
nasm -felf64 -o hello_asm.o ./hello_asm.asm
ld -o hello_asm ./hello_asm.o
gcc -std=c17 -o elf ./elf.c
./elf
chmod a+x ./bin
./bin
```

# Useful Commands
```
readelf -h ./bin
readelf -l ./bin
hexdump -C ./bin
cat /proc/[pid]/maps
```

# Links
```
man 5 elf
man 2 write
man 2 exit
```
[man 5 elf](https://www.man7.org/linux/man-pages/man5/elf.5.html)


[Intel Manuals](https://www.intel.com/content/www/us/en/developer/articles/technical/intel-sdm.html)
