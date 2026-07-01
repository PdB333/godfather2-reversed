// FUNC_NAME: DataBlockReader::readFields
void __thiscall DataBlockReader::readFields(int this, void* stream)
{
    char hasMore;
    int tokenType;
    int valueInt;
    int ptr;

    FUN_0046c710(stream); // possibly init stream reader
    FUN_0043aff0(stream, 0x98525e6d); // read magic/hash header
    hasMore = FUN_0043b120(); // check if more data available
    while (hasMore == '\0') // while data remains
    {
        FUN_0043b210(); // read next token header?
        tokenType = FUN_0043ab70(); // get token type (0-4)
        switch(tokenType)
        {
        case 0: // integer read
            ptr = FUN_0043b210(); // read token value
            *(undefined4 *)(this + 0x54) = *(undefined4 *)(ptr + 8); // +0x54: m_typeId
            break;
        case 1: // string read
            FUN_0043b210(); // read token
            valueInt = FUN_0043ab90(); // get string handle or index
            FUN_004089b0(this + 0x5c, valueInt); // +0x5c: m_name
            break;
        case 2: // another string
            FUN_0043b210();
            valueInt = FUN_0043ab90();
            FUN_004089b0(this + 100, valueInt); // +0x64: m_description
            break;
        case 3: // integer
            ptr = FUN_0043b210();
            *(undefined4 *)(this + 0x58) = *(undefined4 *)(ptr + 8); // +0x58: m_flags
            break;
        case 4: // string
            FUN_0043b210();
            valueInt = FUN_0043ab90();
            FUN_00408980(this + 0x6c, valueInt); // +0x6c: m_icon
            break;
        }
        FUN_0043b1a0(); // skip/advance to next token
        hasMore = FUN_0043b120(); // check again
    }
    return;
}