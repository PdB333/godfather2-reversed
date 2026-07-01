// FUNC_NAME: EARSObject::~EARSObject()
void __fastcall EARSObject::~EARSObject(EARSObject* this)
{
    // Set vtable pointer to the class's normal vtable (likely at 0x00d74eb4)
    this->vtable = (void**)&VTable_00d74eb4;

    // If the object has a child/subobject pointer, deallocate it
    if (this->m_pSomething != 0) {
        FUN_004daf90(this->m_pSomething); // +0x04: subobject pointer; likely operator delete or destructor call
    }

    // Set vtable to purecall vtable to mark object as destroyed
    this->vtable = (void**)&VTable_Purecall_00e3924c;
}