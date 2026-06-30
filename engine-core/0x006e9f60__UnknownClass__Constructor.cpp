// FUNC_NAME: UnknownClass::Constructor
void* __thiscall UnknownClass::Constructor(byte initializationFlag) {
    // Call base class constructor
    BaseClassConstructor();
    
    // If bit 0 is set, initialize member at offset 0xAC (172 bytes)
    if (initializationFlag & 0x1) {
        InitMemberAtOffset0xAC(this);
    }
    
    return this;
}