// FUNC_NAME: SomeEARSObject::constructorWithAllocation
// Address: 0x006d71e0
// Role: Constructor for a game object. Calls base class constructor, then optionally allocates internal memory of size 0x270 (624 bytes) using a global allocator if flag bit 0 is set.

int __thiscall SomeEARSObject::constructorWithAllocation(byte param_2) {
    // Call base class constructor (likely from EARS hierarchy)
    baseConstructor();

    // If the low bit of the flag is set, perform allocation via a global allocator
    if ((param_2 & 1) != 0) {
        // Get pointer to global memory allocator's vtable
        int *allocatorVtable = (int *)getGlobalAllocator();
        // Call virtual function at offset 4 (likely allocate or initialize)
        // The function takes this pointer and the allocation size (0x270)
        (**(code **)(*allocatorVtable + 4))(this, 0x270);
    }

    return this;
}