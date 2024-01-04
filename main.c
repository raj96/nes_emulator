#include <stdio.h>
#include "emulator.h"
#include "log.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        LOGF("Usage: %s <nes file>", argv[0]);
    }

    char *nes_file_name = argv[1];
    emulator_run(nes_file_name);
    return 0;
}