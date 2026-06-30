// FUNC_NAME: ObjectManager::getObjectByIndex
// Reconstructed from 0x00704130
// Retrieves a pointer to an object from an internal table given an index.
// The table stores pointer-sized entries (8 bytes each). 
// If the entry is non-null, it returns the entry pointer minus 0x48 (base offset).

// Expected 'this' layout:
// +0x0: pointer to an array of object entry structures (each 8 bytes).
// The entry at 'index' is dereferenced as an int* to get a pointer that points
// to a field 0x48 bytes into the actual object. Subtracting 0x48 recovers the base pointer.

int __thiscall ObjectManager::getObjectByIndex(int* thisPtr, int index)
{
    // Get the base table pointer (thisPtr->table)
    int* tablePtr = (int*)(*thisPtr);
    
    // Read the object pointer from the table at offset index * 8
    int objectPtr = tablePtr[index * 8 / 4];   // equivalent to *(int*)(tablePtr + index * 8)
    
    if (objectPtr != 0)
    {
        // Convert from internal pointer to actual object base
        return objectPtr - 0x48;
    }
    
    return 0;
}