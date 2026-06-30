// FUNC_NAME: setGlobalFlag
void setGlobalFlag(int flagIndex, int value) {
    // Global state flags/options at DAT_00e50be4 (8 bytes), DAT_00e50bec (8 bytes), DAT_00e50bf4 (4 bytes)
    if (flagIndex == 0) {
        *(uint8_t*)(0x00e50be4) = (uint8_t)(value != 0);
        return;
    }
    if (flagIndex == 1) {
        *(uint8_t*)(0x00e50be4 + 1) = (uint8_t)(value != 0);
        return;
    }
    if (flagIndex == 2) {
        *(uint8_t*)(0x00e50be4 + 2) = (uint8_t)(value != 0);
        return;
    }
    if (flagIndex == 3) {
        *(uint8_t*)(0x00e50be4 + 3) = (uint8_t)(value != 0);
        return;
    }
    if (flagIndex == 4) {
        *(uint8_t*)(0x00e50be4 + 4) = (uint8_t)(value != 0);
        return;
    }
    if (flagIndex == 5) {
        *(uint8_t*)(0x00e50be4 + 5) = (uint8_t)(value != 0);
        return;
    }
    if (flagIndex == 6) {
        *(uint8_t*)(0x00e50be4 + 6) = (uint8_t)(value != 0);
        return;
    }
    if (flagIndex == 7) {
        *(uint8_t*)(0x00e50be4 + 7) = (uint8_t)(value != 0);
        return;
    }
    // Second group of flags at 0x00e50bec
    if (flagIndex == 8) {
        *(uint8_t*)(0x00e50bec) = (uint8_t)(value != 0);
        return;
    }
    if (flagIndex == 9) {
        *(uint8_t*)(0x00e50bec + 1) = (uint8_t)(value != 0);
        return;
    }
    // Word-sized value at offset 4 from base2 (0x00e50bec + 4)
    if (flagIndex == 10) {
        *(int*)(0x00e50bec + 4) = value;
        return;
    }
    // Separate 4-byte value at 0x00e50bf4
    if (flagIndex == 11) {
        *(int*)(0x00e50bf4) = value;
    }
    // Note: values for indices 8-10 are stored contiguously at 0x00e50bec (8 bytes total: byte, byte, pad?, int)
    // 0x00e50bf4 is a separate 4-byte field
}