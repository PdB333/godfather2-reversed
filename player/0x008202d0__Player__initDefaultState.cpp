// FUNC_NAME: Player::initDefaultState
void __fastcall Player::initDefaultState(int this)
{
    // Initialize various player state fields with global default values
    *(int*)(this + 0x4C) = DAT_00d5ef9c;   // +0x4C: defaultHealth
    *(int*)(this + 0x50) = DAT_00d5d7b8;   // +0x50: defaultStamina
    *(int*)(this + 0x68) = DAT_00d73390;   // +0x68: defaultArmor
    *(int*)(this + 0x54) = _DAT_00d5780c;  // +0x54: defaultDamage
    *(int*)(this + 0x64) = _DAT_00d5780c;  // +0x64: defaultDamage2 (same value)
    *(int*)(this + 0x6C) = DAT_00d5ef6c;   // +0x6C: defaultSomething
    *(int*)(this + 0x58) = 0;              // +0x58: zero
    *(int*)(this + 0x5C) = 0;              // +0x5C: zero
    *(int*)(this + 0x60) = 0;              // +0x60: zero
    *(int*)(this + 0x70) = DAT_00d7338c;   // +0x70: defaultAnother
    *(int*)(this + 0x80) = _DAT_00d5780c;  // +0x80: defaultDamage repeated
    *(int*)(this + 0x84) = _DAT_00d5780c;  // +0x84: defaultDamage repeated
    *(int*)(this + 0x88) = _DAT_00d5780c;  // +0x88: defaultDamage repeated
    *(int*)(this + 0x8C) = _DAT_00d5780c;  // +0x8C: defaultDamage repeated
    *(int*)(this + 0x90) = 0;              // +0x90: zero
    *(int*)(this + 0x94) = 0;              // +0x94: zero
    *(int*)(this + 0x98) = 0;              // +0x98: zero
    *(int*)(this + 0x9C) = _DAT_00d5780c;  // +0x9C: defaultDamage repeated
    *(int*)(this + 0xC0) = _DAT_00d5780c;  // +0xC0: sub-object field
    *(int*)(this + 0xC4) = 0;              // +0xC4: zero
    *(int*)(this + 0xC8) = 0;              // +0xC8: zero
    *(int*)(this + 0xCC) = 0;              // +0xCC: zero
    *(int*)(this + 0xD0) = 0;              // +0xD0: zero
    *(int*)(this + 0xD4) = _DAT_00d5780c;  // +0xD4: defaultDamage repeated
    *(int*)(this + 0xD8) = 0;              // +0xD8: zero
    *(int*)(this + 0xDC) = 0;              // +0xDC: zero
    *(int*)(this + 0xE0) = 0;              // +0xE0: zero
    *(int*)(this + 0xE4) = 0;              // +0xE4: zero
    *(int*)(this + 0xE8) = _DAT_00d5780c;  // +0xE8: defaultDamage repeated
    *(int*)(this + 0xEC) = 0;              // +0xEC: zero
    *(int*)(this + 0xF0) = 0;              // +0xF0: zero
    *(int*)(this + 0xF4) = 0;              // +0xF4: zero
    *(int*)(this + 0xF8) = 0;              // +0xF8: zero
    *(int*)(this + 0xFC) = _DAT_00d5780c;  // +0xFC: defaultDamage repeated

    // Initialize sub-object at offset 0xC0 with size 0x100 (from 0xC0 to 0x1C0?)
    FUN_0056dbe0((int*)(this + 0xC0), this + 0x100); // likely a constructor or memset

    // Set a flag at offset 0x121 to 1 (active/initialized)
    *(char*)(this + 0x121) = 1;
}