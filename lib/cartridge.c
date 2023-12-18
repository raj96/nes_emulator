#include <cartridge.h>
#include <log.h>

#include <stdio.h>
#include <sys/stat.h>
#include <string.h>

#define NES_HEADER_MAGIC (0x4e | (0x45 << 8) | (0x53 << 16) | (0x1a << 24))

typedef union {
    uint8_t bytes[8];
    struct {
        uint32_t header;
        uint8_t prg_rom_blk_size;
        uint8_t chr_rom_blk_size;
        union {
            uint8_t byte;
            struct {
                uint8_t mirroring:1;
                uint8_t persistent_memory:1;
                uint8_t trainer:1;
                uint8_t ignore_mirroring:1;
                uint8_t mapper_ln:4;
            };
        } flag6;

        union {
            uint8_t byte;
            struct {
                uint8_t ignore:4;
                uint8_t mapper_hn:4;
            };
        } flag7;
    } fields;
} _nes_header;

_cartridge load_cartridge(char *nes_file_loc) {
    FILE *nes_file = fopen(nes_file_loc, "rb");
    if(nes_file == NULL) {
        LOGF("Could not load NES file");
    }

    struct stat info;
    stat(nes_file_loc, &info);

    char *nes_content = (char *)malloc(sizeof(char) * info.st_size);

    fread(nes_content, info.st_size, 1, nes_file);

    fclose(nes_file);

    _nes_header *header = (_nes_header *)(nes_content);
    _cartridge cartridge;

    if(header->fields.header != NES_HEADER_MAGIC) {
        LOGF("%s is not a valid nes file", nes_file_loc);
    }

    cartridge.prg_rom_size = header->fields.prg_rom_blk_size * 16384;
    cartridge.chr_rom_size = header->fields.chr_rom_blk_size * 8192;

    cartridge.prg_rom = (uint8_t *)malloc(sizeof(uint8_t) * cartridge.prg_rom_size);
    cartridge.chr_rom = (uint8_t *)malloc(sizeof(uint8_t) * cartridge.chr_rom_size);

    int prg_rom_offset = 16;
    int chr_rom_offset = prg_rom_offset + cartridge.prg_rom_size;

    if(header->fields.flag6.trainer) {
        prg_rom_offset += 512;
        chr_rom_offset += 512;
    }

    cartridge.mapper = (header->fields.flag7.mapper_hn << 4) | header->fields.flag6.mapper_ln;
    
    cartridge.mirror_mode = header->fields.flag6.mirroring == 0 ? MirroringHorizontal : MirroringVertical;
    cartridge.mirror_mode = header->fields.flag6.ignore_mirroring == 1 ? MirroringFourScreenVram : cartridge.mirror_mode;

    memcpy(cartridge.prg_rom, nes_content + prg_rom_offset, cartridge.prg_rom_size);
    if(cartridge.chr_rom_size > 0)
        memcpy(cartridge.chr_rom, nes_content + chr_rom_offset, cartridge.chr_rom_size);

    free(nes_content);

    return cartridge;
}

void destroy_cartridge(_cartridge cartridge) {
    free(cartridge.prg_rom);
    if(cartridge.chr_rom != NULL)
        free(cartridge.chr_rom);
}

