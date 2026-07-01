// FUNC_NAME: EARSObject::EARSObject
// Address: 0x008bd840
// Role: Constructor with conditional initialization

EARSObject::EARSObject(byte initializeFlag) {
    // Call base class constructor (FUN_008c80c0)
    BaseClass::BaseClass();

    // If flag bit 0 is set, perform additional initialization
    if (initializeFlag & 1) {
        // Call additional initialization (FUN_009c8eb0)
        this->additionalInit();
    }

    return this;
}