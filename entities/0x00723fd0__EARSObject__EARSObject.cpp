// FUNC_NAME: EARSObject::EARSObject
// Address: 0x00723fd0
// Constructor for an EARSObject derivative. Takes an allocation flag; if bit 0 is set,
// a separate memory block of 0x130 bytes is initialized (likely for extended data).
undefined4 __thiscall EARSObject::EARSObject(byte allocFlag) {
    // Call base class constructor (e.g., virtual table setup)
    this->EARSObject::baseConstructor();

    // If flag indicates dynamic allocation, allocate/initialize the object's data block
    if ((allocFlag & 1) != 0) {
        this->EARSObject::initializeDataBlock(0x130); // +0x130 size
    }

    return this;
}