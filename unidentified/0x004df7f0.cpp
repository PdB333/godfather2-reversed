// FUN_004df7f0: RefCountedWrapper::setInnerRefPtr(RefCounted* newRef)
void __thiscall RefCountedWrapper::setInnerRefPtr(int* thisPtr, RefCounted* newRef)
{
    // Dereference 'this' to get outer data block pointer
    int* dataBlock = (int*)*thisPtr; // +0x00: pointer to data block (Pimpl)
    if (dataBlock == nullptr) return;

    // Old inner reference-counted pointer at dataBlock+0x20
    RefCounted* oldRef = *(RefCounted**)(dataBlock + 0x20);
    if (oldRef != nullptr)
    {
        // Decrement reference count at object offset +0x04
        int* refCount = (int*)((char*)oldRef + 4);
        (*refCount)--;

        // If ref count reached zero, call destructor (vtable entry at +0x04)
        if (*refCount == 0)
        {
            void** vtable = *(void***)oldRef; // vtable pointer at +0x00
            void (*destroy)(void*) = (void (*)(void*))vtable[1]; // second entry = destructor
            destroy(oldRef);
        }

        // Clear old pointer
        *(RefCounted**)(dataBlock + 0x20) = nullptr;
    }

    // Assign new pointer and increment its reference count
    *(RefCounted**)(dataBlock + 0x20) = newRef;
    if (newRef != nullptr)
    {
        (*(int*)((char*)newRef + 4))++; // refCount at +0x04
    }
}