// FUNC_NAME: DebugAllocatorBlock::DebugAllocatorBlock
// Function at 0x008e1a10: Constructor for a debug memory block with signature patterns.
// Initializes vtable pointer, several unknown function pointers, and writes debug sentinel values.
// Likely used for memory corruption detection in EA EARS engine.

class DebugAllocatorBlock {
public:
    // Offset 0x00: vtable pointer (set to PTR_FUN_00d80248)
    void* vtable;

    // Offsets (index * 4) from base:
    // +0x3C: unknown pointer (set to PTR_LAB_00d80238)
    void* unknownPtr0F;
    // +0x48: unknown pointer (set to PTR_LAB_00d80234)
    void* unknownPtr12;
    // +0x50: unknown pointer (set to PTR_LAB_00d80230)
    void* unknownPtr14;
    // +0x54: unknown pointer (set to PTR_LAB_00d801d0)
    void* unknownPtr15;
    // +0x58: unknown pointer (set to PTR_LAB_00d80168)
    void* unknownPtr16;

    // Debug signature fields at offset 0x60..0x65 (index * 4 => byte offset 0x180..0x194)
    // +0x180: signature1 = 0xbadbadba
    uint32_t signature1;
    // +0x184: signature2 = 0xbeefbeef
    uint32_t signature2;
    // +0x188: signature3 = 0xeac15a55
    uint32_t signature3;
    // +0x18C: signature4 = 0x91100911
    uint32_t signature4;
    // +0x190: signature5 = 0
    uint32_t signature5;
    // +0x194: signature6 = 0
    uint32_t signature6;

    // Constructor (__thiscall)
    DebugAllocatorBlock(uint32_t param_2) {
        // Call to base initialization function (e.g., memory pool setup, size 0x4000)
        FUN_0046e6b0(param_2, 0x4000);

        // Set vtable pointer
        vtable = &PTR_FUN_00d80248;

        // Set unknown function pointers (possibly vtables for multiple inheritance)
        unknownPtr0F = &PTR_LAB_00d80238;
        unknownPtr12 = &PTR_LAB_00d80234;
        unknownPtr14 = &PTR_LAB_00d80230;
        unknownPtr15 = &PTR_LAB_00d801d0;
        unknownPtr16 = &PTR_LAB_00d80168;

        // Write debug sentinel values for corruption detection
        signature1 = 0xbadbadba;
        signature2 = 0xbeefbeef;
        signature3 = 0xeac15a55;
        signature4 = 0x91100911;
        signature5 = 0;
        signature6 = 0;
    }
};