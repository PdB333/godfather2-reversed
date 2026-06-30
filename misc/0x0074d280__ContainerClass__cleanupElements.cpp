// FUNC_NAME: ContainerClass::cleanupElements
// Address: 0x0074d280
// Role: Destroys an array of 8-byte elements, then frees the array memory.
// The struct layout: [0x00] pointer to array of elements (each element 8 bytes),
//                   [0x04] count of elements.

void __fastcall ContainerClass::cleanupElements(int* thisPtr)
{
    // +0x00: pointer to element array
    int* elementArray = (int*)thisPtr[0];
    // +0x04: number of elements
    int count = thisPtr[1];

    // Walk backward through the array (original code does iVar1-1 while iVar1 >= 0)
    for (int i = count - 1; i >= 0; i--)
    {
        // Each element occupies 8 bytes (2 ints)
        int* element = elementArray + i * 2;
        // Check first field of element; if non‑null, release the element
        if (element[0] != 0)
        {
            // Calls destructor / cleanup function for the element
            FUN_004daf90(element);
        }
    }

    // Free the underlying array memory
    if (elementArray != 0)
    {
        FUN_009c8f10(elementArray);
    }
}