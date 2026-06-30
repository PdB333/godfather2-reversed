// FUNC_NAME: SomeClass::scalarDeletingDestructor
// Function address: 0x00728d80
// MSVC compiler-generated scalar deleting destructor.
// Destroys the subobject at offset +0x04 if non-null, then optionally deallocates memory.

int __thiscall SomeClass::scalarDeletingDestructor(int thisPtr, unsigned char flag)
{
    // Destroy the subobject at +0x04 (e.g., a string, container, or another object)
    if (*(int *)(thisPtr + 4) != 0) {
        destroySubObject(thisPtr + 4);      // FUN_004daf90 - subobject destructor
    }

    // If the low bit of flag is set, deallocate the memory of this object
    if ((flag & 1) != 0) {
        operatorDelete(thisPtr);            // FUN_009c8eb0 - operator delete
    }

    return thisPtr;
}