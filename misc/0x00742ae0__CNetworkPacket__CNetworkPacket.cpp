// FUNC_NAME: CNetworkPacket::CNetworkPacket
// This function appears to be a constructor for a network packet class.
// It initializes a base class with two arguments, sets up a vtable, zeroes a 40-byte buffer,
// and conditionally computes a pointer offset.
// +0x12 (offset 0x48): pointer to data? 
// +0x14 (offset 0x50): computed base pointer (data - 0x48)
// +0x15..0x1e (offset 0x54..0x78): fields zeroed

void __thiscall CNetworkPacket::CNetworkPacket(CNetworkPacket *this, int arg1, int arg2) {
    // Call base class constructor
    FUN_004ac120(arg1, arg2);
    
    // Set vtable pointer
    *this = &PTR_LAB_00d63bdc;
    
    // Zero out fields at offsets 0x15 through 0x1e (relative to int pointer)
    this[0x15] = 0;
    this[0x16] = 0;
    this[0x17] = 0;
    this[0x18] = 0;
    this[0x19] = 0;
    this[0x1a] = 0;
    this[0x1b] = 0;
    this[0x1c] = 0;
    this[0x1d] = 0;
    this[0x1e] = 0;
    
    // Conditionally compute pointer at offset 0x14 as (pointer at 0x12 - 0x48)
    int baseOffset = 0;
    if (this[0x12] != 0) {
        baseOffset = this[0x12] - 0x48;
    }
    this[0x14] = baseOffset;
}