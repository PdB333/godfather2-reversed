// FUNC_NAME: setFlagBit5
extern char* DAT_01223484; // Global pointer to some manager/object

void setFlagBit5(char param_1) {
    // Offset 0x37c is a flags field (bit 5 = 0x20)
    uint* flags = (uint*)(DAT_01223484 + 0x37c);
    if (param_1 != '\0') {
        *flags |= 0x20;
    } else {
        *flags &= ~0x20;
    }
}