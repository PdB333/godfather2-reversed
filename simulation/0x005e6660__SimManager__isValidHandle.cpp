// FUNC_NAME: SimManager::isValidHandle

// Function at 0x005e6660: Validates an entity handle by checking its index, magic/type, and active status.
// The handle is a 32-bit value: lower 16 bits = slot index (max 0x200 slots), upper 16 bits = type/magic.
// The global SimManager (at DAT_012234bc) contains an array of Entity structures at offset +0x10,
// each of size 0x30, with the full handle stored at offset +0x2C.
// Calls helper function at 0x005e5e60 to verify slot activity.

extern void* g_simManager; // DAT_012234bc

// Helper: checks whether slot at given index is active (returns nonzero if active)
int __cdecl checkSlotActive(unsigned int slotIndex, int unkZero); // FUN_005e5e60

struct Entity {
    uint8_t _pad0[0x2C];    // 0x00 - 0x2B
    uint32_t handle;         // +0x2C: full handle
    // remaining fields up to 0x30
};

bool SimManager::isValidHandle(uint32_t handle)
{
    uint16_t index = (uint16_t)(handle & 0xFFFF);
    if (index >= 0x200)
        return false;

    // Compute pointer to the entity structure in the array (manager + 0x10 + index * 0x30)
    uintptr_t entityAddr = reinterpret_cast<uintptr_t>(g_simManager) + 0x10 + (index * 0x30);
    Entity* entity = reinterpret_cast<Entity*>(entityAddr);
    if (entity == nullptr)
        return false;

    // Verify the full handle matches the stored value
    if (entity->handle != handle)
        return false;

    // Check if the slot is currently active via the helper
    return (checkSlotActive(index, 0) != 0);
}