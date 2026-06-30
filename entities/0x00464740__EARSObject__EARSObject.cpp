// FUNC_NAME: EARSObject::EARSObject
// Constructor at 0x00464740 for EARSObject; calls base init and optional setup based on flag.
EARSObject* __thiscall EARSObject::EARSObject(EARSObject* this, uint8_t flags) {
    // Base class initialization (0x00464770)
    this->initBase();

    if (flags & 1) {
        // Perform additional setup when flag bit 0 is set (0x009c8eb0)
        this->setup();
    }

    return this;
}