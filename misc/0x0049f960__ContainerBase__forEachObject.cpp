// FUNC_NAME: ContainerBase::forEachObject
// Address: 0x0049f960
// Iterates over an array of object pointers stored at +0x8c (m_pObjectArray) with count at +0x90 (m_objectCount),
// calling the provided callback on each pointer along with the extra argument.

void __thiscall ContainerBase::forEachObject(void (*callback)(void*, uint32), uint32 arg)
{
    // +0x8c: m_pObjectArray (void**)
    // +0x90: m_objectCount (int)
    void** pArray = *(void***)(this + 0x8c);
    int count = *(int*)(this + 0x90);
    if (pArray && count > 0) {
        void** pEnd = pArray + count;
        do {
            callback(*pArray, arg);
            pArray++;
        } while (pArray < pEnd); // Original uses pointer comparison to base+count*4
    }
}