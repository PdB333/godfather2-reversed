// FUNC_NAME: ObjectDatabase::getObjectHandle
// Function address: 0x004c3df0
// This function performs a two-level lookup: first it uses a short index (this+0x74) to index into a type table
// (pointed by this+0x70->+0x1c) to get a base pointer for a secondary table. Then it calls FUN_005828a0 with the
// given key and that base pointer to obtain an index, and finally reads a handle from the secondary table at offset
// base + 0x10 + index * 0x14. Returns -1 on failure.

int __thiscall ObjectDatabase::getObjectHandle(int this, int key)
{
    int typeDataPtr;
    int lookupIndex;
    int objectHandle;

    if (this == 0 || *(int *)(this + 0x70) == 0) {
        return -1;
    }

    // +0x70: pointer to a structure containing type table information
    // +0x1c of that structure: pointer to the array of type entries (each 0x18 bytes)
    // +0x74: short index into the type array
    typeDataPtr = *(int *)(*(int *)(this + 0x70) + 0x1c + *(short *)(this + 0x74) * 0x18 + 0x14);

    // Use the type data pointer as a base for the secondary lookup
    lookupIndex = FUN_005828a0(key, typeDataPtr);
    if (lookupIndex == -1) {
        return -1;
    }

    // Secondary table: each entry is 0x14 bytes, handle at offset 0x10
    objectHandle = *(int *)(typeDataPtr + 0x10 + lookupIndex * 0x14);
    if (objectHandle == -1) {
        return -1;
    }

    return objectHandle;
}