// FUNC_NAME: ObjectArray::clear
// Address: 0x0043cf50
// Role: Releases all objects in the array, frees the array memory, and resets container state.
// The array stores 0x1c-byte elements; the object pointer is at offset 0x18 within each element.
// m_pFactory (offset 0x0c) provides a vtable-based release method (index 1 in vtable) that takes (object, 0).
// After clearing, calls FUN_009c8f10 to deallocate the array buffer.

void __thiscall ObjectArray::clear(ObjectArray* this)
{
    int i;
    int count;
    int elemOffset;
    void* pObject;
    
    count = this->m_nCount - 1;
    if (count >= 0) {
        elemOffset = count * 0x1c;
        do {
            // Each element is 0x1c bytes; object pointer is at offset 0x18
            pObject = *(void**)(*(int*)(this->m_pArray) + 0x18 + elemOffset);
            if (pObject != 0) {
                // Call vtable method at index 1 (offset 4) of the factory object
                (**(code**)(**(int**)(this->m_pFactory) + 4))(pObject, 0);
            }
            count = count - 1;
            elemOffset = elemOffset - 0x1c;
        } while (count >= 0);
    }
    
    this->m_nCount = 0;
    
    // Free the array buffer (likely a custom deallocator)
    FUN_009c8f10(this->m_pArray);
    
    this->m_pArray = 0;
    this->m_nCapacity = 0;  // offset 0x18
}
```