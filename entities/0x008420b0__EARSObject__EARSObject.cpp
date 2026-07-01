// FUNC_NAME: EARSObject::EARSObject
// Address: 0x008420b0
// Role: Constructor for base EARS engine object. Initializes 7 zeroed fields before setting vtable pointer.
void __thiscall EARSObject::EARSObject(EARSObject *this) {
    // Repeatedly call internal zero-initializer for each field (offsets +0x04 through +0x1C)
    this->zeroField();
    this->zeroField();
    this->zeroField();
    this->zeroField();
    this->zeroField();
    this->zeroField();
    this->zeroField();
    // Set vtable pointer at offset 0x0
    this->vtable = (void**)0x00d74760; // VTable for EARSObject
}