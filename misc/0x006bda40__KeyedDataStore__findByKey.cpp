// FUNC_NAME: KeyedDataStore::findByKey
// Function at 0x006bda40 - Finds an object in a container by matching a 4-int key.
// param_1: this pointer (likely a KeyedDataStore or similar container).
// param_2: pointer to a node structure (e.g., linked list node) that contains a pointer to a member of the target object.
// Returns pointer to the found object (iVar2) if key matches, else 0.

int __thiscall KeyedDataStore::findByKey(int thisPtr, int param_2)
{
    int foundObject = 0;
    
    // Get pointer to the object from the node structure.
    // The node at param_2 has a pointer at offset +4.
    // That pointer points to a member inside the actual object.
    // Subtracting 0x48 gives the base address of the containing object.
    int objectPtr;
    if (*(int*)(param_2 + 4) == 0) {
        objectPtr = 0;
    } else {
        objectPtr = *(int*)(param_2 + 4) - 0x48; // +0x4: pointer to inner member; -0x48: container offset
    }
    
    // Compare four 32-bit key fields from this (offsets 0x60-0x6c)
    // with the object's key fields (offsets 0x20-0x2c).
    if (objectPtr != 0 &&
        *(int*)(thisPtr + 0x60) == *(int*)(objectPtr + 0x20) &&   // +0x60: key part 0
        *(int*)(thisPtr + 0x64) == *(int*)(objectPtr + 0x24) &&   // +0x64: key part 1 (or 100 decimal)
        *(int*)(thisPtr + 0x68) == *(int*)(objectPtr + 0x28) &&   // +0x68: key part 2
        *(int*)(thisPtr + 0x6c) == *(int*)(objectPtr + 0x2c))     // +0x6c: key part 3
    {
        foundObject = objectPtr;
    }
    
    return foundObject;
}