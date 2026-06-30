// FUNC_NAME: RijndaelContextManager::acquireOrFindContext
#include <cstdint>

// Static pool of Rijndael context slots. Each slot is 44 bytes (0x2c).
// There are 32 slots (range 0x1205a88 - 0x1206008 = 0x580 bytes).
// Slot layout (offsets from start):
// +0x00: uint64 contextIdOrFunctionPair; // includes flags: low 32-bit non-zero means used, byte at +0x04 must be 0x06 for valid.
// +0x08: uint64 data2;
// +0x10: uint64 data3;
// +0x18: uint64 data4;
// +0x20: uint64 data5;
// +0x28: uint32 functionPointer; // pointer to a function (4 bytes)
// Total: 0x2c (44 bytes)
struct RijndaelContextSlot {
    uint64 field_00; // +0x00
    uint64 field_08; // +0x08
    uint64 field_10; // +0x10
    uint64 field_18; // +0x18
    uint64 field_20; // +0x20
    void*  field_28; // +0x28 (function pointer)
};
static_assert(sizeof(RijndaelContextSlot) == 0x2c, "Slot size mismatch");

// Global array of slots (declared somewhere in the binary at 0x01205a88)
extern RijndaelContextSlot g_rijndaelContextPool[32];

// External initialization values (from PE data section at 0x00e27a84 etc.)
extern uint64 _PTR_s_rijndael_00e27a84;    // +0x00 value
extern uint64 DAT_00e27a8c;                 // +0x08 value
extern uint64 DAT_00e27a94;                 // +0x10 value
extern uint64 _PTR_FUN_00e27a9c;           // +0x18 value
extern uint64 _PTR_FUN_00e27aa4;           // +0x20 value
extern void* PTR_FUN_00e27aac;             // +0x28 value

// Returns slot index (0-31) of an existing or newly allocated context, or -1 on failure.
int RijndaelContextManager::acquireOrFindContext()
{
    // Phase 1: look for a slot that is already initialized (used and marked with 0x06).
    for (int i = 0; i < 32; ++i) {
        RijndaelContextSlot& slot = g_rijndaelContextPool[i];
        // Check: if the first 4 bytes are non-zero AND the byte at offset 4 equals 0x06.
        int* pLowInt = reinterpret_cast<int*>(&slot.field_00);
        char* pByteOffset4 = reinterpret_cast<char*>(&slot.field_00) + 4;
        if (*pLowInt != 0 && *pByteOffset4 == 0x06) {
            return i; // Found existing valid slot
        }
    }

    // Phase 2: search for an empty slot (first 4 bytes zero) and initialize it.
    for (int i = 0; i < 32; ++i) {
        int* pLowInt = reinterpret_cast<int*>(&g_rijndaelContextPool[i].field_00);
        if (*pLowInt == 0) {
            // Found empty slot; fill it with predefined data.
            RijndaelContextSlot& slot = g_rijndaelContextPool[i];
            slot.field_00 = _PTR_s_rijndael_00e27a84;
            slot.field_08 = DAT_00e27a8c;
            slot.field_10 = DAT_00e27a94;
            slot.field_18 = _PTR_FUN_00e27a9c;
            slot.field_20 = _PTR_FUN_00e27aa4;
            slot.field_28 = PTR_FUN_00e27aac;
            return i;
        }
    }

    // No free slot available.
    return -1;
}