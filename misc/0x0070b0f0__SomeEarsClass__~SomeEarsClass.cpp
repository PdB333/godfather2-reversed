// FUNC_NAME: SomeEarsClass::~SomeEarsClass
void __thiscall SomeEarsClass::~SomeEarsClass(SomeEarsClass* thisPtr)
{
    // Free owned pointer at offset +0x10 (m_pMember2)
    if (thisPtr->m_pMember2 != 0) {
        deallocateObject(thisPtr->m_pMember2);
    }
    // Free owned pointer at offset +0x08 (m_pMember1)
    if (thisPtr->m_pMember1 != 0) {
        deallocateObject(thisPtr->m_pMember1);
    }
    // Set vtable to base class vtable (0x00e3729c)
    thisPtr->vtable = (SomeEarsClass_vtable*)0x00e3729c;
}