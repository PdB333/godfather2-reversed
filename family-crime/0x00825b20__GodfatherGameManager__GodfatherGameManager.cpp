// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
void __thiscall GodfatherGameManager::GodfatherGameManager(GodfatherGameManager *this) {
    // Set vtable pointer (base class)
    *(void **)this = (void *)&PTR_FUN_00d73470;  // +0x00 vtable
    
    // Initialize pointer at offset 0x3C (0xf * 4)
    this->field_0x3C = &PTR_LAB_00d73460;        // +0x3C
    
    // Initialize pointer at offset 0x48 (0x12 * 4)
    this->field_0x48 = &PTR_LAB_00d7345c;        // +0x48
    
    // Construct subobject at offset 0x50 (0x14 * 4)
    FUN_004086d0(&this->subObjectAt0x50);        // +0x50 subobject constructor
    FUN_00408310(&this->subObjectAt0x50);        // +0x50 subobject initialization
    
    // If pointer at +0x58 (0x16*4) is non-null, call its virtual function through +0x64 (0x19*4)
    if (this->somePointer != 0) {
        // +0x19*4 = offset 0x64 is likely vtable function pointer
        (*(void (__thiscall **)(void *))((char *)this->somePointer + 0x64))(this->somePointer);
    }
    
    // Global or manager initialization call
    FUN_0046c640();
}