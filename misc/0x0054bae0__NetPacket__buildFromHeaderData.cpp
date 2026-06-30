// FUNC_NAME: NetPacket::buildFromHeaderData
void __fastcall NetPacket::buildFromHeaderData(void* thisPtr, undefined4* headerData)
{
    uint* this = (uint*)thisPtr;
    uint temp;
    
    // Global constants (likely sequence/ack numbers or protocol IDs)
    temp = DAT_00e445dc;  // e.g., some network constant
    
    // Set up vtable pointer (class type)
    this[0] = (uint)&PTR_LAB_00e39f00;  // vtable offset +0x00
    
    // Set internal buffer pointer (points to self + 0x20)
    this[4] = (uint)(this + 8);  // +0x10: pointer to data section at +0x20
    
    // Set first data word (from global constant)
    this[1] = temp;  // +0x04: e.g., sequence number
    
    // Set flags/type field
    this[6] = 0x80000008;  // +0x18: flags (maybe indicates type)
    
    // Clear some field
    this[5] = 0;  // +0x14
    
    // Set magic/checksum field (0xfe16702f repeated)
    this[0x6a] = 0xfe16702f;  // +0x1A8: checksum or protocol constant
    
    // Copy 128 bits (4 DWORDs) from header data into packet payload area
    this[0x6c] = headerData[0];  // +0x1B0
    this[0x6d] = headerData[1];  // +0x1B4
    this[0x6e] = headerData[2];  // +0x1B8
    this[0x6f] = headerData[3];  // +0x1BC
    
    // Re-set first data word (redundant, possibly due to compiler optimization)
    this[1] = temp;  // +0x04
    
    // More global constants
    temp = DAT_00e2cd54;  // e.g., another network constant
    this[5] = 0;  // +0x14
    this[0x68] = 0;  // +0x1A0: clear some field
    this[0x69] = temp;  // +0x1A4: set another constant
    this[0x6a] = 0xfe16702f;  // +0x1A8: set magic again
    this[0x6b] = 0;  // +0x1AC: clear checksum/flag
}