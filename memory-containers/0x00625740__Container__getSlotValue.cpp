// FUNC_NAME: Container::getSlotValue
uint32_t __fastcall Container::getSlotValue(int index) {
    // this passed in ECX (in_EAX in decompilation)
    uint32_t* slotPtr;
    
    // +0x08: pointer to end of array (sentinel)
    // +0x0C: pointer to base of 8-byte element array
    if (index < 1) {
        // For index 0 or negative, use a separate allocation function
        slotPtr = (uint32_t*)FUN_00625430();  // Gets default/null slot
    } else {
        // Compute address: base + (index-1)*8
        slotPtr = (uint32_t*)(*(int*)((int)this + 0x0C) + (index - 1) * 8);
        // Bounds check: must be before the end pointer
        if (*(uint32_t**)((int)this + 0x08) <= slotPtr) {
            return 0xFFFFFFFF;
        }
    }
    
    if (slotPtr == nullptr) {
        return 0xFFFFFFFF;
    }
    
    return *slotPtr;  // Return first 4 bytes of the 8-byte slot
}