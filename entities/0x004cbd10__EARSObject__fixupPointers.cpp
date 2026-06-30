// FUNC_NAME: EARSObject::fixupPointers

void EARSObject::fixupPointers()
{
    // +0x00: vtable pointer (set to static vtable)
    // +0x04: reserved (set to 0)
    // +0x08: pointer to child list structure (relative offset will be fixed up)
    this->vtable = &s_vtable_EARSObject;  // s_vtable_EARSObject at 0x00e3666c
    this->field_4 = 0;

    if (this->childListOffset != 0)
    {
        // Convert relative offset to absolute pointer
        this->childListOffset = (int)&this->childListOffset + (int)this;
    }

    ChildList* childList = (ChildList*)this->childListOffset;
    if (childList != nullptr)
    {
        // Fix up child list's own internal pointers
        if (childList->children != nullptr)
        {
            childList->children = (ChildObject**)((int)childList->children + (int)this);
        }

        int childCount = childList->count;
        for (int idx = 0; idx < childCount; idx++)
        {
            int offset = idx * 4;
            ChildObject** childSlot = (ChildObject**)((char*)childList->children + offset);
            ChildObject* child = *childSlot;
            if (child != nullptr)
            {
                // Adjust the pointer in the array by adding this base
                *childSlot = (ChildObject*)((int)child + (int)this);
            }
            // Re-fetch the possibly adjusted child pointer
            child = childList->children[idx];
            if (child != nullptr)
            {
                // Fix child's pointer at +0x68 (relative to child)
                if (child->somePtr != nullptr)
                {
                    child->somePtr = (void*)((int)child->somePtr + (int)child);
                }
                // Fix grandchild pointer at +0x04 (relative to what somePtr points to)
                void* grandChild = child->somePtr;
                if (grandChild != nullptr)
                {
                    if (*(void**)((char*)grandChild + 4) != nullptr)
                    {
                        *(void**)((char*)grandChild + 4) = (void*)((int)*(void**)((char*)grandChild + 4) + (int)child);
                    }
                }
            }
        }
    }
}