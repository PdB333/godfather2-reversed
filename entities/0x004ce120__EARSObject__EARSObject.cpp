// FUNC_NAME: EARSObject::EARSObject
EARSObject* __thiscall EARSObject::EARSObject(byte allocatedFlag) {
    // Set vtable pointer to class-specific vtable
    this->vtable = &EARSObject_vtable; // +0x00, vtable address: 0x00e36c60

    // Initialize base components
    this->initPart1(); // FUN_004ce530 - likely base class constructor or member initialization
    this->initPart2(); // FUN_004cebd0 - second initialization step
    this->initPart3(); // FUN_004083d0 - third initialization step

    // If the allocation flag indicates, perform post-init cleanup (possibly deallocation or debug action)
    if (allocatedFlag & 1) {
        this->cleanup(); // FUN_009c8eb0 - cleanup/delete helper
    }

    return this;
}