// FUNC_NAME: EARSHandle::getPointer
// Address: 0x004dec00
// Role: Returns pointer to the underlying object if the handle is non-null; otherwise returns 0.
// The handle is represented as a struct of 4 ints; if any of them is non-zero, the handle is considered valid.

// Reconstructed from decompiled x86 assembly (Ghidra)
// Calling convention: __thiscall (implicit this in ECX, but decompiled shows in_EAX as this)

unsigned int __thiscall EARSHandle::getPointer(void)
{
    // The four ints that represent the handle (this) - offset 0x00, 0x04, 0x08, 0x0C
    int* handleData = reinterpret_cast<int*>(this);
    
    // Check if the handle is null: all four ints must be zero
    if ((handleData[0] != 0 || handleData[1] != 0) || 
        (handleData[2] != 0 || handleData[3] != 0))
    {
        // Call internal function to retrieve the actual object pointer
        unsigned int* objectPtr = reinterpret_cast<unsigned int*>(FUN_004e0f60());
        if (objectPtr != nullptr)
        {
            // Return the first 32-bit value from the returned object
            return *objectPtr;
        }
    }
    return 0;
}