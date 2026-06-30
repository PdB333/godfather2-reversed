// FUNC_NAME: SomeClass::constructor
void SomeClass::constructor(void) {
    // Set type field at offset 8 (short) to 3
    *(unsigned short*)(this + 8) = 3;
    // Set vtable pointer at offset 0
    this->vtable = &PTR_LAB_00e351ac; // vtable table
    // Initialize subobject at offset 16 (this+4) – likely base class
    FUN_0049b000(this + 4);
    // Zero out fields at offsets 0xA8, 0xAC, 0xB8
    this->field_0xA8 = 0; // +0x2a (word)
    this->field_0xAC = 0; // +0x2b (word)
    this->field_0xB8 = 0; // +0x2e (word)
    // Set pointer field at offset 4 to point to subobject at this+4
    this->subobjectPtr = this + 4;
}