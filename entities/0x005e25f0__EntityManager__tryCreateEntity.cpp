// FUNC_NAME: EntityManager::tryCreateEntity
// Address: 0x005e25f0
// __thiscall: this at param_1 (ecx)
// Attempts to create a new entity from a prototype. Checks manager enable flag, finds a slot by type,
// and initializes the slot if the system is ready.
// Each slot is 0x4a4 bytes. The sub-object lives at slot+0x04, and handle is stored at slot+0x490.

uint __thiscall EntityManager::tryCreateEntity(undefined4 *outHandle, int prototype, undefined4 slotId, undefined4 extraData)
{
    uint index;
    uint result = 0;

    *outHandle = 0;
    // +0x1744: m_bActive (bool)
    if (*(char *)((int)this + 0x1744) != '\0' && prototype != 0)
    {
        // Map slotId to an index (FUN_005e26a0)
        index = getSlotIndex(this, slotId);
        if (index < 5) // Maximum of 5 slots
        {
            // Slot at this + index * 0x4a4
            int slotBase = (int)this + index * 0x4a4;
            // Global system ready? (FUN_005e8670)
            if (isSystemReady())
            {
                undefined4 handle = allocateHandle(); // FUN_005e2680
                *outHandle = handle;
                // Store handle at slot+0x490
                *(undefined4 *)(slotBase + 0x490) = handle;
                // Associate prototype (FUN_004d3d90)
                setPrototypeReference(prototype);
                // Initialize sub-object at slot+4 (FUN_005e9220)
                result = initializeSlotObject(slotBase + 4, prototype, slotId, extraData);
                return result;
            }
        }
    }
    // Failure path: return 0 (original in_EAX&0xffffff00 is assumed zero)
    return 0;
}