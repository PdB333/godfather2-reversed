// FUNC_NAME: NetSession::processMessageHeader
void NetSession::processMessageHeader(void* buffer)
{
    int size;
    char flags;
    char hasSubData;
    
    size = buffer;
    handleBuffer(buffer); // FUN_00853430
    uint word = *(ushort*)(size + 6);
    writeWord(0x10, &word); // FUN_0064b810
    flags = readByte(*(byte*)(size + 8)); // FUN_0064bb50
    hasSubData = readByte(*(byte*)(size + 9)); // FUN_0064bb50
    if (hasSubData != '\0') {
        copyData(this, size + 0xc); // FUN_004a9cf0
        word = *(ushort*)(size + 6);
        writeWord(0x10, &word); // FUN_0064b810
        return;
    }
    word = *(ushort*)(size + 4);
    writeWord(0x10, &word); // FUN_0064b810
    return;
}