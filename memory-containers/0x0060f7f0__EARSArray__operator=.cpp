// FUNC_NAME: EARSArray::operator=

int* EARSArray::operator=(int* other)
{
    int* originalThis = this;
    if (this != other)
    {
        // Destroy existing elements by calling destructor for each element
        int elementCount = this[1];
        for (int count = elementCount; count > 0; count--)
        {
            destroyElement(); // likely takes element address; decompiler omitted argument
        }

        // If capacity is insufficient, reallocate
        if ((uint)this[2] < (uint)other[1])
        {
            operatorDeleteArray((void*)*this); // free old data
            int newCapacity = other[1];
            this[2] = newCapacity;
            *this = (newCapacity == 0) ? 0 : (int)operatorNewArray(newCapacity * 0x14c);
        }

        // Copy elements from other to this
        int index = 0;
        if (other[1] != 0)
        {
            do
            {
                int* destElement = (int*)(*originalThis + index);
                if (destElement != (int*)0x0)
                {
                    int* srcBase = (int*)(*other + index);

                    // Copy first 4 ints (offsets 0,4,8,12) and a byte at offset 12? Actually 4 ints = 16 bytes
                    *destElement = *srcBase;
                    destElement[1] = srcBase[1];
                    destElement[2] = srcBase[2];
                    *(char*)(destElement + 3) = *(char*)(srcBase + 3); // byte at offset 12, likely part of an int

                    // Copy the bulk data: 0x4c dwords from offset 0x10
                    int* srcWord = (int*)((int)srcBase + 0x10);
                    int* destWord = destElement + 4; // offset 0x10
                    for (int wordCount = 0x4c; wordCount != 0; wordCount--)
                    {
                        *destWord = *srcWord;
                        srcWord++;
                        destWord++;
                    }

                    // Post-copy processing on the source element (e.g., reference counting or hook)
                    elementCopyPostProcess((int)srcBase + 0x140);
                }
                index += 0x14c;
            } while (index / 0x14c < (uint)other[1]); // loop condition based on element count
        }

        // Update element count
        originalThis[1] = other[1];
    }
    return originalThis;
}