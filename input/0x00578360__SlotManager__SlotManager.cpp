// FUNC_NAME: SlotManager::SlotManager
// Function address: 0x00578360
// Role: Constructor for SlotManager class that manages a pool of fixed-size slots (0xE0 bytes each).
// Each slot is presumably a packet window or similar object (32 max, based on 0x20 constants).
// Initializes internal state, allocates an array of slots, calls individual slot initialization.

void SlotManager::SlotManager(int slotCount) // param_1 = slotCount
{
    // Call base class initializer (likely ObjectPool or similar)
    FUN_00570a70();

    // Set vtable pointer
    this->vtable = &PTR_FUN_00e3ac08; // +0x00 vtable

    // Core configuration
    this->slotCount = slotCount;           // +0xB9
    this->reserved0 = 0;                   // +0xBA
    this->reserved1 = 0;                   // +0xBC
    this->invalidIndex1 = -1;              // +0xB8
    this->invalidIndex2 = -1;              // +0xBE
    this->invalidIndex3 = -1;              // +0xC2
    this->invalidIndex4 = -1;              // +0xC4
    this->someFlag1 = 0;                   // +0xBF
    this->someFlag2 = 0;                   // +0xC0
    this->someFlag3 = 0;                   // +0xC1
    this->someFlag4 = 0;                   // +0xC3
    this->someFlag5 = 0;                   // +0xC5
    this->someFlag6 = 0;                   // +0xC6
    this->reserved2 = 0;                   // +0xC7 (offset 199)
    this->someFlag7 = 0;                   // +0xC9
    this->someFlag8 = 0;                   // +0xCA
    this->someFlag9 = 0;                   // +0xCB
    this->someFlag10 = 0;                  // +0xCC
    this->someFlag11 = 0;                  // +0xCD
    this->someFlag12 = 0;                  // +0xCE
    this->someFlag13 = 0;                  // +0xCF
    this->someFlag14 = 0;                  // +0xD0

    // Constants
    this->priority = 4;                    // +0xBD
    this->maxSlots = 32;                   // +0xC8 (200 decimal)
    this->defaultPriority2 = 4;            // +0xD1
    this->invalidIndex5 = -1;              // +0xD2
    this->someFlag15 = 0;                  // +0xD3
    this->someFlag16 = 0;                  // +0xD4
    this->someFlag17 = 0;                  // +0xD5
    this->invalidIndex6 = -1;              // +0xD6
    this->someFlag18 = 0;                  // +0xD7
    this->invalidIndex7 = -1;              // +0xD8
    this->someFlag19 = 0;                  // +0xD9
    this->someFlag20 = 0;                  // +0xDA
    this->someFlag21 = 0;                  // +0xDB
    this->maxSlots2 = 32;                  // +0xDC
    this->someFlag22 = 0;                  // +0xDD? Actually set later, see below

    // Allocate array of slot objects (each 0xE0 bytes)
    // Use global allocator function from DAT_0120556c
    // param: size = slotCount * 0xE0, flags (local_c = 2, local_8 = 0x10, local_4 = 0)
    int allocFlags[3] = {2, 0x10, 0};
    void* allocFunc = *(void**)(DAT_0120556c);
    this->slotsArray = ((void* (*)(int, int*))allocFunc)(slotCount * 0xE0, allocFlags); // +0xBB

    // Initialize each slot by calling Fun_00588f80 (slot constructor)
    for (int i = 0; i < slotCount; i++)
    {
        if (this->slotsArray + i * 0xE0 != 0)
        {
            FUN_00588f80(); // Called on each slot (likely sets internal data)
        }
    }

    // Free list setup
    this->freeListHead = &this->freeListNext; // +0xDD points to +0xE5 (first element of free list)
    this->freeListNext = 0;                    // +0xE5
    this->someGlobalData = DAT_00e39f98;       // +0xE6
    this->freeListActive = 1;                  // +0xE7
    this->freeListTail = 0;                    // +0xE8

    // Clear remaining fields
    this->reserved3 = 0; // +0xE9
    this->reserved4 = 0; // +0xEA
}