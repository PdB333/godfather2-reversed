// FUNC_NAME: HandleManager::reserveCapacity
void __thiscall HandleManager::reserveCapacity(unsigned int newCapacity)
{
    // this is a pointer to the HandleManager instance
    // Offsets:
    // +0x00: slots (Slot*)
    // +0x04: count (int) - number of used slots
    // +0x08: capacity (int) - number of allocated slots

    // If the current capacity is already >= newCapacity, do nothing
    if (this->capacity >= newCapacity) {
        return;
    }

    // Allocate a new slot array with newCapacity elements (each 8 bytes)
    Slot* newSlots = (Slot*)FUN_009c8e80(newCapacity * 8); // operator new or custom alloc

    if (this->slots != nullptr) {
        unsigned int i = 0;
        Slot* dest = newSlots;

        if (this->count != 0) {
            do {
                Slot* src = &this->slots[i]; // source slot from old array

                if (dest != nullptr) {
                    // Copy slot data: object pointer and next free link
                    void* objectPtr = src->object;
                    dest->object = objectPtr;
                    dest->nextFree = nullptr; // initialize next link to null

                    // If the slot holds an object, update the object's back-pointer
                    // The object at address objectPtr stores a pointer to its slot at offset +4.
                    if (objectPtr != nullptr) {
                        dest->nextFree = *(Slot**)((char*)objectPtr + 4); // old back-pointer
                        *(Slot**)((char*)objectPtr + 4) = dest;          // point to new slot
                    }
                }

                // Clear the old slot
                if (src->object != nullptr) {
                    FUN_004daf90(src); // likely removes the slot from internal lists or frees
                }

                i++;
                dest++;
            } while (i < (unsigned int)this->count);
        }

        // Free the old slot array
        FUN_009c8f10(this->slots); // operator delete or custom free
    }

    // Update the manager's pointers and capacity
    this->slots = newSlots;
    this->capacity = newCapacity;
}