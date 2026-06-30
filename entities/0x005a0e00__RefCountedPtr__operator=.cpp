// FUNC_NAME: RefCountedPtr::operator=
void RefCountedPtr::operator=(const RefCountedPtr& other)
{
    // Self-assignment check
    if (&m_ptr != &other.m_ptr)
    {
        // Release current reference
        if (m_ptr != nullptr)
        {
            m_ptr->refCount--;
            if (m_ptr->refCount == 0)
            {
                releaseRefCountedObject(m_ptr); // calls FUN_005a3270 to deallocate
            }
        }
        // Copy pointer and increment ref count
        m_ptr = other.m_ptr;
        if (m_ptr != nullptr)
        {
            m_ptr->refCount++;
        }
    }
}