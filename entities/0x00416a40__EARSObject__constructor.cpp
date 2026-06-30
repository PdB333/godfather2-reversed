// FUNC_NAME: EARSObject::constructor

// Constructor for EARS engine base object.
// Calls base initializer, then optionally allocates memory via vtable-based allocator.
// Size 0x70 = 112 bytes (object size)
EARSObject* __thiscall EARSObject::constructor(byte allocFlag) {
    // Base class or common initialization (calls FUN_00416bf0)
    this->baseInitialize();

    // If low bit set, allocate memory for this object
    if ((allocFlag & 1) != 0) {
        // Get allocator vtable pointer from global (FUN_009c8f80)
        int* allocVtable = (int*)getAllocatorVtable();
        // Call vtable function at offset +4 (index 1) : allocator(this, size)
        void (*allocFunc)(EARSObject*, int) = (void (*)(EARSObject*, int))(*allocVtable + 4);
        allocFunc(this, 0x70);
    }

    return this;
}