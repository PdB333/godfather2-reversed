// FUNC_NAME: GhostObject::pack
// Address: 0x008bfb90
// Role: Serializes the ghost object into a buffer, returning total bytes written.
// The object has an array of sub-objects (size 0x50 each) at some offset, and variable-length data for each.
// Offset 0x1a8: count of sub-objects (uint)
// Sub-object size: 0x50 bytes
// Variable data overhead per sub-object: 0x14 * 4 = 80 bytes? Actually 0x14 is 20, multiplied by 4 gives 80 bytes fixed overhead per sub-object in the serialized buffer.
// The buffer layout: first count * 0x50 bytes of fixed sub-objects, then variable-length data for each sub-object sequentially.

int __thiscall GhostObject::pack(void* this, void* buffer)
{
    uint subObjectCount = *(uint*)((char*)this + 0x1a8);  // Number of sub-objects
    uint i;
    uint variableDataSize = 0;
    uint fixedDataSize = 0;
    int subObjectVariableSize;

    // First pass: compute total variable data size needed
    for (i = 0; i < subObjectCount; i++)
    {
        subObjectVariableSize = FUN_008c8390();  // Returns size of variable data for current sub-object (in 4-byte words? or bytes?)
        variableDataSize += subObjectVariableSize;
    }

    // Second pass: serialize fixed sub-objects and variable data
    char* fixedPtr = (char*)buffer;  // Pointer to fixed sub-object array
    char* variablePtr = (char*)buffer + subObjectCount * 0x50;  // Variable data starts after fixed array
    for (i = 0; i < subObjectCount; i++)
    {
        FUN_008c8b50(fixedPtr);  // Serialize fixed sub-object (size 0x50) into buffer at fixedPtr
        int variableSize = FUN_008c8930(variablePtr);  // Serialize variable data and return size written (in bytes? or words?)
        fixedPtr += 0x50;  // Advance fixed pointer to next sub-object
        variablePtr += variableSize;  // Advance variable pointer by the size written
    }

    // Total bytes written = (variableDataSize + subObjectCount * 0x14) * 4
    // variableDataSize is sum of sizes from FUN_008c8390 (assumed in 4-byte units)
    // subObjectCount * 0x14 is fixed overhead per sub-object (20 * 4 = 80 bytes)
    return (variableDataSize + subObjectCount * 0x14) * 4;
}