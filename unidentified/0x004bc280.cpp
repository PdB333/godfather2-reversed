// FUN_004bc280: destroyTriplePointerArray
// This function frees an array of structs (each 0x34 bytes) that contain three pointers (at offsets 0x0c, 0x18, 0x24),
// then frees the array itself. param_1 = pointer to container: [ptr to array, count].
// The loop iterates from count-1 down to 0, freeing each element's three pointers, then frees the array base.

void __fastcall destroyTriplePointerArray(int* container)
{
    // container[0] = pointer to array of elements (each element = 0x34 bytes)
    // container[1] = number of elements in the array
    int elementCount = container[1] - 1;
    if (elementCount >= 0)
    {
        int elementOffset = elementCount * 0x34;
        do
        {
            // Base of current element (at *container + current offset)
            int elementBase = *container + elementOffset;

            // Free pointers at offsets 0x24, 0x18, and 0x0c from element start
            int* ptr24 = *(int**)(*container + 0x24 + elementOffset);
            if (ptr24 != 0)
            {
                FUN_009c8f10(ptr24);  // Deallocate pointer
            }

            int* ptr18 = *(int**)(elementBase + 0x18);
            if (ptr18 != 0)
            {
                FUN_009c8f10(ptr18);
            }

            int* ptr0c = *(int**)(elementBase + 0x0c);
            if (ptr0c != 0)
            {
                FUN_009c8f10(ptr0c);
            }

            elementCount--;
            elementOffset -= 0x34;
        } while (elementCount >= 0);
    }

    // Free the array itself
    if (*container != 0)
    {
        FUN_009c8f10(*container);
    }
}