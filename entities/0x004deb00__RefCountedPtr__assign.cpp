// FUNC_NAME: RefCountedPtr::assign
void RefCountedPtr::assign(void* newPointer)
{
    // If we currently hold a pointer
    if (m_pRefCountedObject != nullptr)
    {
        // Decrement reference count at +0x04 of the object
        int* refCount = (int*)((char*)m_pRefCountedObject + 4);
        (*refCount)--;

        // If reference count reaches zero, destroy the object
        if (*(int*)((char*)m_pRefCountedObject + 4) == 0)
        {
            // Call destructor through vtable (+0x04 is the release function)
            void (*releaseFunc)(void*) = *(void (**)(void*))(*(int*)m_pRefCountedObject + 4);
            releaseFunc(m_pRefCountedObject);
        }

        // Clear our pointer (m_pRefCountedObject is at +0x20 of this)
        m_pRefCountedObject = nullptr;
    }

    // Assign the new pointer
    m_pRefCountedObject = newPointer;

    // If new pointer is not null, increment its reference count
    if (newPointer != nullptr)
    {
        int* refCount = (int*)((char*)newPointer + 4);
        (*refCount)++;
    }
}