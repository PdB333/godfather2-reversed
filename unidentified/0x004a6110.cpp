// FUN_004a6110: CWorldManager::updateObjectStateFlags
// Address: 0x004a6110
// Role: Updates per-object state flags for interactable and vehicle lists based on virtual function checks.
// The class uses an array of 8-byte entries (pointer + flags) stored at offset 0x1d (count at 0x1e)
// and a separate count at 0x1b for another object type (likely vehicles).
// After updating flags, calls helper functions (likely post-processing).
// Note: This function uses __thiscall convention; 'this' is in ECX/EDI.

void CWorldManager::updateObjectStateFlags()
{
    // Fields of this class (estimated offsets in bytes):
    // +0x1d (0x74 for 32-bit? Actually offset in dwords): pointer to array of 8-byte entries
    // +0x1e (0x78): number of entries in that array
    // +0x1b (0x6c): number of secondary objects (e.g., vehicles)
    // +0x20 (0x80): flags for this manager itself

    uint i;
    int count1 = *(int*)((char*)this + 0x78); // +0x1e * 4 = 0x78
    if (count1 != 0)
    {
        char* arrayPtr = *(char**)((char*)this + 0x74);
        for (i = 0; i < (uint)count1; i++)
        {
            // Each entry is 8 bytes: [0] object pointer, [4] flags (ushort in low 16 bits)
            uint* entry = (uint*)(arrayPtr + i * 8);
            void* objPtr = (void*)*entry;
            if (objPtr != nullptr)
            {
                // Call vtable functions on the object to determine state
                // vtable+4: isActive()
                if (((bool (__thiscall*)(void*))(* (int**)objPtr)[1])())
                {
                    *(ushort*)(entry + 1) |= 0x8;  // Set bit 3
                }
                // vtable+8: isVisible()
                if (((bool (__thiscall*)(void*))(* (int**)objPtr)[2])())
                {
                    *(ushort*)(entry + 1) |= 0x10; // Set bit 4
                }
                // vtable+0x18: isDynamic()
                if (((bool (__thiscall*)(void*))(* (int**)objPtr)[6])())
                {
                    *(ushort*)(entry + 1) |= 0x400; // Set bit 10
                }
            }
        }
    }

    // Second loop: process vehicles or other secondary objects
    int count2 = *(int*)((char*)this + 0x6c); // +0x1b * 4 = 0x6c
    if (count2 != 0)
    {
        for (i = 0; i < (uint)count2; i++)
        {
            // Assume FUN_004a62b0 is a method that processes each vehicle index
            processVehicleEntry(); // Renamed from FUN_004a62b0
        }
    }

    // Check state of the manager itself
    if (((bool (__thiscall*)(void*))(* (int**)this)[6])()) // vtable+0x18
    {
        *(ushort*)((char*)this + 0x80) |= 1; // Set bit 0 in manager flags
    }

    // Final post-processing functions (likely update transforms and visibility)
    updateTransforms();  // Renamed from FUN_004a6710
    updateVisibility();  // Renamed from FUN_004a67a0
}