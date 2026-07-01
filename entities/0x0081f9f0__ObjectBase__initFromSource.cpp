// FUNC_NAME: ObjectBase::initFromSource
// Address: 0x0081f9f0
// Role: Initialize object from source data, set vtable, and fill remaining slots with debug sentinels.
// Called by many constructors to set base fields and mark unused region.

void __thiscall ObjectBase::initFromSource(ObjectBase* this, uint32_t* source) {
    // Set virtual function table pointer (class-specific)
    this->vtable = (void**)(&VTable_00d73334); // +0x00

    // Copy 44 bytes (11 uint32_t) from source into the first data region
    for (int i = 0; i < 11; i++) {
        this->data[i] = source[i]; // offset +0x04 to +0x2C
    }

    // Debug sentinel values fill the remaining 32 bytes (8 uint32_t)
    // These mark the object's tail area as uninitialized/freed for debugging
    this->data[11] = 0xbadbadba; // +0x2C
    this->data[12] = 0xbeefbeef; // +0x30
    this->data[13] = 0xeac15a55; // +0x34
    this->data[14] = 0x91100911; // +0x38
    this->data[15] = 0xbadbadba; // +0x3C
    this->data[16] = 0xbeefbeef; // +0x40
    this->data[17] = 0xeac15a55; // +0x44
    this->data[18] = 0x91100911; // +0x48
}