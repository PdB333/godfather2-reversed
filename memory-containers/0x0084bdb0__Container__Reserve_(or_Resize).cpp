// FUNC_NAME: Container::Reserve (or Resize)
void __thiscall Container::Reserve(uint newCapacity, bool copyExisting)
{
    Container* self = this; // param_1

    // Only grow if new capacity exceeds current size
    if (self->m_size < newCapacity)
    {
        // Calculate total allocation size: header (capacity word) + elements
        // Each element is 0x28 bytes (40 bytes)
        // Overflow check: (int)((ulonglong)newCapacity * 0x28 >> 0x20) handles overflow
        uint elementAreaSize = newCapacity * 0x28;
        uint allocSize = elementAreaSize + 4; // +4 for capacity header

        // Allocate memory (FUN_009c8e80 is likely an allocation function)
        uint* newBlock = (uint*)FUN_009c8e80(allocSize);
        uint* newData = nullptr;
        if (newBlock != nullptr)
        {
            newData = newBlock + 1; // skip header
            *newBlock = newCapacity; // store capacity in header

            // Construct new elements using default constructor (vector_constructor_iterator)
            // LAB_0084bcc0 points to the default constructor for the element type
            _vector_constructor_iterator_(newData, 0x28, newCapacity, &LAB_0084bcc0);
        }

        // If there are existing elements and we need to preserve them
        if (self->m_data != nullptr)
        {
            if (copyExisting && self->m_size > 0)
            {
                // Copy old elements into new memory
                // FUN_00714330 might be a copy assignment or move operation
                uint* oldData = self->m_data;
                uint* dst = newData;
                for (uint i = 0; i < self->m_size; i++)
                {
                    // Invoke copy on old element at offset i*0x28
                    FUN_00714330((uint)((byte*)oldData + i * 0x28));
                    // Copy a specific field at offset 0x24 (last 4 bytes of element)
                    dst[9] = *(uint*)((byte*)oldData + i * 0x28 + 0x24);
                    dst += 10; // advance by element size (10*4 = 0x28)
                }
            }

            // Destroy old elements (reverse order)
            uint* oldData = self->m_data;
            int elemCount = *(int*)((byte*)oldData - 4); // read old capacity from header

            // Iterate from last element downwards, cleaning up
            for (int i = elemCount - 1; i >= 0; i--)
            {
                uint* elemPtr = oldData + i * 10; // each element is 10 uints
                // Check a field at offset 0x04 of this element? (puVar1[-9] == offset -0x24)
                if (*(uint*)((byte*)elemPtr - 0x24) != 0)
                {
                    FUN_004daf90((uint*)((byte*)elemPtr - 0x24)); // call destructor
                }
                // Reset vtable pointer at start of element (offset -0x28)
                *(uint**)((byte*)elemPtr - 0x28) = &PTR_LAB_00e2f0c0; // vtable
            }

            // Free old memory (header + elements)
            FUN_009c8f10((uint)((byte*)oldData - 4));
        }

        // Update container to point to new data and set new size
        self->m_data = newData;
        self->m_size = newCapacity; // size becomes new capacity (i.e., resizes)
    }
}