// FUNC_NAME: EARSObject::EARSObject
// Address: 0x005005e0 - Constructor for EARS engine base object.
// Calls base initializer (0x005001a0) and optionally post-construct routine (0x009c8eb0) based on flag.

EARSObject* __thiscall EARSObject::EARSObject(EARSObject* this, byte initFlags)
{
    // Call base class constructor / core initializer at 0x005001a0
    this->baseInitialize();

    // If bit 0 of initFlags is set, perform additional registration or setup
    if (initFlags & 1) {
        this->postConstruct();  // 0x009c8eb0
    }

    return this;
}