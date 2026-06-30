// FUNC_NAME: NetworkPacketBuffer::initNode
void __fastcall initPacketBufferNode(undefined4 unused, uint32* buffer, uint32** outPtr)
{
    int i;
    uint32* cur;

    // Set internal pointers and zero a 512-byte working area (0x80*4)
    buffer[3] = (uint32)(buffer + 0xD);            // +0x0C: pointer to data area start
    cur = buffer + 0xD;
    for (i = 0x80; i != 0; i--) {
        *cur = 0;
        cur++;
    }

    // +0x10: pointer to area past the zeroed block (offset 0x234)
    buffer[4] = (uint32)(buffer + 0x8D);
    // Write magic signature at that location
    buffer[0x8D] = 0x7DCC;

    // Copy magic to first field (offset 0x00)
    buffer[0] = *(uint32*)buffer[4];

    // Clear two fields near the signature block
    ((uint32*)buffer[4])[2] = 0;                   // offset 0x08 from signature
    *(uint32*)(buffer[4] + 4) = 0;                 // offset 0x04 from signature

    // Zero two more fields
    buffer[5] = 0;                                  // +0x14
    buffer[6] = 0;                                  // +0x18

    // Return the buffer pointer
    *outPtr = buffer;
}