// FUN_00461850: PointerArray::pushBack
void __thiscall PointerArray::pushBack(int** param_1, int** param_2)
{
    int* buffer = param_1[0];          // +0x00: pointer to dynamic array of ints
    int& size = param_1[1];            // +0x04: current number of elements
    int& capacity = param_1[2];        // +0x08: allocated capacity

    // Resize if full (double capacity or start at 1)
    if (size == capacity)
    {
        int newCapacity = (capacity == 0) ? 1 : capacity * 2;
        PointerArray::resize(newCapacity);   // FUN_00461ea0
    }

    // Insert new element at the end
    int* slot = buffer + size;         // element = buffer[ size ]
    size++;

    if (slot != nullptr)
    {
        *slot = 0;                     // clear slot (possible safety)
        int* value = *param_2;         // value to insert
        *slot = value;                 // store pointer in array

        if (value != nullptr)
        {
            // Set the object's "container pointer" (offset +0x08) to point back to this slot
            *(int**)(value + 2) = slot;   // value[2] == *(int**)(value + 8)
            *param_2 = nullptr;           // take ownership: clear caller's pointer
        }
    }
}