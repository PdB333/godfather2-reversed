// FUNC_NAME: Container::addElement
void __thiscall Container::addElement(int param_2, int param_3, int param_4, int param_5)
{
    // Get a pointer to a free slot from the internal pool (FUN_004bc300)
    int* slot = reinterpret_cast<int*>(getFreeSlot());

    // Check if the dynamic array needs to grow (capacity at +0x24, size at +0x20)
    int oldSize = *(int*)(this + 0x20);
    if (*(int*)(this + 0x24) == oldSize)
    {
        int newCapacity = (oldSize == 0) ? 1 : oldSize * 2;
        // Reallocate the array to the new capacity (FUN_00407880)
        reallocArray(newCapacity);
    }

    // Increment the size
    int index = *(int*)(this + 0x20);
    *(int*)(this + 0x20) = index + 1;

    // If the slot at (data base + index * elementSize) already exists, destroy it
    // Element size appears to be 0x10 based on the address calculation
    int* base = *(int**)(this + 0x1c);
    if (reinterpret_cast<int*>(reinterpret_cast<char*>(base) + index * 0x10) != nullptr)
    {
        // Destroy the existing element (FUN_004d3b50 takes param_3 as the element)
        destroyElement(param_3);
    }

    // Fill the newly allocated slot
    slot[1] = *(int*)(this + 0x20) - 1;   // Store the index (size - 1)
    slot[0] = param_4;                    // First field
    slot[2] = param_2;                    // Second field
    slot[0xC] = param_5;                  // Field at offset 0x30 (0xC * 4)
}