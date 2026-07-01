// FUNC_NAME: SmartPtr::release
void SmartPtr::release()
{
    // Call the object's virtual destructor/release function (vtable[1]) with flag 0
    if (m_pControlBlock) // offset 0x10: pointer to control block containing vtable
    {
        (*(void (**)(int, int))(*(int*)m_pControlBlock + 4))(m_pObject, 0);
    }
    // Zero out the smart pointer fields: object pointer, reference count, weak reference count
    m_pObject = nullptr;
    m_refCount = 0;
    m_weakRefCount = 0;
}