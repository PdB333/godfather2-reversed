// FUNC_NAME: ValidateObjectHandle
// Function at 0x005e6700 validates an object handle and performs an action if valid.
// Uses global object table at DAT_012234bc (s_pObjectTable), each entry 0x30 bytes, ID at +0x2c.

// Structure for an entry in the object table (size 0x30)
struct ObjectTableEntry {
    // +0x00: unknown
    // ...
    // +0x2c: full handle (uint32)
    uint32_t handle;
    // remaining up to 0x30
};

// Static global pointer to object table (base +0x10 is start of array)
static ObjectTableEntry* s_pObjectTableBase = (ObjectTableEntry*)0x012234bc;

// External function called on valid object (at 0x005e5fe0)
extern uint32_t ProcessObjectAction(uint32_t actionData);

// This function is __cdecl (no this pointer)
uint32_t ValidateObjectHandle(uint32_t handle, uint32_t actionData) {
    uint32_t result;
    // Preserve high 24 bits of EAX (likely an error mask or previous state)
    uint32_t highBits = EAX & 0xFFFFFF00;
    
    // Extract index from low 16 bits of handle
    uint16_t index = (uint16_t)(handle & 0xFFFF);
    
    // Check index is within valid range (maximum 512 entries)
    if (index < 0x200) {
        // Calculate pointer to entry: table base + offset 0x10 + index * 0x30
        ObjectTableEntry* entry = (ObjectTableEntry*)((uint32_t)s_pObjectTableBase + 0x10 + index * 0x30);
        
        // Verify entry is non-null and its stored handle matches the given handle
        if (entry != nullptr && entry->handle == handle) {
            // Valid handle – perform the action
            result = ProcessObjectAction(actionData);
            return result;
        }
    }
    
    // Invalid handle – return the preserved high bits of EAX (original value)
    return highBits;
}