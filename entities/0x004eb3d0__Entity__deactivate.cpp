// FUNC_NAME: Entity::deactivate
// Address: 0x004eb3d0
// This function retrieves a static vtable pointer and calls the second virtual function
// (vtable offset 0x04) with a boolean argument of false (0). This is commonly used to
// deactivate or disable an object in the EA EARS engine.
void __thiscall Entity::deactivate() {
    // Get static vtable pointer for this class (returns address of vtable array)
    int* vtablePtr = (int*)FUN_009c8f80();  // static vtable getter

    // vtablePtr[0] = first virtual function
    // vtablePtr[1] = second virtual function (offset 4 bytes)
    void(__thiscall * deactivateFunc)(Entity*, int) = (void(__thiscall*)(Entity*, int))vtablePtr[1];
    // Call the virtual function with 'this' and a false flag
    deactivateFunc(this, 0);
}