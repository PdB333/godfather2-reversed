// FUNC_NAME: NetConnection::writeGameConfigPacket
void NetConnection::writeGameConfigPacket() {
    // Write a DWORD from global config (likely packet type or size)
    writeFunc(mStream, &DAT_00e4151c, 4, mContext);
    
    // Write a series of byte values (sub-opcodes or flags)
    uint8_t byteVal = 0x50;
    writeFunc(mStream, &byteVal, 1, mContext);
    
    byteVal = 1;
    writeFunc(mStream, &byteVal, 1, mContext);
    
    byteVal = 4;
    writeFunc(mStream, &byteVal, 1, mContext);
    
    byteVal = 4;
    writeFunc(mStream, &byteVal, 1, mContext);
    
    byteVal = 4;
    writeFunc(mStream, &byteVal, 1, mContext);
    
    byteVal = 6;
    writeFunc(mStream, &byteVal, 1, mContext);
    
    byteVal = 8;
    writeFunc(mStream, &byteVal, 1, mContext);
    
    byteVal = 9;
    writeFunc(mStream, &byteVal, 1, mContext);
    
    byteVal = 9;
    writeFunc(mStream, &byteVal, 1, mContext);
    
    byteVal = 4;
    writeFunc(mStream, &byteVal, 1, mContext);
    
    // Write another DWORD from global
    writeFunc(mStream, &DAT_00e4471c, 4, mContext);
}

/*
Notes:
- This function is a member of a class (likely NetConnection or similar networking class) based on __thiscall convention (this in ESI).
- The class layout: 
  +0x00: mStream (pointer to output stream/object)
  +0x04: writeFunc (function pointer to write method)
  +0x08: mContext (some context parameter for writeFunc)
- The writeFunc is called with 4 args: stream object, data pointer, size, context.
- The byte sequence and both DWORDs likely form a game configuration or initialization packet.
*/