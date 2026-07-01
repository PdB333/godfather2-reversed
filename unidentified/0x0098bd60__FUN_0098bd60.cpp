// FUNC_NAME: SomeContainer::clearAndDestroy
// Address: 0x0098bd60
// Iterates over an array of pointers, calls a cleanup function (at offset 0x0C) on each non-null element,
// then resets the end pointer to the beginning.
void __fastcall SomeContainer::clearAndDestroy(uint *this)
{
    // Structure assumed:
    // Offset 0x00: uint* m_begin;  // pointer to start of array
    // Offset 0x04: uint* m_end;    // pointer to one past last element
    uint *begin = (uint *)*this;          // this[0] = begin
    uint *end   = (uint *)this[1];        // this[1] = end

    if (end <= begin)
    {
        // empty, just reset end
        this[1] = (uint)begin;
        return;
    }

    // Iterate over all elements
    for (uint *current = begin; current < end; current++)
    {
        uint *objPtr = (uint *)*current;          // dereference to get object pointer
        if (objPtr != 0)
        {
            // Each object has a function pointer at offset 0x0C (third uint slot)
            // This is usually a cleanup/destructor-like callback
            void (*cleanupFunc)(uint *) = (void (*)(uint *))objPtr[3];
            if (cleanupFunc != 0)
            {
                cleanupFunc(objPtr);
            }
        }
    }

    // Reset the end pointer to the beginning, effectively clearing the array without deallocating memory
    this[1] = (uint)*this;  // this[1] = this[0]
}