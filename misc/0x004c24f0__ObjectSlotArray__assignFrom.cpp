// FUNC_NAME: ObjectSlotArray::assignFrom
void __thiscall ObjectSlotArray::assignFrom(ObjectSlotArray* other)
{
    struct SlotEntry {
        int* objectPointer; // pointer to the actual object
        int* nextEntry;     // pointer to next SlotEntry in the linked list (also stored at object+4)
    };

    if (this == other)
        return;

    // Remove all current entries from the linked list
    for (int i = this->count - 1; i >= 0; --i)
    {
        SlotEntry* entry = &((SlotEntry*)this->entries)[i];
        int* object = entry->objectPointer;
        if (object != nullptr)
        {
            int* nextPtr = object + 1; // object->next (offset +4)
            if (*nextPtr == (int*)entry) // if object's next points directly to this entry
            {
                *nextPtr = entry->nextEntry;
            }
            else
            {
                // Find the predecessor and bypass this entry
                int* prevNext = object;
                while (prevNext + 1 != (int*)entry)
                {
                    prevNext = *(int**)(prevNext + 1);
                }
                *(int**)(prevNext + 1) = entry->nextEntry;
            }
        }
    }

    // Reallocate if the new count exceeds current capacity
    if (this->capacity < other->count)
    {
        customFree(this->entries);
        this->capacity = other->count;
        this->entries = (SlotEntry*)customAlloc(this->capacity * sizeof(SlotEntry));
        if (this->capacity == 0)
            this->entries = nullptr;
    }

    // Copy entries from other and insert into linked list
    for (unsigned int i = 0; i < (unsigned int)other->count; ++i)
    {
        SlotEntry* destEntry = &((SlotEntry*)this->entries)[i];
        int* srcObject = ((SlotEntry*)other->entries)[i].objectPointer;

        destEntry->objectPointer = srcObject;
        destEntry->nextEntry = nullptr;

        if (srcObject != nullptr)
        {
            // Insert destEntry into the linked list right after the source object
            destEntry->nextEntry = *(int**)(srcObject + 1); // save object's current next
            *(int**)(srcObject + 1) = (int*)destEntry;     // object->next now points to this slot
        }
    }

    this->count = other->count;
}