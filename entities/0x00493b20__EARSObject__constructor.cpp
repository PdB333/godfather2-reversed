// FUNC_NAME: EARSObject::constructor
void __fastcall EARSObject::constructor(EARSObject* this) {
    // Call base class constructor (no arguments)
    baseClassConstructor();
    
    // Call member initialization
    initMemberVariables(this);
    
    // If pointer at offset +0x290 is non-null, clean it up
    if (this->field_0x290 != nullptr) {
        cleanupPointer();
    }
    
    // If pointer at offset +0x298 is non-null, set up something using field at +0x14 and buffer at +0x2a0
    if (this->field_0x298 != nullptr) {
        setupSomething(this->field_0x14, this->field_0x298, &this->field_0x2a0);
    }
}