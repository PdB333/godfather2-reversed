// FUNC_NAME: RefCountedPointer::assign
void RefCountedPointer::assign(RefCountedObject* newPtr)
{
    RefCountedObject* oldPtr = this->m_ptr;
    if (oldPtr != newPtr)
    {
        if (oldPtr != nullptr)
        {
            // Decrement reference count at offset +0x8
            oldPtr->m_refCount--;
            if (oldPtr->m_refCount == 0)
            {
                // Call destructor/release function
                sampleDestructor(oldPtr);
                // Custom deallocation via global allocator vtable (DAT_01205964)
                g_allocatorVtable->deallocate(oldPtr, 0);
            }
            this->m_ptr = nullptr;
        }
        if (newPtr != nullptr)
        {
            // Increment reference count at offset +0x8
            newPtr->m_refCount++;
            this->m_ptr = newPtr;
        }
    }
}