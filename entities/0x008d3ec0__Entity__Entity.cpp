// FUNC_NAME: Entity::Entity
Entity* __fastcall Entity::Entity(Entity* this) {
    // Call base class constructor (likely EARSObject or similar)
    FUN_008d2820();

    // Initialize vtable pointers and fields
    // Offset 0x4C: first vtable pointer (base class?)
    this->vtable1 = &PTR_FUN_00e2f19c;
    // Offset 0x50: some integer flag
    this->field_0x50 = 1;
    // Offset 0x54: zero
    this->field_0x54 = 0;
    // Offset 0x00: primary vtable pointer
    this->vtable0 = &PTR_FUN_00d7d588;
    // Offset 0x4C: overwritten with derived vtable pointer
    this->vtable1 = &PTR_LAB_00d7d578;
    // Offset 0x58: zero
    this->field_0x58 = 0;
    // Offset 0x5C: 2-byte zero
    *(short*)((char*)this + 0x5C) = 0;
    // Offset 0x5E: 2-byte zero
    *(short*)((char*)this + 0x5E) = 0;
    // Offset 0x64: copy of global _DAT_00d5780c
    this->field_0x64 = _DAT_00d5780c;
    // Offset 0x60: zero
    this->field_0x60 = 0;
    // Offset 0x68: zero
    this->field_0x68 = 0;
    // Offset 0x6C: 2-byte zero
    *(short*)((char*)this + 0x6C) = 0;
    // Offset 0x6E: 2-byte zero
    *(short*)((char*)this + 0x6E) = 0;
    // Offset 0x74: copy of global _DAT_00d5780c
    this->field_0x74 = _DAT_00d5780c;
    // Load another global
    uint uVar1 = DAT_00d5ccf8;
    // Offset 0x80: 1-byte zero
    *(byte*)((char*)this + 0x80) = 0;
    // Offset 0x81: 1-byte zero
    *(byte*)((char*)this + 0x81) = 0;
    // Offset 0x70: zero
    this->field_0x70 = 0;
    // Offset 0x78: copy of DAT_00d5ccf8
    this->field_0x78 = uVar1;
    // Offset 0x7C: copy of DAT_00d5ccf8
    this->field_0x7C = uVar1;
    // Offset 0x84: zero
    this->field_0x84 = 0;
    return this;
}