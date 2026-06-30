// FUNC_NAME: ResourcePool::getOrAllocateSlot
// Address: 0x0043c390
// Role: Retrieves or allocates a slot in the resource pool for a given owner object.
//       Sets a corresponding bit in the owner's 64-bit slot usage mask (offsets +0x148 and +0x14c).
//       Returns a pointer to the slot data (size 0x1c) or -1 on failure.

// Forward declarations of helper functions:
// FUN_0043c250: int findSlot(ResourcePool* pool);
// FUN_004dafd0: int generateSlotKey();
// FUN_0043c140: int addSlot(ResourcePool* pool, int key, int flags);
// FUN_0043c8f0: void markSlotUsed(void* owner);  // called with &owner

// Global string pointer used when no slot is found (likely a name for logging)
extern char* g_slotName;

int ResourcePool::getOrAllocateSlot(ResourcePool* pool, void* owner) {
    int slotIndex;
    int ownerKey;

    // Step 1: Try to find an existing free slot
    slotIndex = findSlot(pool);
    if (slotIndex == -1) {
        // No free slot: attempt to create one.
        // g_slotName might be a naming hint from the caller (passed in EAX)
        if (g_slotName == nullptr || *g_slotName == '\0') {
            ownerKey = -1;
        } else {
            ownerKey = generateSlotKey(); // hash or unique ID from name
        }
        if (ownerKey != -1) {
            slotIndex = addSlot(pool, ownerKey, 0); // add a new slot with key and flags=0
        }
        if (slotIndex == -1) {
            return -1; // allocation failed
        }
    }

    // Step 2: Notify the owner that this slot is now in use.
    // The function may modify the owner pointer itself (unused here) or update internal state.
    markSlotUsed(&owner); // owner is passed by address; side effect on the pointed object

    // Step 3: Set the bit corresponding to slotIndex in the owner's 64-bit usage mask.
    // Offsets: +0x148 (low 32 bits), +0x14c (high 32 bits) relative to owner.
    uint64_t bitMask = (uint64_t)1 << slotIndex;
    *(uint32_t*)((uint8_t*)owner + 0x148) |= (uint32_t)bitMask;
    *(uint32_t*)((uint8_t*)owner + 0x14c) |= (uint32_t)(bitMask >> 32);

    // Step 4: Validate slot index and return pointer to slot data.
    if (slotIndex > 63) {
        return -1; // out of bounds (mask would be incomplete)
    }
    // pool->slots is an array of structs of size 0x1c located at *(pool + 4)
    SlotData* slots = *(SlotData**)((uint8_t*)pool + 4);
    return (int)&slots[slotIndex]; // return as int per original casting
}