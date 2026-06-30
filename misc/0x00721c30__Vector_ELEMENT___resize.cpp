// FUNC_NAME: Vector<ELEMENT>::resize
void __thiscall Vector_ELEMENT_resize(uint *this, uint newSize, char destroyExisting)
{
    uint *oldBuffer;
    uint *newBuffer;
    uint allocatedSize;
    int elementIndex;
    int oldCount;
    int freeIndex;

    if ((int)*this < (int)newSize)
    {
        // Calculate total allocation size: newSize * elementSize (0x24) + 4 (header for count)
        allocatedSize = newSize * 0x24;
        // Check for overflow (though not strictly necessary here)
        if ((int)((ulonglong)newSize * 0x24 >> 0x20) != 0)
            allocatedSize = -(uint)((int)((ulonglong)newSize * 0x24 >> 0x20) != 0);
        else
            allocatedSize = (uint)((ulonglong)newSize * 0x24);
        // Allocate with custom allocator (likely malloc with 4-byte header)
        newBuffer = (uint *)FUN_009c8e80(allocatedSize + 4);
        if (newBuffer != (uint *)0x0)
        {
            // Store capacity in first word, data pointer starts at newBuffer+1
            *newBuffer = newSize;
            // Construct default elements using vector_constructor_iterator
            _vector_constructor_iterator_(newBuffer + 1, 0x24, newSize, (void (*)(void *))&LAB_00721a70);
        }

        // Clean up old buffer if it exists
        oldBuffer = (uint *)this[3];
        if (oldBuffer != (uint *)0x0)
        {
            // If destroyExisting is true, call element destructor on each old element
            if (destroyExisting != '\0')
            {
                for (elementIndex = 0; elementIndex < (int)*this; elementIndex++)
                {
                    FUN_00721b60((uint)((int)oldBuffer + elementIndex * 0x24));
                }
            }
            // Always call additional cleanup (likely freeing internal pointers)
            allocatedSize = (uint)oldBuffer;
            if (allocatedSize != 0)
            {
                freeIndex = *(int *)(allocatedSize - 4); // Element count from header
                // Iterate backwards over the buffer
                for (int i = freeIndex; i >= 0; i--)
                {
                    uint *element = (uint *)(allocatedSize + (i * 0x24));
                    if (*element != 0)
                    {
                        FUN_004daf90((int)element);
                    }
                }
                // Free the old buffer (including header)
                FUN_009c8f10(allocatedSize - 4);
            }
        }

        // Update pointer and size
        this[3] = (uint)newBuffer;
        *this = newSize;
    }
}