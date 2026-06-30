// FUNC_NAME: EA::Net::MessageStream::buildHeader
int __thiscall MessageStream::buildHeader(void)
{
    // Global stream object pointer (likely a network packet builder)
    // DAT_01205590 = global stream vtbl
    // Vtable offset 0x10 points to write method (writeData)
    struct Stream {
        void (*writeData)(void *this, void *data, uint size);
    };
    extern Stream *gStream;

    // Write message type (0x801 = eMsgType?)
    ushort messageType = 0x801;
    gStream->writeData(this, &messageType, 2);

    // Write zero (empty field?)
    ushort empty = 0;
    gStream->writeData(this, &empty, 2);

    // Write size of following data (4 bytes of flags?)
    uint flagsSize = 4;
    gStream->writeData(this, &flagsSize, 4);

    // Write bool: isSelf? (derived from this pointer non-zero)
    bool isSelf = (this != 0) ? 1 : 0;
    gStream->writeData(this, &isSelf, 4);

    // Write bool: from return address check (always true)
    bool secondFlag = true; // Based on return address non-zero
    gStream->writeData(this, &secondFlag, 4);

    // Write data from object offsets
    gStream->writeData((char*)this + 0xC, (void*)&this, 4); // Possibly object ID
    // Write another bool at offset 0x10
    bool flagAt10 = (*(uint*)(&secondFlag) != 0); // Always true
    gStream->writeData((char*)this + 0x10, &flagAt10, 4);

    return 0x14; // Total size written (20 bytes)
}