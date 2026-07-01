// FUNC_NAME: cleanupObjectArray
void __fastcall cleanupObjectArray(int *container)
{
    int count = container[1] - 1;
    if (count >= 0)
    {
        int offset = count * 0x14;
        do
        {
            int *objectPtr = *(int **)(container[0] + offset);
            if (objectPtr != 0)
            {
                // Call the destructor/release function at offset 0xC in the element structure
                void (*destructor)(int *) = *(void (**)(int *))(container[0] + offset + 0xC);
                destructor(objectPtr);
            }
            count--;
            offset -= 0x14;
        } while (count >= 0);
    }
    if (container[0] != 0)
    {
        // Free the array memory
        FUN_009c8f10(container[0]);
    }
}