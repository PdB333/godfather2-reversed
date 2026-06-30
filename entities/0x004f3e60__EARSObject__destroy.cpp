// FUNC_NAME: EARSObject::destroy
// Address: 0x004f3e60
// Destructor: returns sub-object at offset +0x10 to a free-list pool, optionally deallocates itself.
// The memory manager (global) uses a linear bump allocator with sentinel markers.
// Pool slot layout: [4 bytes sentinel] [4 bytes pointer to returned object] [next slot...]

extern uint32_t* g_poolAllocator; // +0x14 holds the current free head pointer inside the pool buffer
extern void*   g_poolSentinel;    // &PTR_LAB_01123be8 – unique marker for free slots
extern void    deallocateObject(void* ptr); // FUN_009c8eb0 – frees the given block

uint32_t* __thiscall EARSObject::destroy(uint32_t* thisObj, uint8_t flags) {
    // Set vtable back to base (prevent double destruction)
    thisObj[0] = (uint32_t)&PTR_FUN_00e37110;

    // Recover embedded sub-object pointer at offset +0x10
    uint32_t* subPtr = (uint32_t*)thisObj[4];
    if (subPtr != nullptr) {
        // Get pointer to the current free head (a slot in the pool)
        uint32_t** freeHeadPtr = (uint32_t**)((uint8_t*)g_poolAllocator + 0x14);
        uint32_t* currentSlot = *freeHeadPtr;

        // Mark this slot as free by writing the sentinel value
        *(uint32_t*)currentSlot = (uint32_t)g_poolSentinel;

        // Advance to the data area of the slot and store the returned pointer
        uint32_t* dataArea = currentSlot + 1; // next 4 bytes
        *dataArea = (uint32_t)subPtr;

        // Update free head to the next slot
        *freeHeadPtr = dataArea + 1;

        // Clear the sub-object references
        thisObj[4] = 0;
        thisObj[5] = 0;
    }

    // If flag bit 0 is set, deallocate the entire object
    if ((flags & 1) != 0) {
        deallocateObject(thisObj);
    }

    return thisObj;
}