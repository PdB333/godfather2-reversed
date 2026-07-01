// FUNC_NAME: DynamicArray::ensureCapacity
void __thiscall DynamicArray::ensureCapacity(int param_2)
{
    int *thisPtr = reinterpret_cast<int*>(this);
    uint currentCapacity = thisPtr[2]; // +0x08: capacity
    if (currentCapacity < (uint)param_2)
    {
        // Allocate new buffer (each element is 4 bytes)
        undefined4 *newBuffer = (undefined4 *)FUN_009c8e80(param_2 * 4);
        uint count = thisPtr[1]; // +0x04: number of elements
        if (thisPtr[0] != 0)    // +0x00: existing buffer pointer
        {
            // Copy existing elements
            for (uint i = 0; i < count; i++)
            {
                newBuffer[i] = *(undefined4 *)(thisPtr[0] + i * 4);
            }
        }
        // Free old buffer if it exists
        FUN_009c8f10((void *)thisPtr[0]);
        // Update buffer and capacity
        thisPtr[0] = (int)newBuffer;
        thisPtr[2] = param_2;
    }
}