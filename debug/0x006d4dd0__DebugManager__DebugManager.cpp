// FUNC_NAME: DebugManager::DebugManager
#include <cstdint>

// Constants for sentinel values (debug initialization markers)
static const uint32_t kSentinelBad = 0xBADBADBA;
static const uint32_t kSentinelBeef = 0xBEEFBEEF;
static const uint32_t kSentinelEA = 0xEAC15A55;
static const uint32_t kSentinel911 = 0x91100911;

// Global pointer to the singleton DebugManager instance
DebugManager* g_debugManager;

// Forward declarations of helper functions called (assumed base class init)
void __thiscall initBasePart1(uint32_t param);
void __thiscall initBasePart2();

class DebugManager {
public:
    // vtable pointer at offset 0x00
    void** vtable;

    // Other virtual function pointers at specific offsets (indices in array of pointers)
    // offset +0x3C (0xF*4) -> &PTR_LAB_00d5f3e0
    void* funcPtrAt0x3C;
    // offset +0x48 (0x12*4) -> &PTR_LAB_00d5f3dc
    void* funcPtrAt0x48;
    // offset +0x50 (0x14*4) -> &PTR_LAB_00d5f3d8
    void* funcPtrAt0x50;
    // offset +0x58 (0x16*4) -> &PTR_LAB_00d5f3d4 (overwritten last)
    void* funcPtrAt0x58;

    // Data members before the large sentinel array
    uint32_t dataAt0x28;   // from _DAT_00d5780c
    uint32_t dataAt0x29;   // from DAT_00d5f00c
    uint32_t dataAt0x2A;   // zero
    uint32_t dataAt0x2B;   // from DAT_00e447a4

    // Large sentinel array: occupies indices 0x2D to 0x88 (inclusive) -> 92 dwords = 23 blocks of 4 dwords each
    uint32_t sentinelArray[92];
};

// __thiscall constructor at address 0x006d4dd0
DebugManager* __thiscall DebugManager::DebugManager(uint32_t someParam) {
    // Call base class or some initialization routines
    initBasePart1(someParam);

    // Setup vtable and function pointers
    vtable = &PTR_FUN_00d5f3f0;                             // +0x00
    funcPtrAt0x3C = &PTR_LAB_00d5f3e0;                     // +0x3C
    funcPtrAt0x48 = &PTR_LAB_00d5f3dc;                     // +0x48
    funcPtrAt0x50 = &PTR_LAB_00d5f3d8;                     // +0x50
    funcPtrAt0x58 = &PTR_LAB_00d5f3d4;                     // +0x58 (last assignment to +0x58)

    // Another base initialization
    initBasePart2();

    // Initialize the sentinel array (23 blocks of 4 dwords each)
    // Starting at offset 0x2D*4 = 0xB4 (180 bytes)
    for (int i = 0x2D; i <= 0x88; i += 4) {
        sentinelArray[i - 0x2D]     = kSentinelBad;
        sentinelArray[i - 0x2D + 1] = kSentinelBeef;
        sentinelArray[i - 0x2D + 2] = kSentinelEA;
        sentinelArray[i - 0x2D + 3] = kSentinel911;
    }

    // Set data members from globals (indices 0x28-0x2B)
    dataAt0x28 = g_global1;   // _DAT_00d5780c
    dataAt0x29 = g_global2;   // DAT_00d5f00c
    dataAt0x2A = 0;
    dataAt0x2B = g_global3;   // DAT_00e447a4

    // Store this pointer globally
    g_debugManager = this;

    return this;
}