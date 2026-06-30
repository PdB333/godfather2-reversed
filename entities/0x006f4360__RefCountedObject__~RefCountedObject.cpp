// FUNC_NAME: RefCountedObject::~RefCountedObject
void __thiscall RefCountedObject::~RefCountedObject()
{
    // Call a virtual function at vtable[1] (offset 0x04) from the container pointed by +0x10.
    // This likely releases or frees the underlying object pointed by +0x00.
    // The vtable container is a structure that holds a pointer to the actual vtable.
    (**(void (__thiscall**)(void*, int))(*(int*)this->m_pVtableContainer + 4))(this->m_pObject, 0);
    // Clear all managed pointers
    this->m_pObject = 0; // +0x00
    this->m_pField4 = 0; // +0x04
    this->m_pField8 = 0; // +0x08
}