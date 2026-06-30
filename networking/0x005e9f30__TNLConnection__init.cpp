// FUNC_NAME: TNLConnection::init
int __fastcall TNLConnection::init(TNLConnection* this)
{
    // +0x1c: set to some global sentinel (likely invalid/initial sequence)
    int sentinel = DAT_00e2b1a4;
    this->m_connectionSentinel = sentinel; // +0x1c

    // +0xa8: a flag or pointer, zeroed
    this->field_0xa8 = 0; // +0xa8

    // Array of 16 packet slots starting at +0x24, each slot is 8 bytes:
    // slot[0]: [0x24]=sentinel, [0x28]=0
    // slot[1]: [0x2c]=sentinel, [0x30]=0, etc.
    // total 0x10 (16) iterations, covering offsets 0x24 to 0xA3
    PacketSlot* slots = reinterpret_cast<PacketSlot*>( (char*)this + 0x24 );
    for (int i = 0; i < 0x10; i++)
    {
        slots[i].m_sequence = sentinel;   // first dword of slot
        slots[i].m_flags    = 0;          // second dword
    }

    // Fields after the array:
    this->field_0xa0 = 0; // +0xa0 (last slot's second dword? but overwritten)
    this->field_0xa4 = 0; // +0xa4 (just after array)
    this->field_0xbc = 0; // +0xbc
    this->field_0xc0 = 0; // +0xc0
    this->field_0xc4 = 0; // +0xc4
    this->field_0xc8 = 0; // +0xc8 (200 decimal)
    this->field_0xcc = 0; // +0xcc
    this->field_0xd0 = 0; // +0xd0
    this->field_0xd4 = 0; // +0xd4
    this->field_0xd8 = 0; // +0xd8
    this->field_0xdc = 0; // +0xdc
    this->field_0xe0 = 0; // +0xe0
    this->field_0xe8 = 0; // +0xe8

    // Call sub-initializers
    FUN_005ef9a0(); // likely another init routine
    FUN_005ef890(); // secondary init
    FUN_005e9fe0(); // final init

    return static_cast<int>(this);
}