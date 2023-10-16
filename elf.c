#include <elf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>


int main(int argc, char* argv[]) {
    Elf64_Ehdr header = {
        .e_ident = {
            ELFMAG0,
            ELFMAG1,
            ELFMAG2,
            ELFMAG3,
            ELFCLASS64,
            ELFDATA2LSB,
            EV_CURRENT,
            ELFOSABI_SYSV,
            0, 0, 0, 0, 0, 0, 0, 0
        },
        .e_type = ET_EXEC,
        .e_machine = EM_X86_64,
        .e_entry = 0x40007f,
        .e_phoff = 64,
        .e_shoff = 0,
        .e_flags = 0,
        .e_ehsize = 64,
        .e_phentsize = 56,
        .e_phnum = 1,
        .e_shentsize = 64,
        .e_shnum = 0,
        .e_shstrndx = SHN_UNDEF
    };

    Elf64_Phdr phdr = {
        .p_type = PT_LOAD,
        .p_offset = 0x78, // 64 + 56 = 120
        .p_vaddr = 0x400078,
        .p_paddr = 0x400078,
        .p_filesz = 44,
        .p_memsz = 44,
        .p_flags = PF_X | PF_R,
        .p_align = 0x8
    };

    char objcode[] = {
        0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x21, 0xa, // Hello!\n
        0xb8, // mov rax (32bit)
        1, 0, 0, 0, // write syscall 1
        0xbf, // mov rdi (32 bit)
        1, 0, 0, 0, // stdout
        0x48, 0xbe, // mov rsi, 64 bit pointer
        0x78, 0, 0x40, 0, 0, 0, 0, 0, // Hello strings address in virtual memory
        0xba, // mov rdx (32bit)
        7, 0, 0, 0, // number of bytes in Hello!\n
        0xf, 0x5, // syscall
        0xb8, // mov rax (32 bit)
        0x3c, 0, 0, 0, // 60 = exit syscall
        0x48, 0x31, 0xff, // xor rdi, rdi
        0xf, 0x5 // syscall
    };
    
    FILE* f = fopen("bin", "w");
    if (!f) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    size_t s = fwrite(&header, 1, sizeof(header), f);
    if (s != sizeof(header)) {
        perror("fwrite");
        exit(EXIT_FAILURE);
    }

    s = fwrite(&phdr, 1, sizeof(phdr), f);
    if (s != sizeof(phdr)) {
        perror("fwrite");
        exit(EXIT_FAILURE);
    }

    s = fwrite(objcode, 1, sizeof(objcode), f);

    if (s != sizeof(objcode)) {
        perror("fwrite");
        exit(EXIT_FAILURE);
    }

    fclose(f);

    return EXIT_SUCCESS;

}





































