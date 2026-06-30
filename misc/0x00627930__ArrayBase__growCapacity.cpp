// FUNC_NAME: ArrayBase::growCapacity
// Address: 0x00627930
// This function grows the capacity of a dynamic array (e.g., EA::Container::VectorBase).
// It ensures the new capacity is at least double the old, with a minimum of 4 slots.
// If the requested minCapacity is not strictly greater than the current capacity,
// an assertion is triggered (likely a programming error).

void ArrayBase::growCapacity(void* container, int minCapacity, int* capacity, int elementSize, void* errorContext)
{
    int oldCapacity = *capacity;
    int newCapacity;

    // Ensure minimum capacity (doubled capacity must be at least 4)
    if (oldCapacity * 2 < 4) {
        newCapacity = 4;
    } else {
        newCapacity = oldCapacity * 2;
        // Sanity check: if minCapacity is not larger than oldCapacity, it's an error
        if ((minCapacity / 2 <= oldCapacity) && (minCapacity - 4 <= oldCapacity)) {
            // Trigger assertion failure (FUN_00633920) and break into debugger
            assertionFail(container, errorContext);
            __debugbreak();
            return;
        }
    }

    // Reallocate array memory from old size to new size (bytes)
    reallocateMemory(oldCapacity * elementSize, newCapacity * elementSize); // FUN_006279a0

    *capacity = newCapacity;
}