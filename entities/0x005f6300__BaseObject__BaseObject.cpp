// FUNC_NAME: BaseObject::BaseObject
// Function address: 0x005f6300
// Identified role: Constructor for BaseObject. Calls base class constructor (0x005f8bc0)
// and optionally allocates memory via FUN_009c8eb0 based on a flag.

uint32_t __thiscall BaseObject::BaseObject(uint32_t this, uint8_t allocFlag) {
    // Call base class constructor (likely BaseEntity or similar)
    FUN_005f8bc0();
    
    // If low bit of allocFlag is set, allocate additional memory for this instance
    // FUN_009c8eb0 is likely a memory allocator/initializer
    if ((allocFlag & 1) != 0) {
        FUN_009c8eb0(this);
    }
    
    // Return this pointer
    return this;
}