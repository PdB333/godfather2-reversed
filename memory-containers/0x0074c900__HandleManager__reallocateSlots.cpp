// FUNC_NAME: HandleManager::reallocateSlots

struct Slot {
    void* object; // +0x00: pointer to the managed object
    Slot* next;   // +0x04: linked list next (used for free list or object back-link)
};

struct SlotArray { // this pointer layout
    Slot* slots;   // +0x00: pointer to array of Slot structures
    int size;      // +0x04: number of used slots
    int capacity;  // +0x08: total allocated slots
};

void __thiscall HandleManager::reallocateSlots(SlotArray* this, uint newCapacity)
{
    // Resize the internal slot array to fit at least newCapacity slots.
    // Maintains back-pointers from objects to their slot (at object+0x04).
    if ((uint)this->capacity < newCapacity)
    {
        Slot* newSlots = (Slot*)FUN_009c8e80(newCapacity * sizeof(Slot)); // allocate new array (8 bytes per slot)
        if (this->slots != nullptr)
        {
            uint index = 0;
            Slot* newSlot = newSlots;
            if (this->size != 0)
            {
                do
                {
                    Slot* oldSlot = &this->slots[index];
                    // Copy object pointer
                    newSlot->object = oldSlot->object;
                    newSlot->next = nullptr; // reset the link field
                    if (oldSlot->object != nullptr)
                    {
                        // The object stores a back-pointer to its slot at offset +0x04.
                        // Transfer the old back-pointer to the new slot (for chain management),
                        // then update the object to point to the new slot.
                        newSlot->next = (Slot*)(*(int*)((char*)oldSlot->object + 4));
                        *(Slot**)((char*)oldSlot->object + 4) = newSlot;
                    }
                    // Release/destroy the old slot (likely removes object reference)
                    FUN_004daf90(oldSlot);
                    index++;
                    newSlot++;
                } while (index < (uint)this->size);
            }
            FUN_009c8f10(this->slots); // free the old slot array
        }
        this->slots = newSlots;
        this->capacity = newCapacity;
    }
}