// FUNC_NAME: EARSObject::EARSObject
EARSObject * EARSObject::EARSObject(EARSObject *this) {
    // First initialization step (possibly base class or memory setup)
    performInitialization();
    
    // Set the virtual function table pointer
    this->vtable = &_vtable_EARSObject;
    
    // Temporary object (unknown type): likely some structure with 3 fields
    // local_24[0] = 0, local_24[1] = 0, local_24[2] = _DAT_00d5780c (global constant)
    // Actually this is just a local array initialized, not used later except check destruct
    // We'll mimic decompiler layout; the actual purpose is unclear.
    
    // Second initialization step
    performInitialization();
    
    // Another temporary object (local_94) similar to above
    // local_94[0] = 0, local_94[1] = 0, local_94[2] = _DAT_00d5780c
    
    // Third initialization step
    performInitialization();
    
    // Capture global value for later assignment
    uint32_t globalValue = _DAT_00d5780c;
    
    // Set member fields: from offset +0x4C to +0x60 zeroed, +0x64 set to global value
    // Offsets in bytes: 0x13*4 = 0x4C, 0x14*4=0x50, 0x15*4=0x54, 0x16*4=0x58, 0x17*4=0x5C, 0x18*4=0x60, 0x19*4=0x64
    this->field_4C = 0;   // +0x4C
    this->field_50 = 0;   // +0x50
    this->field_54 = 0;   // +0x54
    this->field_58 = 0;   // +0x58
    this->field_5C = 0;   // +0x5C
    this->field_60 = 0;   // +0x60
    this->field_64 = globalValue; // +0x64
    
    // Cleanup: local_94 was zero-initialized, so condition is false -> skip
    // But the decompiler shows an if check for potential non-zero (indicates dynamic allocation)
    // We keep the check for completeness.
    if (local_94[0] != 0) {
        destroyTemporary(local_94);
    }
    
    // Cleanup: same for local_24
    if (local_24[0] != 0) {
        destroyTemporary(local_24);
    }
    
    return this;
}