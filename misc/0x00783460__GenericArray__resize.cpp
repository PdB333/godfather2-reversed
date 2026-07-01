// FUNC_NAME: GenericArray::resize
// Address: 0x00783460
// Resizes the internal array to newSize. Initializes new elements to zero.
// Destroys elements beyond the new size if shrinking.

void __thiscall GenericArray::resize(uint newSize)
{
    uint currentSize = this->mSize;

    if (currentSize < newSize)
    {
        // Grow the array: reallocate to new size
        this->reallocate(newSize);
        currentSize = this->mSize;

        // Initialize newly added elements to zero (each element is 8 bytes)
        while (currentSize < newSize)
        {
            void* element = this->mElements + currentSize * 8;
            if (element != nullptr)
            {
                *(uint32_t*)element = 0;
                *(uint32_t*)((char*)element + 4) = 0;
            }
            currentSize++;
        }
        this->mSize = newSize;
    }
    else if (currentSize > newSize)
    {
        // Shrink: destroy elements beyond newSize
        while (currentSize > newSize)
        {
            currentSize--;
            void* element = this->mElements + currentSize * 8;
            if (*(uint32_t*)element != 0)  // pointer check, assumes vtable or some sentinel?
            {
                this->destroyElement(element);
            }
        }
        this->mSize = newSize;
    }
    // else equal, do nothing
}