// FUNC_NAME: UnknownClass::destroyPointerArray
// Function at 0x006f8010 - Destructor/cleanup for a container that holds an array of 0xC-byte objects.
// The class has two fields: a pointer to the array (offset +0x00) and a count (offset +0x04).
void __fastcall UnknownClass::destroyPointerArray(void *thisPtr)
{
    int *this = (int *)thisPtr;
    int count = this[1];          // +0x04: number of elements
    int idx = count - 1;

    if (idx >= 0)
    {
        int step = idx * 0xC;     // 12 bytes per element
        int *base = (int *)this[0]; // +0x00: pointer to array of 12-byte structs

        do
        {
            int *element = (int *)((char *)base + step);
            // First 4 bytes of each element is a pointer; if non‑null, destroy the referenced object
            if (*element != 0)
            {
                // FUN_004daf90 – likely destructor for the inner object
                ((void (__fastcall *)(int *))0x004daf90)(element);
            }
            idx--;
            step -= 0xC;
        } while (idx >= 0);
    }

    if (this[0] != 0)
    {
        // FUN_009c8f10 – likely operator delete[] or custom memory deallocator
        ((void (__fastcall *)(int *))0x009c8f10)((int *)this[0]);
    }
}