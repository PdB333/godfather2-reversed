// FUNC_NAME: ResourceManager::createResourceInternal
// Function address: 0x00597d70
// Role: Creates a resource entry and returns a handle (always 8). Appears to be a stub or fixed allocation.

int __cdecl ResourceManager::createResourceInternal() // Assuming __cdecl; could be __thiscall with 'this' in EAX
{
    // Stack variables for resource configuration
    int resourceType = 2;                   // +0x00: Type identifier (2)
    int* resourceSizePtr;                   // Pointer to size variable
    int returnHandle = 8;                   // Handle to return (always 8)
    int resourceSize = 0x208;               // 520 bytes memory block size

    resourceSizePtr = &resourceSize;        // Point to the size

    // Call virtual function at offset 0x10 on global manager object (DAT_01205590)
    // First call: probably begin allocation or get context
    (*(void (**)(void))*DAT_01205590 + 0x10)();

    // Second call: set resource type (offset +2 in some context) with value and size
    (*(void (**)(int, int*, int))*DAT_01205590 + 0x10)(((int)this) + 2, &resourceType, 2);

    // Third call: set resource size (offset +4) with pointer and size
    (*(void (**)(int, int**, int))*DAT_01205590 + 0x10)(((int)this) + 4, &resourceSizePtr, 4);

    return returnHandle; // Always returns 8
}