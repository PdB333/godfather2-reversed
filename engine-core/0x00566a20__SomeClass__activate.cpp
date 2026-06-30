// FUNC_NAME: SomeClass::activate
void SomeClass::activate() {
    // Set active flag at offset +0x10
    this->m_bActive = 1;

    // Retrieve vtable pointer from sub-object at offset +0xc
    // The sub-object's first 4 bytes are the vtable pointer
    void** vtable = *(void***)this->m_pSubObject;
    
    // Call virtual function at vtable index 14 (0x38 / 4)
    ((void (*)())vtable[14])();
}