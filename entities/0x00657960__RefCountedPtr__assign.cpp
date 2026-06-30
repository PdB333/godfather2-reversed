// FUNC_NAME: RefCountedPtr::assign
void RefCountedPtr::assign(RefCountedObject* newPtr) {
    RefCountedObject* oldPtr = *m_ptr; // m_ptr is the member pointer (this->m_ptr)
    if (oldPtr) {
        // Decrement reference count at offset +8 from object start
        oldPtr->m_refCount--;
        if (oldPtr->m_refCount == 0) {
            // Call virtual destructor (second vtable entry at offset +8 from vtable)
            ((void (*)(RefCountedObject*))(oldPtr->vtable[1]))(oldPtr);
        }
    }
    *m_ptr = newPtr;
    if (newPtr) {
        newPtr->m_refCount++;
    }
}