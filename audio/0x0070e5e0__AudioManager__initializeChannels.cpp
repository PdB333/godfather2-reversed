// FUNC_NAME: AudioManager::initializeChannels

void __fastcall AudioManager::initializeChannels(int* this)
{
    // vtable pointers (multiple inheritance)
    *this = (int)&PTR_FUN_00d61854;                // +0x00 primary vtable
    this[0x0f] = (int)&PTR_LAB_00d61844;           // +0x3C secondary vtable
    this[0x12] = (int)&PTR_LAB_00d61840;           // +0x48 tertiary vtable

    // Offsets (in int units) for 24 slot structures (each 2 ints apart)
    const int slotOffsets[24] = {
        0xe0, 0xe2, 0xe4, 0xe6, // group 1 (0x380–0x398)
        0xd8, 0xda, 0xdc, 0xde, // group 2 (0x360–0x378)
        200,                     // 0xc8 (0x320)
        0xca, 0xcc, 0xce, 0xd0, 0xd2, 0xd4, 0xd6, // group 3 (0x328–0x358)
        0xe8, 0xea, 0xec, 0xee, 0xf0, 0xf2,       // group 4 (0x3a0–0x3c8)
        0xf4, 0xf6                                  // group 5 (0x3d0–0x3d8)
    };

    // First pass: zero-initialize all slot structures
    for (int i = 0; i < 22; i++) {
        FUN_004086d0(this + slotOffsets[i]); // likely memset or placement new
    }

    // Second pass: construct slot structures
    for (int i = 0; i < 22; i++) {
        FUN_00408310(this + slotOffsets[i]); // constructor for each slot
    }

    // Conditional randomization of slots
    // +0x88: bool m_useRandom, +0xf8: int m_numSlots
    if (*(char*)(this + 0x88) != '\0' && this[0xf8] > 0) {
        for (int i = 0; i < this[0xf8]; i++) {
            void* slotPtr = thunk_FUN_004ab300(); // get pointer to i-th slot
            if (slotPtr != 0) {
                float randomValue = (float)FUN_004aabd0(); // generate random float
                FUN_004aa8c0(randomValue);                // set some parameter
                FUN_004aad70(this + 0x14);                // apply to channel at +0x50
            }
        }
    }

    // Initialize 16 stream/controller slots
    for (int i = 0; i < 16; i++) {
        FUN_004ab210(); // likely InitializeStreamSlot()
    }

    // Initialize the last two slot structures (indices 22 and 23)
    FUN_004086d0(this + 0xf4);
    FUN_004086d0(this + 0xf6);
    FUN_00408310(this + 0xf4);
    FUN_00408310(this + 0xf6);

    // Finalize audio subsystem
    FUN_0046c640(); // likely AudioManager::postInit() or similar
}