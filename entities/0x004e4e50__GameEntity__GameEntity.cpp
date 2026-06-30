// FUNC_NAME: GameEntity::GameEntity
// Function address: 0x004e4e50
// Role: Constructor for GameEntity class. Initializes all member fields to default values,
// stores constructor parameters into specific offsets, sets vtable, and zeros many fields.

void __thiscall GameEntity::GameEntity(GameEntity* this, int typeId, int param2, int param3, short param4, byte param5, int param6, int param7, int param8)
{
    // vtable pointer at offset 0x00
    this->vtable = &PTR_FUN_00e371d8;

    // Fields at various offsets (all 4-byte unless noted)
    this->m_typeId = typeId;           // +0x04
    this->m_param7 = param7;           // +0x08
    this->m_param8 = param8;           // +0x0C
    this->m_param3 = param3;           // +0x18

    // Byte at offset 0x1E
    *(uint8*)((int)this + 0x1E) = param5;

    // Short at offset 0x1C (writing through pointer at index 7, which is offset 0x1C)
    *(uint16*)((int)this + 0x1C) = param4;

    this->m_param2 = param2;           // +0x24
    this->m_param6 = param6;           // +0x28

    // Fields from +0x80 to +0x8C
    this->m_field80 = -1;              // +0x80
    this->m_field84 = 0;               // +0x84
    this->m_field88 = 0;               // +0x88
    this->m_field8C = 0;               // +0x8C

    // Fields at +0x10 and +0x20
    this->m_field10 = 0;               // +0x10
    this->m_field20 = 0;               // +0x20

    // Fields at +0x90, +0x94, +0x98 (byte)
    this->m_field90 = 0;               // +0x90
    this->m_field94 = 0;               // +0x94
    *(uint8*)((int)this + 0x98) = 0;   // +0x98 byte

    // Zero out 4 groups of 4 ints each (offsets 0x30 to 0x7C? Actually indices 0xC-0x1F)
    // These correspond to offsets: 0x30, 0x34, 0x38, 0x3C; then 0x40,0x44,0x48,0x4C;
    // 0x50,0x54,0x58,0x5C; 0x60,0x64,0x68,0x6C; and finally 0x70,0x74,0x78,0x7C.
    // For simplicity, initialize all fields from +0x30 to +0x7F to zero.
    // (Indices 0xC through 0x1F inclusive)
    int* base = (int*)((int)this + 0x30);
    for (int i = 0; i < 20; ++i) {
        base[i] = 0;
    }

    return;
}