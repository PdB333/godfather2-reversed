// FUNC_NAME: IndexedContainer::getCurrentElement
int __fastcall IndexedContainer::getCurrentElement(IndexedContainer* thisPtr)
{
    // Offset +0x10c: pointer to container (likely a dynamic array of some elements)
    void* container = *(void**)((char*)thisPtr + 0x10c);
    if (container == nullptr)
    {
        return 0;
    }

    // Offset +0x14c: stored index into the container
    unsigned int storedIndex = *(unsigned int*)((char*)thisPtr + 0x14c);

    // Get container's virtual function table
    void** vtable = *(void***)container;

    // vtable+0x8: function to get size/count (likely unsigned int (*)(void*))
    unsigned int (*getSize)(void*) = (unsigned int (*)(void*))vtable[2]; // 0x8 / 4 = 2

    // vtable+0xc: function to get element by index (int (*)(void*, unsigned int))
    int (*getElement)(void*, unsigned int) = (int (*)(void*, unsigned int))vtable[3]; // 0xc / 4 = 3

    unsigned int containerSize = getSize(container);
    if (storedIndex < containerSize)
    {
        return getElement(container, storedIndex);
    }

    return 0;
}