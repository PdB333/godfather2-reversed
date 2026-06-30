// FUNC_NAME: PacketHeader::init
// Function address: 0x00710e30
// Initializes a packet header structure with magic values and flags.
// Structure fields (offsets in bytes):
// +0x00: flags (uint32) - initially 0, then OR'd with 0x90 (bit7 and bit4 set)
// +0x04: field1 (uint32) - set to global constant DAT_00d5efa8 (probably version/type)
// +0x08: field2 (uint32) - set to 0
// +0x0C: field3 (uint32) - magic 0xbadbadba
// +0x10: field4 (uint32) - magic 0xbeefbeef
// +0x14: field5 (uint32) - magic 0xeac15a55
// +0x18: field6 (uint32) - magic 0x91100911
// Called from FUN_00718750 (likely packet allocation function)

void __thiscall PacketHeader::init(PacketHeader* this)
{
    uint uVar1;
    
    uVar1 = DAT_00d5efa8;                // Get global constant (likely packet type/version)
    this->flags = 0;                     // Clear flags
    this->field1 = uVar1;                // Set version/type field
    this->field3 = 0xbadbadba;           // Sentinel magic
    this->field4 = 0xbeefbeef;           // Sentinel magic
    this->field5 = 0xeac15a55;           // EARS engine magic ("EA C15A55"?)
    this->field6 = 0x91100911;           // Sentinel magic
    this->flags = this->flags | 0x90;    // Set bits 4 and 7 (0x80+0x10) - packet flags?
    this->field2 = 0;                    // Zero additional field
    return;
}