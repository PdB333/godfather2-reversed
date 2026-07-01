// FUNC_NAME: EntityManager::collectActiveEntities

// Reconstructed from Ghidra at 0x00892130
// This function iterates over the internal entity list (dynamic array at this+0x8/0xC)
// and copies pointers to entities that have their "active" flag set (entity+0x174 != 0)
// into an output dynamic array (param_2 is a pointer to a DynamicArray<Entity*> structure).

// The output array is owned by the caller; this function will release any previous buffer in *param_2,
// then reallocate as needed to fit the filtered results.

// DynamicArray layout:
// +0x00: buffer pointer (int*)
// +0x04: count (int)
// +0x08: capacity (int)

void __thiscall EntityManager::collectActiveEntities(DynamicArray<Entity*>& outArray)
{
    uint index;
    int* elementPtr;
    int* newBuffer;
    int newCapacity;
    uint count = 0;

    // Reset output array: free old buffer and clear
    // FUN_009c8f10 is likely a deallocation function (e.g., operator delete or free)
    FUN_009c8f10(outArray.buffer);
    outArray.buffer = nullptr;
    outArray.capacity = 0;

    // Iterate over each entry in the internal list
    // Internal list: m_entitiesBuffer at this+0x8, m_entityCount at this+0xC
    if (m_entityCount != 0)
    {
        do
        {
            elementPtr = *(int**)(m_entitiesBuffer + index * 4);

            // Check if pointer is non-null and the entity's active flag (at offset 0x174) is non-zero
            if (elementPtr != nullptr && *(int*)(*elementPtr + 0x174) != 0)
            {
                // Ensure output array capacity
                if (outArray.count == outArray.capacity)
                {
                    // Need to grow: if capacity is 0, start with 1; otherwise double
                    newCapacity = (outArray.capacity == 0) ? 1 : (outArray.capacity * 2);
                    // FUN_00891ce0 is likely a reallocation function (e.g., realloc or new[] copy)
                    FUN_00891ce0(newCapacity);
                }

                // Append pointer to output
                newBuffer = outArray.buffer + outArray.count;
                outArray.count++;
                if (newBuffer != nullptr)
                {
                    *newBuffer = (int)*elementPtr;
                }
            }

            index++;
        } while (index < m_entityCount);
    }

    return;
}