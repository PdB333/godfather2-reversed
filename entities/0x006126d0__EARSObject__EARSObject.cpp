// FUNC_NAME: EARSObject::EARSObject
void __thiscall EARSObject::EARSObject(EARSObject *this)
{
    // Vtable pointer at +0x00, points to class's vtable at 0x00e34174
    this->vtable = (void *)&PTR_LAB_00e34174;

    // +0x04: likely some flag or reference count, initialized to 0
    this->field_0x04 = 0;

    // +0x08: ID or handle, set to -1 (0xFFFFFFFF) - common default for invalid IDs
    this->objectId = 0xFFFFFFFF;

    // +0x10: field at offset 0x10 (skip index 3 at 0x0C, possibly inherited)
    this->field_0x10 = 0;

    // +0x14 through +0x24 (offsets 20-36) zeroed
    this->field_0x14 = 0;
    this->field_0x18 = 0;
    this->field_0x1C = 0;
    this->field_0x20 = 0;
    this->field_0x24 = 0;

    // +0x28 (offset 40) zeroed
    this->field_0x28 = 0;

    // +0x2C through +0x74 (offsets 44-116) zeroed - a large contiguous block
    this->field_0x2C = 0;
    this->field_0x30 = 0;
    this->field_0x34 = 0;
    this->field_0x38 = 0;
    this->field_0x3C = 0;
    this->field_0x40 = 0;
    this->field_0x44 = 0;
    this->field_0x48 = 0;
    this->field_0x4C = 0;
    this->field_0x50 = 0;
    this->field_0x54 = 0;
    this->field_0x58 = 0;
    this->field_0x5C = 0;
    this->field_0x60 = 0;
    this->field_0x64 = 0;
    this->field_0x68 = 0;
    this->field_0x6C = 0;
    this->field_0x70 = 0;
    this->field_0x74 = 0;

    // +0x78 (offset 120) zeroed
    this->field_0x78 = 0;

    // +0x7C through +0x84 (offsets 124-132) zeroed
    this->field_0x7C = 0;
    this->field_0x80 = 0;
    this->field_0x84 = 0;

    // +0x8C (offset 140) zeroed
    this->field_0x8C = 0;

    // +0x90 (offset 144) zeroed
    this->field_0x90 = 0;

    // +0x94 (offset 148) zeroed
    this->field_0x94 = 0;

    // +0x98 (offset 152) zeroed
    this->field_0x98 = 0;

    // +0x9C (offset 156) - byte field, set to 0
    this->byteField_0x9C = 0;

    // +0xA0 (offset 160) zeroed
    this->field_0xA0 = 0;

    // Note: offset 0x0C (index 3) is not set here; may be initialized by parent constructor or later.
}