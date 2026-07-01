// FUNC_NAME: EA::Internal::ResizableArray::pushBack
void __thiscall ResizableArray::pushBack(void* this, void* element, undefined4 param_3, undefined4 param_4, void (*elementDestructor)(void*))
{
    int newCapacity;
    int local_10[3];   // temporary buffer for construction
    void* local_4;     // function pointer placeholder

    // Acquire global lock or critical section (likely thread-safe)
    FUN_004d3b50(&element);                // probably a lock/mutex
    FUN_004d4c00(&DAT_00d8a51c, &DAT_00e337ec); // another global lock

    // Assert if size exceeds 299 (array max capacity?)
    if (*(uint*)(this + 0x5c) > 299)
    {
        FUN_00938650(0);   // assert or error
    }

    newCapacity = *(int*)(this + 0x60);
    if (*(int*)(this + 0x5c) == newCapacity)
    {
        // Grow capacity: double or set to 1 if empty
        if (newCapacity == 0)
            newCapacity = 1;
        else
            newCapacity *= 2;

        FUN_00407880(newCapacity);   // reallocate internal storage
    }

    // Increment size
    int size = *(int*)(this + 0x5c);
    *(int*)(this + 0x5c) = size + 1;

    // Construct the new element in place (each element is 0x10 bytes)
    void* slot = *(void**)(this + 0x58) + size * 0x10;
    if (slot != 0)
    {
        FUN_004d3b50(local_10);   // placement new or copy constructor
    }

    // If temporary buffer has content, destroy it
    if (local_10[0] != 0)
    {
        (*local_4)(local_10[0]);   // call destructor for temporary
    }

    // If the original element pointer is valid, destroy it via provided destructor
    if (element != 0)
    {
        (*elementDestructor)(element);
    }

    return;
}