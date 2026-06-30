// FUNC_NAME: EARSObject::EARSObject
// Address: 0x00681740
// Role: Constructor for an EARS object with optional virtual base initialization
// The 'flags' parameter indicates whether to construct virtual bases (bit 0 set).

// Reconstructed C++ for EARSObject constructor
void __thiscall EARSObject::EARSObject(uint8_t flags) {
    // Call base class constructor (always)
    this->baseClassConstructor();  // FUN_00680f50

    // If the low bit is set, construct the virtual base
    if (flags & 1) {
        this->virtualBaseConstructor();  // FUN_009c8eb0
    }
}