// FUNC_NAME: ObjectManager::getValueFromHandle
// Address: 0x0061af30
// Reconstructed from Ghidra decompilation of unknown class method.
// The function uses a handle passed via EAX to lookup in a global table at 0x011a0f38.
// Table has 4096 entries of 0x38 bytes each.
// Offset 0x00: pointer to a primary object; offset 0x20: pointer to secondary structure.
// Helper function FUN_0061b210 returns an index into secondary array.
// Returns uint32 from that array.

#include <cstdint>

// Global table of 4096 structures, each 0x38 (56) bytes, located at 0x011a0f38
extern uint8_t g_ObjectTable[0x1000 * 0x38];

// Helper function (FUN_0061b210): takes a pointer to a local buffer, returns an index
extern int32_t resolveSubIndex(void* buffer);

uint32_t getValueFromHandle(uint32_t handle)
{
    uint32_t* puVar1;
    int32_t* piVar2;
    int32_t iVar3;
    uint32_t defaultReturn = 0; // unaff_EDI placeholder – original returns whatever was in EDI

    // Bounds check and sentinel against overflow (handle * 0x38 must not equal 0xFEE5F0D8)
    if ((handle < 0x1000) &&
        (handle * 0x38 != 0xFEE5F0D8u) &&
        (*(int32_t*)(g_ObjectTable + handle * 0x38) != 0))
    {
        // Retrieve pointer from structure at offset +0x20 (32 bytes)
        piVar2 = *(int32_t**)(*(int32_t*)(g_ObjectTable + handle * 0x38) + 0x20);
        if (piVar2 != nullptr)
        {
            // Call helper to compute an index (likely into a secondary array)
            iVar3 = resolveSubIndex(&defaultReturn);
            if (iVar3 >= 0)
            {
                // Access array at base = *piVar2 (int32 value), offset 4 + iVar3*8
                puVar1 = (uint32_t*)(*piVar2 + 4 + iVar3 * 8);
                if (puVar1 != nullptr)
                {
                    return *puVar1;
                }
            }
        }
    }
    return defaultReturn;
}