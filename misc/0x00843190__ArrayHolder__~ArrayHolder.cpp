// FUNC_NAME: ArrayHolder::~ArrayHolder

void __fastcall ArrayHolder::~ArrayHolder(int *thisPtr)
{
    int count = thisPtr[1]; // +0x04: number of elements in the array
    int *arrayBase = (int *)thisPtr[0]; // +0x00: pointer to dynamically allocated array of 8-byte elements

    // Destroy each element in reverse order
    while (--count >= 0)
    {
        int *element = &arrayBase[count * 2]; // each element is 8 bytes (2 ints)
        if (element[0] != 0) // check if the element's first field is non-null
        {
            FUN_004daf90(element); // destructor for the element
        }
    }

    // Free the array memory
    if (arrayBase != 0)
    {
        FUN_009c8f10(arrayBase); // operator delete or free
    }
}