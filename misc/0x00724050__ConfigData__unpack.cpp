// FUNC_NAME: ConfigData::unpack

void __thiscall ConfigData::unpack(void* thisPtr, Stream& stream)
{
    // Initialize stream with key (a check hash or seed)
    stream.beginRead();               // FUN_0043b540
    stream.setKey(0xa6bca73c);        // FUN_0043aff0 - some magic constant

    // Process until end of stream
    char bEnd;
    while ((bEnd = stream.isEnd()) == '\0')   // FUN_0043b120
    {
        // Read type identifier (0..5 in observed data)
        int type = stream.readType();          // FUN_0043ab70

        // Read a value node and extract the integer at offset 8
        void* valueNode = stream.readNode();   // FUN_0043b210
        int value = *(int*)((char*)valueNode + 8); // +0x8 is the value field within the node

        // Store value into the settings array based on type
        switch (type)
        {
        case 0:
            *(int*)((char*)thisPtr + 0x44) = value; // field[0]
            break;
        case 1:
            *(int*)((char*)thisPtr + 0x48) = value; // field[1]
            break;
        case 2:
            *(int*)((char*)thisPtr + 0x4c) = value; // field[2]
            break;
        case 3:
            *(int*)((char*)thisPtr + 0x50) = value; // field[3]
            break;
        case 4:
            *(int*)((char*)thisPtr + 0x54) = value; // field[4]
            break;
        case 5:
            *(int*)((char*)thisPtr + 0x58) = value; // field[5]
            break;
        // Other types ignored (no default case in original)
        }

        // Advance stream to next entry
        stream.advance();               // FUN_0043b1a0
    }
}