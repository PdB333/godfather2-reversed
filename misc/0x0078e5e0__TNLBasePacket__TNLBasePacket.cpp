// FUNC_NAME: TNLBasePacket::TNLBasePacket
undefined4 * __thiscall TNLBasePacket::TNLBasePacket(undefined4 *this, undefined4 arg)
{
    // Call base class constructor
    FUN_0046c590(arg);
    
    // Set vtable pointer and additional virtual function table pointers
    *this = &PTR_FUN_00d69bbc;                // +0x00: primary vtable
    this[0xf] = &PTR_LAB_00d69bac;            // +0x3C: secondary vtable or interface
    this[0x12] = &PTR_LAB_00d69ba8;           // +0x48: tertiary vtable or callback
    
    // Debug sentinel values (used for memory integrity checking)
    this[0x24] = 0xbadbadba;                  // +0x90: marker
    this[0x25] = 0xbeefbeef;                  // +0x94: marker
    this[0x26] = 0xeac15a55;                  // +0x98: marker
    this[0x27] = 0x91100911;                  // +0x9C: marker
    
    // Initialize synchronization object (event/critical section?)
    FUN_004086b0(&DAT_0120e93c, 0x7fff);      // Dat_0120e93c is likely a global sync object
    
    return this;
}