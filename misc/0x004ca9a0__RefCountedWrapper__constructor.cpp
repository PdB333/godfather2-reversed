// FUNC_NAME: RefCountedWrapper::constructor

int RefCountedWrapper::constructor(RefCountedWrapper *this, RefCountedBase *ptr, int refCount)
{
    int newRefCount;
    RefCountedBase *localPtr;

    localPtr = ptr;
    // Increment reference count on the incoming pointer
    ptr->AddRef();
    if (refCount == 0) {
        newRefCount = 0;
    } else {
        // Possibly attach an external reference count
        newRefCount = FUN_004265d0(refCount, localPtr);
    }
    // Store the reference count result
    FUN_004cac50(localPtr, newRefCount);
    // Store the pointer at offset +0x14
    this->m_ptr = ptr;
    // Increment reference count again (maybe for the stored pointer)
    ptr->AddRef();
    if (refCount != 0) {
        // Attach the external reference count to the stored pointer
        newRefCount = FUN_004265d0(refCount, this->m_ptr);
        this->m_refCount = newRefCount; // +0x18
        // Detach the external reference count from the original pointer
        ptr->SetRefCount(refCount, 0);
        // Finalize the wrapper
        ptr->Finalize();
        return this;
    }
    this->m_refCount = 0; // +0x18
    ptr->Finalize();
    return this;
}