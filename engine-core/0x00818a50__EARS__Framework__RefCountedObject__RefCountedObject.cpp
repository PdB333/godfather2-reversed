// FUNC_NAME: EARS::Framework::RefCountedObject::RefCountedObject
void __thiscall EARS::Framework::RefCountedObject::RefCountedObject(void* this, void* internalObj, int handle)
{
    // +0x00: pointer to the internal object (often a base class pointer with vtable)
    this->m_pInternalObj = internalObj;
    // Call virtual function at vtable offset 8 (e.g., Acquire, Initialize)
    (*(void (**)(void))(*((int**)internalObj)[2]))();
    if (handle != 0) {
        // Associate handle with internal object (likely registration/lookup)
        this->m_handle = ::FUN_004265d0(handle, internalObj);
    } else {
        this->m_handle = 0;
    }
    // +0x04: handle or identifier for the internal object
}