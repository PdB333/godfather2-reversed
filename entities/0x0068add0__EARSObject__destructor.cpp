// FUNC_NAME: EARSObject::destructor
// Address: 0x0068add0
// Role: Destructor that releases two owned sub-objects and sets vtable to a sentinel pointer

// Class offsets:
// +0x00: vtable pointer
// +0x08: void* m_pSubObj2
// +0x14: void (*m_deleteFunc2)(void*)
// +0x18: void* m_pSubObj1
// +0x24: void (*m_deleteFunc1)(void*)

void __fastcall EARSObject::destructor(EARSObject *this)
{
    if (this->m_pSubObj1 != nullptr)
    {
        this->m_deleteFunc1(this->m_pSubObj1);
    }
    if (this->m_pSubObj2 != nullptr)
    {
        this->m_deleteFunc2(this->m_pSubObj2);
    }
    this->vtable = &PTR_LAB_00d576d4;
}