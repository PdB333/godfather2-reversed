// FUNC_NAME: Connection::readPacketByte
unsigned char Connection::readPacketByte(Connection* const this)
{
    // Validate packet magic number (0x4ecfbe13)
    FUN_0043aff0(this, 0x4ecfbe13);
    // Set packet read state to 3 (data body mode)
    FUN_0043af00(3);
    char isBufferComplete = FUN_0043b120();
    if (isBufferComplete == '\0') {
        int bufferPtr = FUN_0043b210(); // get current read pointer
        return *(unsigned char*)(bufferPtr + 8); // read byte at offset 8 (data start)
    }
    return 0xFF; // error or end-of-stream marker
}