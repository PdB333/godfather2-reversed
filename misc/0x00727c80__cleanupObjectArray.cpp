// FUNC_NAME: cleanupObjectArray
// Function at 0x00727c80 - Destructor for a container holding an array of 8-byte elements. Iterates backwards, calls element destructor if first field non-zero, then frees the array.

struct EightByteElement
{
    int field0; // offset 0: likely a pointer or flag
    int field4; // offset 4: unknown
};

void __fastcall cleanupObjectArray(int *thisPtr)
{
    int count = thisPtr[1]; // +0x04: number of elements
    EightByteElement *pElements = (EightByteElement *)thisPtr[0]; // +0x00: pointer to array

    for (int i = count - 1; i >= 0; i--)
    {
        if (pElements[i].field0 != 0)
        {
            // FUN_004daf90 - destructor/cleanup for a single element
            cleanupElement(&pElements[i]);
        }
    }

    if (pElements != 0)
    {
        // FUN_009c8f10 - free the array memory (likely operator delete[])
        freeArrayMemory(pElements);
    }
}