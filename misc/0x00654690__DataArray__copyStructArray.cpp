// FUNC_NAME: DataArray::copyStructArray
void __thiscall DataArray::copyStructArray(int elementCount, void* sourceBuffer)
{
    if (elementCount != 0)
    {
        int srcOffset = 0;
        do
        {
            // Destination pointer from array stored at this+0x8 (pointer to contiguous 20-byte elements)
            char* destElement = *(char**)(this + 8) + srcOffset;
            if (destElement != nullptr)
            {
                // Copy 20 bytes: two 8-byte chunks + one 4-byte chunk (little-endian)
                *(unsigned long long*)destElement = *(unsigned long long*)((char*)sourceBuffer + srcOffset);
                *(unsigned long long*)(destElement + 8) = *(unsigned long long*)((char*)sourceBuffer + srcOffset + 8);
                *(unsigned int*)(destElement + 16) = *(unsigned int*)((char*)sourceBuffer + srcOffset + 16);
            }
            srcOffset += 20;
            elementCount--;
        } while (elementCount != 0);
    }
}