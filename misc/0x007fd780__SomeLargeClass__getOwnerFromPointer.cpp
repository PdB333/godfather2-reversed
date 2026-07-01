// FUNC_NAME: SomeLargeClass::getOwnerFromPointer
// Function at 0x007fd780: Retrieves the containing object from a pointer to a sub-object at offset 0x48.
// The field at this+0xff0 stores a pointer to a sub-object (e.g., a component or node) that is embedded
// at offset 0x48 within the target object. Returns the target object's base address, or 0 if the pointer is null.
int __fastcall SomeLargeClass::getOwnerFromPointer(int this) {
    // Check if the stored pointer at offset 0xff0 is non-null
    if (*(int*)(this + 0xff0) != 0) {
        // Subtract 0x48 to get the base of the containing object (container_of pattern)
        return *(int*)(this + 0xff0) - 0x48;
    }
    return 0;
}