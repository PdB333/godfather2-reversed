// FUNC_NAME: BaseObject::releaseSubComponents
// Address: 0x009823b0
// This function iterates over an array of 8 sub-objects (each 0x10 bytes) starting at this+0x4c, calling a destructor-like function pointer for each non-null pointer.
// Then it handles two additional sub-objects at offsets 0x2c and 0x3c.
// The array of 8 items is likely for components like child objects or slots.
void __thiscall BaseObject::releaseSubComponents() {
    // Array of 8 items, each 16 bytes, starting at this+0x4c.
    // Each item: [0x00] pointer to object, [0x0C] function pointer to cleanup routine.
    // Index 0 at this+0x4c, index 7 at this+0xbc.
    int currentItemOffset = 0xcc; // End marker? Actually point one past last item.
    int itemIndex = 7; // Loop from last index (7) down to 0.

    do {
        // Calculate base of current item (pointed to by iVar2 - 0x10)
        int itemBase = currentItemOffset - 0x10; // this + (0xcc - 0x10) = this+0xbc initially, then decreasing.
        int* objectPtr = (int*)((char*)this + itemBase);
        if (*objectPtr != 0) {
            // Retrieve cleanup function pointer at itemBase + 0xc (offset within item)
            typedef void (__thiscall* CleanupFunc)(void*);
            CleanupFunc cleanup = *(CleanupFunc*)((char*)this + itemBase + 0xc);
            // Call cleanup on the object
            cleanup((void*)*objectPtr);
        }
        currentItemOffset -= 0x10; // Move to previous item
        itemIndex--;
    } while (itemIndex >= 0);

    // Handle sub-object at offset 0x3c with cleanup function at offset 0x48
    int* obj1 = (int*)((char*)this + 0x3c);
    if (*obj1 != 0) {
        typedef void (__thiscall* CleanupFunc)(void*);
        CleanupFunc cleanup = *(CleanupFunc*)((char*)this + 0x48);
        cleanup((void*)*obj1);
    }

    // Handle sub-object at offset 0x2c with cleanup function at offset 0x38
    int* obj2 = (int*)((char*)this + 0x2c);
    if (*obj2 != 0) {
        typedef void (__thiscall* CleanupFunc)(void*);
        CleanupFunc cleanup = *(CleanupFunc*)((char*)this + 0x38);
        cleanup((void*)*obj2);
    }
}