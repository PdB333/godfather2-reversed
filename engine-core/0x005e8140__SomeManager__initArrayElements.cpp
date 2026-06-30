// FUNC_NAME: SomeManager::initArrayElements
// Address: 0x005e8140
// Role: Initializes a structure containing an array of 4 sub-structures (each 108 bytes) and additional fields.
// The function zeros the first element and then loops to zero 4 blocks of 20 words each, separated by 7-word gaps.
// After the loop, calls another initialization routine and zeros four more words at high offsets.

undefined4 * __fastcall SomeManager::initArrayElements(undefined4 *this)
{
    undefined4 *puVar1;
    undefined4 *puVar2;
    int iVar3;

    // Zero first word (likely a pointer or flag)
    *this = 0;

    // Initialize loop: puVar2 starts at this[1], puVar1 at this[7]
    // iVar3 = 3, loop runs until iVar3 < 0 (4 iterations)
    iVar3 = 3;
    puVar2 = this + 1;
    puVar1 = this + 7;
    do {
        // Zero the first word of the current sub-structure (at puVar2)
        *puVar2 = 0;
        // Zero 19 words starting at puVar1[-5] (which is puVar2+1) up to puVar1[0xd] (puVar2+19)
        puVar1[-5] = 0;   // offset within sub-structure: +1 word from puVar2
        puVar1[-4] = 0;   // +2
        puVar1[-3] = 0;   // +3
        puVar1[-2] = 0;   // +4
        puVar1[-1] = 0;   // +5
        *puVar1 = 0;      // +6
        puVar1[1] = 0;    // +7
        puVar1[2] = 0;    // +8
        puVar1[3] = 0;    // +9
        puVar1[4] = 0;    // +10
        puVar1[5] = 0;    // +11
        puVar1[6] = 0;    // +12
        puVar1[7] = 0;    // +13
        puVar1[8] = 0;    // +14
        puVar1[9] = 0;    // +15
        puVar1[10] = 0;   // +16
        puVar1[0xb] = 0;  // +17
        puVar1[0xc] = 0;  // +18
        puVar1[0xd] = 0;  // +19
        // Advance both pointers by 27 words (size of each sub-structure)
        puVar2 = puVar2 + 0x1b;
        puVar1 = puVar1 + 0x1b;
        iVar3 = iVar3 + -1;
    } while (-1 < iVar3);

    // Call another initialization function (likely sets remaining fields)
    FUN_005e7db0();

    // Zero additional fields at high offsets (0x125-0x128 words from start)
    // These are at byte offsets: 0x494, 0x498, 0x49C, 0x4A0
    this[0x125] = 0;
    this[0x126] = 0;
    this[0x127] = 0;
    this[0x128] = 0;

    return this;
}