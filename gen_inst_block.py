#!/bin/python3

base_inst = """const instruction MNEMONIC_ADDR_MODE = {
    .mnemonic = "MNEMONIC",
    .opcode = OPCODE,
    .total_bytes = TOTAL_BYTES,
    .addr_mode = &__addr_mode_R_ADDR_MODE,
    .operation = &__base_MNEMONIC,
};"""

content = ""
insts = []
with open("inst.txt") as f:
    content = f.readlines()

for inst_set in content:
    mnemoninc, addr_mode, opcode = inst_set.strip().split("_")
    r_addr_mode = addr_mode[:3]
    total_bytes = 2
    if "ab" in addr_mode:
        total_bytes += 1
    elif "imp" in addr_mode or "acc" in addr_mode:
        total_bytes = 1

    print(
        base_inst
            .replace("MNEMONIC", mnemoninc)
            .replace("OPCODE", opcode)
            .replace("R_ADDR_MODE", r_addr_mode)
            .replace("ADDR_MODE", addr_mode)
            .replace("TOTAL_BYTES", str(total_bytes))
    )
    print()
    insts.append(f"{mnemoninc}_{addr_mode}")

for inst in insts:
    print(f"register_instruction({inst});")
