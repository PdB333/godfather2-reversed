// FUNC_NAME: SomeManager::resetState
// Function address: 0x004c69b0
// This function appears to initialize a manager/state structure with defaults.
// It zeros many fields and sets specific offsets to global default values.
// There is an array of 2 sub-blocks (each 64 bytes) that each contain 4 marker values
// separated by 4 zero words, all set to the same default.

void SomeManager::resetState()
{
    // Global defaults (likely constants or singletons)
    int defaultValue1 = (int)DAT_00e2b1a4; // +0x2b, +0x2c, +0x2d, used in sub-blocks
    int defaultValue2 = (int)DAT_00e2e230; // +0x2e

    // Initialize first few fields to zero
    this->field_00 = 0; // +0x00
    this->field_04 = 0; // +0x04
    this->field_08 = 0; // +0x08

    // Zero out fields at higher offsets
    this->field_90 = 0; // +0x90 (array or separate block)
    this->field_94 = 0; // +0x94
    this->field_98 = 0; // +0x98
    this->field_9C = 0; // +0x9C
    this->field_A0 = 0; // +0xA0
    this->field_A4 = 0; // +0xA4
    this->field_A8 = 0; // +0xA8
    this->field_AC = defaultValue1; // +0xAC
    this->field_B8 = defaultValue2; // +0xB8 (skipping 0xB0-0xB7, set below)
    this->field_BC = 0; // +0xBC
    this->field_C0 = 0; // +0xC0
    this->field_C4 = 0; // +0xC4
    this->field_C8 = 0; // +0xC8
    this->field_CC = 0; // +0xCC
    this->field_B0 = defaultValue1; // +0xB0
    this->field_B4 = defaultValue1; // +0xB4

    // Initialize two sub-blocks (each 64 bytes = 16 dwords)
    // Sub-block 1 starts at offset +0x10
    // Sub-block 2 starts at offset +0x50
    // Each sub-block has marker values at indices 0,5,10,15 (relative to sub-block start)
    // separated by zeros.

    for (int i = 0; i < 2; i++)
    {
        // Base pointer to current sub-block (offset +0x10 + i*0x40)
        int* subBlock = &this->field_10 + (i * 16); // 16 dwords per sub-block

        // Set the 4 marker slots to defaultValue1, zeros in between
        subBlock[0] = defaultValue1; // marker 0
        subBlock[1] = 0;
        subBlock[2] = 0;
        subBlock[3] = 0;
        subBlock[4] = 0;
        subBlock[5] = defaultValue1; // marker 1
        subBlock[6] = 0;
        subBlock[7] = 0;
        subBlock[8] = 0;
        subBlock[9] = 0;
        subBlock[10] = defaultValue1; // marker 2
        subBlock[11] = 0;
        subBlock[12] = 0;
        subBlock[13] = 0;
        subBlock[14] = 0;
        subBlock[15] = defaultValue1; // marker 3
    }

    return;
}