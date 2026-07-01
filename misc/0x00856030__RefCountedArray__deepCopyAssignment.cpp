// FUNC_NAME: RefCountedArray::deepCopyAssignment
// Function at 0x00856030: Deep copy assignment operator for a container that stores elements with reference-counted pointers.
// The container stores three fields: pointer to element array (0), element count (4), and capacity (8).
// Each element is 0x2C bytes and contains a reference-counted pointer at offset 0x10.
RefCountedArray* RefCountedArray::operator=(const RefCountedArray& other)
{
    // Copy capacity and count from the source
    this->capacity = other.capacity;
    this->count = other.count;

    // If source has no capacity, set data to null and return
    if (other.capacity == 0)
    {
        this->data = nullptr;
        return this;
    }

    // Allocate memory for the element array (capacity * elementSize)
    this->data = allocate(other.capacity * 0x2C);

    // If there are elements to copy
    if (this->count > 0)
    {
        int destOffset = 0;
        unsigned int idx = 0;
        do
        {
            char* destElement = static_cast<char*>(this->data) + destOffset;
            const char* srcElement = static_cast<const char*>(other.data) + destOffset;

            if (destElement != nullptr)
            {
                // Copy first 8 bytes
                *reinterpret_cast<uint64_t*>(destElement) = *reinterpret_cast<const uint64_t*>(srcElement);

                // Copy next 4 bytes (offset 8)
                *reinterpret_cast<uint32_t*>(destElement + 8) = *reinterpret_cast<const uint32_t*>(srcElement + 8);

                // Copy two bytes at offsets 0xC and 0xD
                destElement[0xC] = srcElement[0xC];
                destElement[0xD] = srcElement[0xD];

                // Copy the reference-counted pointer at offset 0x10 and increment its refcount if non-null
                int* refPtr = *reinterpret_cast<int**>(const_cast<char*>(srcElement + 0x10));
                *reinterpret_cast<int**>(destElement + 0x10) = refPtr;
                if (refPtr != nullptr)
                {
                    // Refcount is at offset 4 of the pointed object (likely int refCount; after vtable? or just first field)
                    refPtr[1]++; // increment refcount (offset 4 from pointer)
                }

                // Copy two shorts at offsets 0x14 and 0x16
                *reinterpret_cast<uint16_t*>(destElement + 0x14) = *reinterpret_cast<const uint16_t*>(srcElement + 0x14);
                *reinterpret_cast<uint16_t*>(destElement + 0x16) = *reinterpret_cast<const uint16_t*>(srcElement + 0x16);

                // Copy bytes at offsets 0x18 and 0x19
                destElement[0x18] = srcElement[0x18];
                destElement[0x19] = srcElement[0x19];

                // Copy ints at offsets 0x1C, 0x20, 0x24, 0x28
                *reinterpret_cast<int*>(destElement + 0x1C) = *reinterpret_cast<const int*>(srcElement + 0x1C);
                *reinterpret_cast<int*>(destElement + 0x20) = *reinterpret_cast<const int*>(srcElement + 0x20);
                *reinterpret_cast<int*>(destElement + 0x24) = *reinterpret_cast<const int*>(srcElement + 0x24);
                *reinterpret_cast<int*>(destElement + 0x28) = *reinterpret_cast<const int*>(srcElement + 0x28);
            }
            idx++;
            destOffset += 0x2C;
        } while (idx < (unsigned int)this->count);
    }

    return this;
}