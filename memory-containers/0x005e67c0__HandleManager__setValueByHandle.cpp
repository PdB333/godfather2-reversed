// FUNC_NAME: HandleManager::setValueByHandle
// Reconstructed C++ for function at 0x005e67c0
// Assigns a value to a field at offset 0x5C of an object identified by a 32-bit handle.
// Handle format: lower 16 bits = index into a slot array (max 512 slots, each 0x30 bytes),
// higher 16 bits = generation/ID. The full handle is stored at slot+0x2C for validation.
// Global gHandleTableBase (DAT_012234bc) points to the start of the slot array (with 0x10-byte header).

struct HandleSlot {
    uint8_t unknown_0x00[0x10];          // +0x00: padding or header data
    void* objectPointer;                 // +0x10: pointer to the target object
    uint8_t unknown_0x14[0x18];          // +0x14: other fields (total size 0x30)
    uint32_t storedHandle;               // +0x2C: full handle for validation
};

extern HandleSlot* gHandleTableBase;      // DAT_012234bc - points to array start

// Returns 1 if successful, 0 otherwise.
uint8_t HandleManager::setValueByHandle(uint32_t handle, uint32_t value) {
    uint8_t success = 0;
    uint16_t index = handle & 0xFFFF;
    
    if (index < 512) {
        HandleSlot* slot = (HandleSlot*)((uint8_t*)gHandleTableBase + 0x10 + index * sizeof(HandleSlot));
        // Validate: slot exists, stored handle matches, and object pointer is non-null
        if (slot != nullptr && slot->storedHandle == handle && slot != nullptr && slot->objectPointer != nullptr) {
            // Write value to offset 0x5C of the target object
            *(uint32_t*)((uint8_t*)slot->objectPointer + 0x5C) = value;
            success = 1;
        }
    }
    return success;
}