// FUNC_NAME: SimContainer::releaseAllChildren
void __thiscall SimContainer::releaseAllChildren(SimContainer* thisPtr)
{
    // Fields (offsets relative to thisPtr):
    // +0x00: vtable pointer
    // +0x04: array of child object pointers  (void**)
    // +0x08: count of children               (int)
    // +0x0C: capacity (or similar, set to 0)  (int)
    // +0x10: extra allocated block            (void*)
    // +0x14: pointer to allocator object     (Allocator*)

    uint i = 0;
    int childCount = thisPtr->childCount;  // thisPtr[2]

    // Iterate over all children and destroy each one
    if (childCount != 0) {
        do {
            // Call first virtual function of child (likely destructor) with argument 0
            (*(void(__thiscall**)(int))(*reinterpret_cast<void**>(thisPtr->children[i])))(0);
            // Call second virtual function of child (likely memory deallocation) with (child pointer, 0)
            (*(void(__thiscall**)(void*, int))(*reinterpret_cast<void**>(thisPtr->children[i]) + 4))(thisPtr->children[i], 0);
            i++;
        } while (i < (uint)childCount);
    }

    // Call fourth virtual function of this container itself (callback after children destruction)
    (*(void(__thiscall**)())(*(int*)thisPtr->vtable + 0xC))();

    // Use allocator to free the children array
    // The allocator's second virtual function (offset +4) takes (pointer, 0)
    (*(void(__thiscall**)(void*, int))(*(int*)thisPtr->allocator + 4))(thisPtr->children, 0);
    thisPtr->children = nullptr;

    // Reset capacity (or similar field)
    thisPtr->capacity = 0;   // thisPtr[3]
    thisPtr->childCount = 0; // thisPtr[2]

    // Free the children array again (redundant, now nullptr)
    (*(void(__thiscall**)(void*, int))(*(int*)thisPtr->allocator + 4))(thisPtr->children, 0);

    // Free extra allocated block if present
    if (thisPtr->extraBlock != nullptr) {
        (*(void(__thiscall**)(void*, int))(*(int*)thisPtr->allocator + 4))(thisPtr->extraBlock, 0);
    }

    // Call fourth virtual function of allocator (cleanup/finalize)
    (*(void(__thiscall**)())(*(int*)thisPtr->allocator + 0xC))();
}