// FUNC_NAME: SoundManager::~SoundManager

void __fastcall SoundManager::destructor(uint* thisPtr)
{
    uint* renderObjectPtr;

    // Set virtual function tables (multiple inheritance interfaces)
    thisPtr[0] = (uint)&vtable_SoundManager;          // +0x00: base class vtable
    thisPtr[0xf] = (uint)&vtable_SoundManager_IFace1; // +0x3C: first interface
    thisPtr[0x12] = (uint)&vtable_SoundManager_IFace2;// +0x48: second interface

    // If a render object is attached (pointer at +0xD0)
    renderObjectPtr = (uint*)thisPtr[0x34];
    if (renderObjectPtr != 0)
    {
        // Set flag 0x200000 on render object (likely "flagged for destruction")
        renderObjectPtr[3] |= 0x200000;                // +0x0C

        // Remove render object from any update lists
        FUN_0051d6b0(); // e.g., removeFromUpdateList()

        // If render object has a child pointer at +0x08, clear it
        if (*(uint**)(renderObjectPtr + 2) != 0)       // +0x08
        {
            **(uint**)(renderObjectPtr + 2) = 0;
            *(uint**)(renderObjectPtr + 2) = 0;
        }
    }

    // Destroy 6 embedded sub-objects (likely SoundSlot instances)
    // Each sub-object is 8 bytes (two ints at interval 0x08)
    for (int i = 0; i < 6; i++)
    {
        uint* slot = thisPtr + 0x14 + i * 2;          // +0x50, +0x58, +0x60, +0x68, +0x70, +0x78
        FUN_004086d0(slot); // destructor call (e.g., SoundSlot::~SoundSlot())
        FUN_00408310(slot); // operator delete (placement free)
    }

    // Destroy three global singleton objects (sound output instances)
    FUN_004086d0(&DAT_0120e944); // stereo output object
    FUN_004086d0(&DAT_0120e94c); // mono output object
    FUN_004086d0(&DAT_0120e93c); // 3D output object

    // Final cleanup of render object if still attached
    if (thisPtr[0x34] != 0)
    {
        // Clear child pointer and null out render object handle
        *(uint**)(thisPtr[0x34] + 8) = 0;               // +0x08
        thisPtr[0x34] = 0;
    }

    // Perform any remaining cleanup (e.g., thread shutdown, memory pool release)
    FUN_0046c640(); // finalization routine

    return;
}