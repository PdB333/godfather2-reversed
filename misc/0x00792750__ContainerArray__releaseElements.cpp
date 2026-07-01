// FUNC_NAME: ContainerArray::releaseElements
void __thiscall ContainerArray::releaseElements(int* thisPtr)
{
    int count = thisPtr[1] - 1;                 // +0x04: element count minus one for reverse iteration
    if (count >= 0)
    {
        int byteOffset = count * 0x10;           // each element is 0x10 bytes
        do
        {
            int* elementPtr = *(int**)(byteOffset + 4 + thisPtr[0]); // +0x00: base array pointer; +0x04: inner pointer of element
            if (elementPtr != (int*)0)
            {
                FUN_009c8f10(elementPtr);        // deallocate the inner pointer (likely operator delete)
            }
            count--;
            byteOffset -= 0x10;
        } while (count >= 0);
    }
    if (thisPtr[0] != 0)
    {
        FUN_009c8f10(thisPtr[0]);               // deallocate the array itself
    }
    return;
}