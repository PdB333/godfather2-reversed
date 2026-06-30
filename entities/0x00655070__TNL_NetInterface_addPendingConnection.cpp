// Xbox PDB: TNL::NetInterface::addPendingConnection
// FUNC_NAME: ObjectPool::addObject
// Address: 0x00655070
// Role: Adds an object to an internal pool/dynamic array, increments its reference count, and stores it in the array.

void __thiscall ObjectPool::addObject(int* object)
{
    // Lock or prepare the container for modification
    lockContainer();          // FUN_006551b0

    // Attempt to allocate a slot (e.g., from a free list or by incrementing count)
    int slotIndex = allocateSlot();   // FUN_00655250

    // If a slot was allocated, initialize it (maybe clear or set default)
    if (slotIndex != 0)
    {
        initSlot(this, slotIndex);    // FUN_006576b0
    }

    // Increment the object's reference count (offset +0x08)
    *(int*)(object + 8) += 1;

    // Pointer to the container's element count (this+0x24)
    int* countPtr = (int*)(this + 0x24);

    // Grow the internal array to accommodate the new element (new size = old count + 1)
    growArray(*countPtr + 1);         // FUN_00657bf0

    // Increase the count after successful growth
    (*countPtr)++;

    // Pointer to the array of object pointers (this+0x2c)
    int** arrayPtr = (int**)(this + 0x2c);

    // Compute address of the newly added slot (index = count - 1)
    int* slotPtr = *arrayPtr + (*countPtr - 1);
    if (slotPtr != nullptr)
    {
        *slotPtr = object;
    }
}