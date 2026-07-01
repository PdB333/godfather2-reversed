// FUNC_NAME: Player::constructor
void* __thiscall Player::constructor(Player *this, int someArg) {
    // base class constructor (FUN_0046c590)
    BaseClass::constructor(someArg);

    // set vtable pointers (multiple inheritance)
    this->vtable0 = &PTR_FUN_00d8bbf8;           // +0x00
    this->vtable3C = &PTR_LAB_00d8bbe8;          // +0x3C
    this->vtable48 = &PTR_LAB_00d8bbe4;          // +0x48
    this->vtable50 = &PTR_LAB_00d8bbcc;          // +0x50

    // initialize fields
    this->field_0x58 = 0;                        // +0x58
    this->field_0x5C = 0;                        // +0x5C
    *(uint16 *)((uint8 *)this + 0x60) = 0;       // +0x60 (2 bytes)
    *(uint16 *)((uint8 *)this + 0x62) = 0;       // +0x62 (2 bytes)
    this->field_0x64 = 0;                        // +0x64
    *(uint16 *)((uint8 *)this + 0x68) = 0;       // +0x68 (2 bytes)
    *(uint16 *)((uint8 *)this + 0x6A) = 0;       // +0x6A (2 bytes)

    // magic number sentinels
    this->magic1 = 0xbadbadba;                   // +0x144
    this->magic2 = 0xbeefbeef;                   // +0x148
    this->magic3 = 0xeac15a55;                   // +0x14C
    this->magic4 = 0x91100911;                   // +0x150

    // additional zero fields
    this->field_0x154 = 0;                       // +0x154
    this->field_0x168 = 0;                       // +0x168
    this->field_0x16C = 0;                       // +0x16C
    this->field_0x170 = 0;                       // +0x170
    this->field_0x174 = 0;                       // +0x174
    this->field_0x178 = 0;                       // +0x178
    this->field_0x17C = 0;                       // +0x17C
    this->field_0x180 = 0;                       // +0x180
    this->field_0x204 = 0;                       // +0x204
    this->field_0x208 = 0;                       // +0x208

    // byte-length zero fields
    *(uint8 *)((uint8 *)this + 0x1C) = 0;        // +0x1C
    *(uint8 *)((uint8 *)this + 0x30) = 0;        // +0x30
    *(uint8 *)((uint8 *)this + 0x61) = 0;        // +0x61
    *(uint8 *)((uint8 *)this + 0x41) = 0;        // +0x41

    return this;
}