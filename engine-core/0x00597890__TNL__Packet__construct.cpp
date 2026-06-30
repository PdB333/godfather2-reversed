// FUNC_NAME: TNL::Packet::construct

unsigned int __thiscall TNL::Packet::construct(void *this, unsigned int unkParam, int sequenceParam)
{
    // Compute a 16-bit sequence number from the given parameter
    unsigned short sequence = (unsigned short)(sequenceParam * 0x14 + 0xC);
    
    // Local constant: packet type identifier (0x202 = 514)
    unsigned int packetType = 0x202;
    
    // Another constant (maybe flags or sub-type)
    unsigned int flags = 2;
    
    // First call to the global write function (initializes stream?)
    // Assumes a function pointer stored at 0x01205590 + 0x10
    (*(void (*)())(*(int*)0x01205590 + 0x10))();
    
    // Reset flags to 2 (perhaps for safety)
    flags = 2;
    
    // Write 2-byte value 'flags' at offset +2
    void *field2 = (char*)this + 2;
    (*(void (*)(void*, void*))(*(int*)0x01205590 + 0x10))(field2, &flags);
    
    int copyLength = 4;
    
    // Write 4-byte 'packetType' at offset +4
    (*(void (*)(void*, void*, int))(*(int*)0x01205590 + 0x10))((char*)this + 4, &packetType, 4);
    
    // Write 2-byte 'flags' at offset +8
    (*(void (*)(void*, void*))(*(int*)0x01205590 + 0x10))((char*)this + 8, &flags);
    
    // Copy 0x50 bytes (80) from offset +2 to offset +0xC (duplicate header data)
    (*(void (*)(void*, void*, int))(*(int*)0x01205590 + 0x10))((char*)this + 0xC, field2, copyLength * 0x14);
    
    // Return total packet size (0x5C = 92 bytes)
    return 0x5C;
}