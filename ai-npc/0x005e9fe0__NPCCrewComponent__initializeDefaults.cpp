// FUNC_NAME: NPCCrewComponent::initializeDefaults
void __thiscall NPCCrewComponent::initializeDefaults(undefined2 *this) {
    // Global default initialization value (likely 0xCDCDCDCD or similar)
    int defaultVal = g_defaultInitValue; // DAT_00e2b1a4

    // Byte offsets relative to this pointer
    // +0x00: two shorts (maybe flags or state)
    *(short *)this = 0;                          // offset 0-1
    *(short *)((char *)this + 2) = 0;            // offset 2-3

    // +0x04: first default value
    *(int *)((char *)this + 4) = defaultVal;     // offset 4-7
    // +0x08: zero
    *(int *)((char *)this + 8) = 0;              // offset 8-11
    // +0x0C: zero
    *(int *)((char *)this + 12) = 0;             // offset 12-15
    // +0x10: second default value
    *(int *)((char *)this + 16) = defaultVal;    // offset 16-19
    // +0x14: zero
    *(int *)((char *)this + 20) = 0;             // offset 20-23
    // +0x18: zero
    *(int *)((char *)this + 24) = 0;             // offset 24-27

    // Array of 16 entries starting at offset 0x20, each entry is 8 bytes (two ints)
    // The pattern: defaultVal, 0, defaultVal, 0, ... for 16 pairs
    for (int i = 0; i < 16; i++) {
        int *pairFirst = (int *)((char *)this + 0x20 + i * 8);
        pairFirst[0] = defaultVal;  // first int of pair
        pairFirst[1] = 0;           // second int of pair
    }

    // +0xA0: zero (maybe current index or count)
    *(int *)((char *)this + 0xA0) = 0;   // offset 0xA0
    // +0xA4: zero
    *(int *)((char *)this + 0xA4) = 0;   // offset 0xA4
    // +0xA8: zero (0x54 * 2 = 0xA8)
    *(int *)((char *)this + 0xA8) = 0;   // offset 0xA8

    // +0xAC: sentinel value (-1)
    *(int *)((char *)this + 0xAC) = -1;  // offset 0xAC

    // +0xB0: 8-byte zero (maybe timer)
    *(long long *)((char *)this + 0xB0) = 0; // offset 0xB0-0xB7
    // +0xB8: single byte zero (flag)
    *(char *)((char *)this + 0xB8) = 0;     // offset 0xB8

    // +0xEC: default timeout (96000 ms or ticks)
    *(int *)((char *)this + 0xEC) = 96000;  // offset 0xEC
    // +0xF0: zero (remaining time?)
    *(int *)((char *)this + 0xF0) = 0;      // offset 0xF0
}