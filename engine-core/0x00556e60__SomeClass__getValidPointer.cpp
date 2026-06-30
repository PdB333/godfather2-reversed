// FUNC_NAME: SomeClass::getValidPointer
// Function address: 0x00556e60
// Role: Returns the pointer at this+0x40 only if it is non-zero and the associated name string is non-empty.
//       The global at DAT_0113dfc8 appears to be a singleton manager used to retrieve a string identifier for the object.

// Note: unaff_EDI (this) is the implicit this pointer (__thiscall convention).
// The approach uses a global singleton's vtable to convert an object handle to a name string.

int* __thiscall SomeClass::getValidPointer(void)
{
    int* objectPtr = *(int**)(this + 0x40);   // +0x40: pointer to some object/resource

    if (objectPtr != nullptr) {
        // Get global manager instance via vtable call at offset 0x14
        int* globalManager = (int*)(**(code**)(*DAT_0113dfc8 + 0x14))();

        // Call virtual method at offset 0x10 on globalManager to get a name ID for the object
        int nameId = (**(code**)(*globalManager + 0x10))(objectPtr);

        // Convert nameId to a string into local buffer (stack variable)
        char buffer[256]; // approximate size
        char* nameStr = (char*)FUN_00ab06f0(&buffer, nameId);

        // If the name is empty (first character null), return null
        if (*nameStr == '\0') {
            return nullptr;
        }
    }

    // Return the pointer regardless (only returns null if objectPtr was null or name empty)
    return *(int**)(this + 0x40);
}