// FUNC_NAME: BaseObject::~BaseObject
void * __thiscall BaseObject::~BaseObject(BaseObject *this, byte deletingFlag)
{
    // Set vtable to current class's vtable (for proper virtual dispatch during destruction)
    // +0x00: vtable pointer
    this->vtable = &PTR_FUN_00e35228;

    // If there's a child object (offset +0x10) and a child interface (offset +0x04), invoke interface method
    // +0x04: m_childInterface (pointer to interface with virtual functions)
    // +0x08: m_childArg1 (argument passed to interface method)
    // +0x10: m_childObject (pointer to target object)
    if (this->m_childObject != 0 && this->m_childInterface != 0) {
        // Call virtual function at vtable offset 4 on the child interface
        // This likely performs cleanup on the child object
        (this->m_childInterface->vtable->method4)(this->m_childObject, this->m_childArg1);
    }

    // If child interface exists, call its virtual function at vtable offset 12
    // This might be a release/detach function
    if (this->m_childInterface != 0) {
        (this->m_childInterface->vtable->method12)();
    }

    // If the deleting flag (bit 0) is set, deallocate this object's memory
    if ((deletingFlag & 1) != 0) {
        FUN_009c8eb0(this); // Likely ::operator delete
    }

    return this;
}