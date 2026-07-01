// FUNC_NAME: ResourceManager::acquireResource
// Function address: 0x00868a60
// Role: Try to find an existing resource by key pairs; if found, increment refcount at +0x18.
// Otherwise, release two resource references (via FUN_005f5c60), create a new resource using a builder pattern,
// then destroy any leftover builder pointers.

void ResourceManager::acquireResource(ResourceKey key1, ResourceKey key2, ResourceKey key3, ResourceKey key4, void* extraData)
{
    int foundObjectPtr = 0;
    char found = FUN_00867690(key1, key2, key3, key4, extraData, &foundObjectPtr);
    if (found) {
        // Increment reference count at offset +0x18 of the found object
        *(int*)(foundObjectPtr + 0x18) += 1;
        return;
    }

    // Builder structure: [ptr0, ptr1, ptr2, ptr3, ptr4, ptr5, useFlag]
    int builder[7] = {0};

    // Release reference counts for the two key pairs (likely decrement usage counts)
    FUN_005f5c60(key1, key2);
    FUN_005f5c60(key3, key4);

    // Set the "use" flag to 1
    builder[6] = 1;

    // Construct a new resource using the builder
    FUN_00867800(builder);

    // Destroy any non-null pointers that were produced by construction
    if (builder[3] != 0) {
        FUN_004daf90(&builder[3]); // Release pointer at offset 12 bytes
    }
    if (builder[0] != 0) {
        FUN_004daf90(&builder[0]); // Release pointer at start
    }
    return;
}