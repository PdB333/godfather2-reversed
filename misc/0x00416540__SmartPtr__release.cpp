// FUNC_NAME: SmartPtr::release

// 0x00416540 - Smart pointer release function.
// Decrements the reference count of the pointed RefCounted object.
// If the count reaches zero, calls the object's virtual destructor (vtable[1])
// and sets the internal pointer to null.
// Object layout: offset 0x00 - vtable pointer, offset 0x04 - reference count (int32).

void SmartPtr::release()
{
    // m_ptr is stored at offset 0x00 of this smart pointer struct.
    if (m_ptr != nullptr)
    {
        // Ref count is at offset 0x04 of the pointed object.
        int32_t* refCount = reinterpret_cast<int32_t*>(reinterpret_cast<char*>(m_ptr) + 4);
        (*refCount)--;

        // If ref count reaches zero, call the vtable's second entry (offset 0x04 from vtable start).
        if (*refCount == 0)
        {
            void** vtable = *reinterpret_cast<void***>(m_ptr);
            // vtable[1] is the destructor (typically second virtual function in EARS).
            typedef void (*DestroyFunc)(void*);
            DestroyFunc destroy = reinterpret_cast<DestroyFunc>(vtable[1]);
            destroy(m_ptr);
        }

        // Release ownership: null out internal pointer.
        m_ptr = nullptr;
    }
}