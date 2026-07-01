// FUNC_NAME: Debug::Debug
Debug* __thiscall Debug::Debug(Debug* this, void* parent) {
    // Call base initializer (FUN_0081f9f0) with parent pointer
    FUN_0081f9f0(parent);
    
    // Set virtual table pointer
    this->vtable = &Debug_vtable; // +0x00, vtable symbol PTR_FUN_00d73398
    
    // Place debug memory sentinel signatures (4 dwords at +0xA0..0xAC)
    this->debugMagic1 = 0xBADBADBA; // +0xA0
    this->debugMagic2 = 0xBEEFBEEF; // +0xA4
    this->debugMagic3 = 0xEAC15A55; // +0xA8
    this->debugMagic4 = 0x91100911; // +0xAC
    
    // Initialize debug flags to zero
    this->debugFlag1 = 0; // +0xB0
    this->debugFlag2 = 0; // +0xB4
    
    // Call post-initializer (FUN_00820980) with parent pointer
    FUN_00820980(parent);
    
    return this;
}