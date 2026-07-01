// FUNC_NAME: ObjectArray::operator=
// Reconstructed assignment operator for a dynamic array of 32-byte objects with vtable.
// The array is stored as: pointer to buffer, count, capacity (each 4 bytes).
// Each element is a polymorphic object (0x20 bytes) with a vtable at offset 0.

int* __thiscall ObjectArray::operator=(int* thisPtr, int* otherPtr)
{
    if (thisPtr == otherPtr)
        return thisPtr;

    // Destroy existing elements in reverse order (each element is 0x20 bytes)
    int count = thisPtr[1] - 1;  // index of last element
    if (count >= 0)
    {
        int offset = count * 0x20;
        do
        {
            // Call destructor via vtable (first entry)
            Element* element = reinterpret_cast<Element*>(thisPtr[0] + offset);
            element->~Element();   // (*(void (**)(void))(*(int*)element))(0)
            count--;
            offset -= 0x20;
        } while (count >= 0);
    }

    // If current capacity is less than source's count, reallocate buffer
    if (static_cast<uint>(thisPtr[2]) < static_cast<uint>(otherPtr[1]))
    {
        freeMemory(reinterpret_cast<void*>(thisPtr[0])); // FUN_009c8f10
        int newCapacity = otherPtr[1];
        thisPtr[2] = newCapacity;
        if (newCapacity == 0)
        {
            thisPtr[0] = 0;
        }
        else
        {
            thisPtr[0] = reinterpret_cast<int>(allocateMemory(newCapacity * 0x20)); // FUN_009c8e80
        }
    }

    // Copy elements from source to destination
    uint srcCount = static_cast<uint>(otherPtr[1]);
    if (srcCount != 0)
    {
        int dstOffset = 0;
        uint i = 0;
        do
        {
            int* dst = reinterpret_cast<int*>(thisPtr[0] + dstOffset);
            if (dst != nullptr)
            {
                int* src = reinterpret_cast<int*>(otherPtr[0] + dstOffset);
                // Copy 0x20 bytes, but force vtable to a specific one (PTR_LAB_00e35c24)
                dst[0] = reinterpret_cast<int>(&PTR_LAB_00e35c24);  // vtable
                dst[1] = src[1];
                dst[2] = src[2];
                dst[3] = src[3];
                dst[4] = src[4];
                dst[5] = src[5];
                dst[6] = src[6];
                dst[7] = src[7];
            }
            i++;
            dstOffset += 0x20;
        } while (i < srcCount);
    }

    // Set the stored count
    thisPtr[1] = otherPtr[1];

    return thisPtr;
}