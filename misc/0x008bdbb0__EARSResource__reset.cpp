// FUNC_NAME: EARSResource::reset
// Function address: 0x008bdbb0
// Role: Resets a resource handle, releasing the underlying resource and zeroing all fields.
// Structure offsets:
//   +0x00: m_ptr (void*) - pointer to the managed resource
//   +0x04: m_refCount (int) - reference count or usage counter
//   +0x08: m_flags (int) - flags or state

void __thiscall EARSResource::reset(void)
{
    this->m_refCount = 0;
    FUN_009c8f10(this->m_ptr);  // release the resource (likely decrement ref or free)
    this->m_ptr = nullptr;
    this->m_flags = 0;
}