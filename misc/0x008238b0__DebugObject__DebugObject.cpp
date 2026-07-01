// FUNC_NAME: DebugObject::DebugObject
void __fastcall DebugObject::DebugObject(DebugObject* this) {
    // Set vtable pointer
    this->vtable = &PTR_LAB_00d73418;

    // Initialize sentinel values for debugging/uninitialized detection
    this->sentinel1 = 0xbadbadba; // +0x04
    this->sentinel2 = 0xbeefbeef; // +0x08
    this->sentinel3 = 0xeac15a55; // +0x0C
    this->sentinel4 = 0x91100911; // +0x10

    // Initialize byte fields (likely screen coordinates or debug visuals)
    this->byteField_0x16 = 0x1e; // +0x16
    this->byteField_0x17 = 0x1e; // +0x17
    this->byteField_0x14 = 6;    // +0x14
    this->byteField_0x15 = 0x12; // +0x15
    this->byteField_0x18 = 0x3c; // +0x18
    this->byteField_0x19 = 0x3c; // +0x19
}