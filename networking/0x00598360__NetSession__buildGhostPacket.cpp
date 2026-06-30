// FUNC_NAME: NetSession::buildGhostPacket
int buildGhostPacket(int param_1, int param_2, const char* param_3)
{
    // Global binary writer (vtable at DAT_01205590)
    Writer* writer = *(Writer**)(DAT_01205590);
    
    // Write packet header: magic = 0x600, version = 0x54
    writer->writeUint32(0x600);
    writer->writeUint32(0x54);
    
    // Write param_2 as a 2-byte field at offset 2 (relative to buffer start)
    writer->writeShortAt(writer->buffer + 2, param_2);
    
    // Write 4-byte field at offset 4 (value from stack buffer, unknown)
    writer->writeIntAt(writer->buffer + 4, 0);
    
    // Check available space; if > 63, error
    if (writer->getSpaceLeft() > 63) {
        writer->onError();
    }
    
    // Write param_2 again at offset 8 (as 4 bytes)
    writer->writeIntAt(writer->buffer + 8, param_2);
    
    // Zero out 12 bytes at offset 0x48
    writer->writeBlock(writer->buffer + 0x48, 12, 0);
    
    // Write sub-packet header: type = 0x603, size = 0x38
    writer->writeShortAt(writer->buffer + 0x54, 0x603);
    writer->writeShortAt(writer->buffer + 0x56, 0x0c);
    
    // Write pointer to self? (offset 4 as a pointer)
    writer->writeIntAt(writer->buffer + 0x58, (int)(writer->buffer + 4));
    
    // Write null pointer
    writer->writeIntAt(writer->buffer + 0x5c, 0);
    
    // Write string parameter (length up to 31 characters + null)
    int strLen = writer->getStringLength(param_3);
    if (strLen > 31) {
        writer->onError();
    }
    writer->writeStringAt(writer->buffer + 0x60, param_3, strLen + 1);
    
    // Write padding: 12 bytes of value 2
    writer->writePaddedAt(writer->buffer + 0x80, 2, 12);
    
    // Return total packet size (140 bytes)
    return 0x8c;
}