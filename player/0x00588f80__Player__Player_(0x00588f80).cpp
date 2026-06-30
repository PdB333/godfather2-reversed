// FUNC_NAME: Player::Player  (0x00588f80)
void __thiscall Player::Player(Player *this) {
    // Call base class constructor (Entity or Sentient)
    Entity::Entity();

    // Set vtable pointer (0x00)
    this->vtable = &PTR_FUN_00e3ac3c;

    // Zero out fields from offset 0x74 to 0x78 (3 dwords)
    this->field_0x74 = 0;
    this->field_0x78 = 0;
    this->field_0x7c = 0;

    // Zero single byte at offset 0x70
    *(undefined1 *)(this + 0x1c) = 0;

    // Zero more fields at various offsets
    this->field_0x80 = 0;  // +0x80
    this->field_0x8c = 0;  // +0x8c
    this->field_0x9c = 0;  // +0x9c
    this->field_0xa4 = 0;  // +0xa4
    this->field_0xb4 = 0;  // +0xb4
    this->field_0xb8 = 0;  // +0xb8
    this->field_0xbc = 0;  // +0xbc
    this->field_0xc0 = 0;  // +0xc0
    this->field_0xc4 = 0;  // +0xc4
    this->field_0xc8 = 0;  // +0xc8
    this->field_0xcc = 0;  // +0xcc
    this->field_0xd0 = 0;  // +0xd0

    // Set specific field values
    this->field_0x84 = 4;           // +0x84 → perhaps control mode (4 = player controlled?)
    this->field_0x88 = 0xFFFFFFFF;  // +0x88 → invalid ID or reference
    this->field_0x90 = 0;           // +0x90
    this->field_0x94 = 0;           // +0x94
    this->field_0x98 = 0xFFFFFFFF;  // +0x98 → invalid ID or -1 initial state
    this->field_0xa0 = 0xFFFFFFFF;  // +0xa0 → another invalid reference
    this->field_0xa8 = 0;           // +0xa8
    this->field_0xac = 0;           // +0xac
    this->field_0xb0 = 0x20;        // +0xb0 → possibly max count (32 slots)
}