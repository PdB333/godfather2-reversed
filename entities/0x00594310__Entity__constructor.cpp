// FUNC_NAME: Entity::constructor

undefined4 __thiscall Entity::constructor(Entity *this, int *pData, char boolParam)
{
    // Combine 4 bytes from pData into a DWORD (big-endian) and store at offset +0x160 (likely entity hash or GUID)
    this->guid = (pData[0] << 24) | (pData[1] << 16) | (pData[2] << 8) | pData[3];

    // Call some initialization routine (likely sets up default states)
    FUN_0059b5e0();

    // Initialize various fields to zero or default constants
    this->field_0x14c = 0;  // +0x14c
    this->field_0xb8  = 0;  // +0xb8
    this->field_0x130 = globals->someFloat;  // +0x130 (DAT_00e2b1a4)
    this->field_0x134 = globals->someFloat;  // +0x134
    this->field_0xb0  = globals->someFloat;  // +0xb0
    this->field_0xb4  = globals->anotherFloat; // +0xb4 (DAT_00e35654)
    this->field_0x7c  = ((boolParam != 0) | 0x1c2) * 4 | (this->field_0x7c & 0xfffff70a); // +0x7c bitmask
    this->field_0x138 = globals->another; // +0x138 (DAT_00e2afac)
    this->field_0x140 = 8;                // +0x140
    this->field_0x15c = 0;                // +0x15c

    // Set vector at +0xa0 to (0,0,0,1) using vtable function
    (**(void (__thiscall **)(int, int, int, float, Vector4 *))(*globals->vtable + 4))
        (0, 0, 0, 1.0f, &this->vecA0);   // likely translation or quaternion

    // Set vector at +0x80 to (0,0,1,0) using same vtable function
    (**(void (__thiscall **)(int, int, float, int, Vector4 *))(*globals->vtable + 4))
        (0, 0, 1.0f, 0, &this->vec80);   // likely scale or rotation axis

    return 1;
}