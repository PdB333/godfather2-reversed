// FUNC_NAME: Entity::EntityConstructor
void __thiscall Entity::EntityConstructor(Entity *this)
{
    // Set vtable pointer (vtable at 0x00e34174)
    this->vtable = (VTablePtr)0x00e34174; // +0x00

    // Initialize fields to zero/default values
    this->field_4 = 0;             // +0x04
    this->field_8 = 0xffffffff;    // +0x08 (invalid handle/link)
    this->field_10 = 0;            // +0x10
    this->field_14 = 0;            // +0x14
    this->field_18 = 0;            // +0x18
    this->field_1c = 0;            // +0x1C
    this->field_20 = 0;            // +0x20
    this->field_24 = 0;            // +0x24
    this->field_8c = 0;            // +0x8C (offset 0x23 * 4)
    this->field_28 = 0;            // +0x28
    this->field_2c = 0;            // +0x2C (offset 0xB * 4)
    this->field_30 = 0;            // +0x30
    this->field_34 = 0;            // +0x34
    this->field_38 = 0;            // +0x38
    this->field_3c = 0;            // +0x3C
    this->field_40 = 0;            // +0x40
    this->field_44 = 0;            // +0x44
    this->field_48 = 0;            // +0x48
    this->field_4c = 0;            // +0x4C
    this->field_50 = 0;            // +0x50
    this->field_54 = 0;            // +0x54
    this->field_58 = 0;            // +0x58
    this->field_5c = 0;            // +0x5C
    this->field_60 = 0;            // +0x60
    this->field_64 = 0;            // +0x64
    this->field_68 = 0;            // +0x68
    this->field_6c = 0;            // +0x6C
    this->field_70 = 0;            // +0x70
    this->field_90 = 0;            // +0x90 (offset 0x24 * 4)
    this->field_78 = 0;            // +0x78
    this->field_a0 = 0;            // +0xA0 (offset 0x28 * 4)
    this->field_7c = 0;            // +0x7C
    this->field_80 = 0;            // +0x80
    this->field_84 = 0;            // +0x84
    this->field_98 = 0;            // +0x98 (offset 0x26 * 4)
    *(byte *)(this + 0x9c) = 0;    // +0x9C (byte field at offset 0x27*4 = 0x9C)
    this->field_94 = 0;            // +0x94 (offset 0x25 * 4)
}