// FUNC_NAME: NetObject::writeUpdate
void __thiscall NetObject::writeUpdate(int connection) // connection is likely a GameConnection
{
    // local_404: buffer for serialization (1028 bytes)
    // local_52c: mask/size (0x400)
    // local_510, local_50c: maximum sizes (0x2000)
    undefined1 buffer[1028];    // +0x00
    undefined4 maxSize;         // at local_510
    undefined4 maxSize2;        // at local_50c
    undefined4 writeOffset;     // at local_538
    undefined4 readOffset;      // at local_534
    int4 bitMask;               // at local_52c (0x400)
    undefined1 flags;           // at local_528
    undefined4 someFlag;        // at local_524
    undefined1 flag2;           // at local_520
    undefined1 flag3;           // at local_51f
    undefined1 zeroByte;        // at local_504
    undefined4 someVal;         // at local_508
    undefined** pGlobalString;  // local_53c = &PTR_LAB_00e42f38
    undefined1 streamType;      // local_541 = 2

    char* pBuffer = buffer;     // +0x530
    maxSize = 0x2000;
    maxSize2 = 0x2000;
    writeOffset = 0;
    readOffset = 0;
    bitMask = 0x400;
    flags = 0;
    someFlag = 0;
    flag2 = 0;
    flag3 = 0;
    zeroByte = 0;
    someVal = 0;
    pGlobalString = &PTR_LAB_00e42f38; // global null string?
    streamType = 2;

    // Initialize the bitstream with type 2?
    FUN_0064b810(8, &streamType);   // possibly BitStream::init(8, streamType)

    // Read a byte from this+0x198 (character index or id)
    FUN_0064bb50((char)this->field_0x198); // field at offset 0x198, maybe m_objId

    // Read an int from this+0xA4 (position, angle, etc.)
    int field0xA4 = this->field_0xA4; // offset 0xA4
    FUN_0064b810(0x20, &field0xA4);

    // Get total size from vtable[0] (likely getDynamicSize())
    int dynamicSize = (this->vtable[0])();

    // Copy dynamicSize + 0x20 bytes? Actually calls FUN_0064c760(dynamicSize + 0x20, 0xff)
    FUN_0064c760(dynamicSize + 0x20, 0xff); // maybe memset with 0xff?

    // Call vtable[17] (writeUpdate?) with pointer to global string
    (this->vtable[17])(&pGlobalString);

    // Call vtable[8] (writePack?) with pointer to field0xA4
    (this->vtable[8])(&field0xA4);

    // Increment sequence counter at this+0x19C
    this->field_0x19C++; // m_sequence

    // Copy ack sequence from connection+100 to this+0x1A0
    this->field_0x1A0 = *(int*)(connection + 100); // m_ackSequence

    // Copy 0x80 bytes from connection+0x5c into a small buffer (8 bytes?)
    // Actually FUN_00658230(connection+0x5c, auStack_40c, (0x400+7)>>3, 1)
    // (0x400+7)>>3 = 0x80 (128 bytes) but auStack_40c is only 8? Maybe it's a pointer to a buffer?
    undefined1 smallBuffer[8]; // auStack_40c
    FUN_00658230(connection + 0x5c, smallBuffer, 0x80, 1); // likely memcpy or read

    // Finalize stream?
    FUN_0064b440();
}