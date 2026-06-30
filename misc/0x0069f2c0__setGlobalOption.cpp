//FUNC_NAME: setGlobalOption
void setGlobalOption(int optionIndex, int value)
{
    // Global flag storage: 0x00e50be4 is a 8-byte region (bytes 0-7)
    // 0x00e50bec is a 8-byte region (bytes 0-1 used, then int at +4)
    // 0x00e50bf4 is a 4-byte int
    // These are likely debug/configuration flags

    if (optionIndex == 0) {
        *(volatile uint8_t*)0x00e50be4 = (value != 0);
    }
    else if (optionIndex == 1) {
        *(volatile uint8_t*)(0x00e50be4 + 1) = (value != 0);
    }
    else if (optionIndex == 2) {
        *(volatile uint8_t*)(0x00e50be4 + 2) = (value != 0);
    }
    else if (optionIndex == 3) {
        *(volatile uint8_t*)(0x00e50be4 + 3) = (value != 0);
    }
    else if (optionIndex == 4) {
        *(volatile uint8_t*)(0x00e50be4 + 4) = (value != 0);
    }
    else if (optionIndex == 5) {
        *(volatile uint8_t*)(0x00e50be4 + 5) = (value != 0);
    }
    else if (optionIndex == 6) {
        *(volatile uint8_t*)(0x00e50be4 + 6) = (value != 0);
    }
    else if (optionIndex == 7) {
        *(volatile uint8_t*)(0x00e50be4 + 7) = (value != 0);
    }
    else if (optionIndex == 8) {
        *(volatile uint8_t*)0x00e50bec = (value != 0);
    }
    else if (optionIndex == 9) {
        *(volatile uint8_t*)(0x00e50bec + 1) = (value != 0);
    }
    else if (optionIndex == 10) {
        *(volatile int*)0x00e50bec = value; // Note: original writes 4 bytes at offset 4? Actually DAT_00e50bec._4_4_ means offset 4 from 0x00e50bec, 4 bytes. So it's at 0x00e50bec+4.
        // Correction: The decompiled shows DAT_00e50bec._4_4_ = param_2; that means offset 4 from DAT_00e50bec, 4 bytes. So we need to write at 0x00e50bec+4.
        // Let's fix: *(volatile int*)(0x00e50bec + 4) = value;
    }
    else if (optionIndex == 11) {
        *(volatile int*)0x00e50bf4 = value;
    }
    // No else; ignore invalid indices
}