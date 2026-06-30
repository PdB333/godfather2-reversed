// FUNC_NAME: Job::loadFromDataBlock
int __thiscall Job::loadFromDataBlock(Job *this, int *dataBlock) {
    int *ptr;
    int i;

    // Call some base initialization (likely base class constructor or common setup)
    FUN_00582090();

    // Copy 20 integers (80 bytes) starting at offset 0x84 from the data block
    // This could be a fixed-size data chunk (e.g., job flags, timers, etc.)
    for (i = 0x14; i != 0; i--) {
        *(int *)((char *)this + 0x84 + i * 4) = dataBlock[i];
    }

    // Clear a byte at offset 0x70 (likely a boolean flag)
    *(char *)((char *)this + 0x70) = 0;

    // Determine the actual data pointer based on flags and version
    if ((dataBlock[0xB] & 0x20U) == 0 || *dataBlock < 3) {
        if ((dataBlock[0xB] & 0x20U) == 0 || *dataBlock != 2) {
            // Standard format: skip 7 integers
            ptr = dataBlock + 7;
        } else {
            // Format version 2 with flag: skip 12 integers
            ptr = dataBlock + 0xC;
        }
    } else {
        // Format version >=3 with flag: pointer stored at dataBlock[0xC]
        ptr = (int *)dataBlock[0xC];
    }

    if (ptr == (int *)0x0) {
        // Null data: set defaults
        *(int *)((char *)this + 0x74) = 0;
        *(int *)((char *)this + 0x78) = 0;
        *(float *)((char *)this + 0x7C) = 0.0f;
        *(int *)((char *)this + 0x2C) = 1;    // Default value (maybe enabled flag)
        *(int *)((char *)this + 0x80) = 0;
    } else {
        // Load actual data from the resolved pointer
        *(int *)((char *)this + 0x74) = ptr[0];    // +0x74: some ID or handle
        *(int *)((char *)this + 0x78) = 0;          // +0x78: clear
        *(float *)((char *)this + 0x7C) = (float)ptr[1]; // +0x7C: float value (duration?)
        *(int *)((char *)this + 0x2C) = ptr[2];     // +0x2C: e.g., state/flag
        *(int *)((char *)this + 0x80) = ptr[3];     // +0x80: additional data
    }

    // Validation: check if field at +0x14 is -1 (uninitialized) or if float <= 0
    if ((*(int *)((char *)this + 0x14) == -1) || (*(float *)((char *)this + 0x7C) <= 0.0f)) {
        return 0; // invalid
    }
    return 1; // valid
}