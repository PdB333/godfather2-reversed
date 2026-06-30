// FUNC_NAME: createRegisteredObject

// Allocates and registers an object with an ID into a global hash table.
// Parameters:
//   arg1 - object ID (used as key in the table)
//   arg2 - unused (possibly this pointer if called as member? judged as separate parameter)
//   arg3 - first data value (stored at offset 0x04)
//   arg4 - second data value (stored at offset 0x08)
//   arg5 - third data value (stored at offset 0x0C)
//   arg6 - fourth data value (stored at offset 0x60)
// Returns: void (object is registered; caller retains pointer via param_1 after call)

void __cdecl createRegisteredObject(
    uint objectId,
    undefined4 unusedParam,
    undefined4 data0,
    undefined4 data1,
    undefined4 data2,
    undefined4 data3
) {
    // Local array used for memory allocation tags and hash key
    // Index 0 will be overwritten with objectId before insertion
    uint hashKeyAndTags[4];
    hashKeyAndTags[1] = 2;       // memory tag (likely allocation category)
    hashKeyAndTags[2] = 0x10;    // flags (e.g., alignment)
    hashKeyAndTags[3] = 0;       // optional callback or zero

    // Allocate object of size 0x70 bytes
    // FUN_009c8ed0 is an EA EARS allocator (e.g., earMemoryAlloc)
    uint* newObj = (uint*)FUN_009c8ed0(0x70, &hashKeyAndTags[1]);

    if (newObj != nullptr) {
        // Set vtable pointer at offset 0
        newObj[0] = (uint)&PTR_FUN_00e37558;  // class vtable

        // Store data parameters at respective offsets
        newObj[1] = (uint)data0;   // +0x04
        newObj[2] = (uint)data1;   // +0x08
        newObj[3] = (uint)data2;   // +0x0C
        newObj[0x18] = (uint)data3; // +0x60 (note: index 0x18 => byte offset 0x60)
    } else {
        newObj = nullptr;
    }

    // Prepare key for hash table insertion
    hashKeyAndTags[0] = objectId;

    // Compute bucket index: objectId % (globalTable->bucketCount)
    // The global table is assumed to be a structure at DAT_01223398,
    // with bucket count at offset 8 within a second-level structure.
    // The exact access pattern: *(int*)(*(int*)(DAT_01223398+8)+8)
    uint bucketIndex = objectId % *(uint*)(*(int*)(DAT_01223398 + 8) + 8);

    // Insert the newly created object into the hash table
    // FUN_00423cf0 signature: void(HashKeyArray* key, void** objPtr, uint bucketIndex)
    // The object pointer is passed indirectly via &newObj after reassigning param_1
    void* objPtr = newObj;
    FUN_00423cf0(hashKeyAndTags, &objPtr, bucketIndex);
}