// FUNC_NAME: SomeContainer::setCapacity
// Address: 0x00919380
// Sets the capacity of a dynamic container. If the new capacity is larger, it triggers a reallocation.
// The container structure is assumed to have a data pointer at offset 0 and capacity at offset 4.

void __thiscall SomeContainer::setCapacity(unsigned int newCapacity)
{
    // If the new capacity is larger than current, reallocate and update.
    if (this->capacity < newCapacity)
    {
        this->internalReserve(newCapacity);  // actually FUN_00917b10
        this->capacity = newCapacity;
        return;
    }

    // If shrinking, just update the capacity (no memory reallocation).
    if (newCapacity < this->capacity)
    {
        this->capacity = newCapacity;
    }
}