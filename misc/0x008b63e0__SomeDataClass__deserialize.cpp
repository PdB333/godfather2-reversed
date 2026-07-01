// FUNC_NAME: SomeDataClass::deserialize
// Address: 0x008b63e0
// Role: Deserializes this object from a binary stream (tokens 0-6) into member fields.

void __thiscall SomeDataClass::deserialize(int thisPtr, int streamPtr)
{
    char hasData;
    int tokenType;
    int intValue;
    float floatValue;

    streamInit(streamPtr);                     // Initialize stream for reading
    streamReadToken(streamPtr, 0x22f2995b);    // Seek to specific token/hash
    hasData = streamHasMoreTokens(streamPtr);  // Check if data remains

    while (hasData == 0) {
        beginToken(streamPtr);                 // Start reading a token
        tokenType = readTokenType(streamPtr);  // Get token type (0-6)
        
        switch (tokenType) {
        case 0:
            beginToken(streamPtr);
            intValue = readInt(streamPtr);
            setIntField(thisPtr + 0x50, intValue);  // m_field1
            break;
        case 1:
            beginToken(streamPtr);
            intValue = readInt(streamPtr);
            setIntField(thisPtr + 0x58, intValue);  // m_field2
            break;
        case 2:
            // Read float directly
            beginToken(thisPtr + 0x60);
            readFloat(thisPtr + 0x60);               // m_field3 (float)
            break;
        case 3:
            beginToken(streamPtr);
            intValue = readInt(streamPtr);            // Actually reads a string then converts
            intValue = stringToInt(intValue);
            *(int *)(thisPtr + 0x74) = intValue;     // m_field5
            break;
        case 4:
            beginToken(streamPtr);
            intValue = readInt(streamPtr);
            intValue = stringToInt(intValue);
            *(int *)(thisPtr + 0x70) = intValue;     // m_field4
            break;
        case 5:
            beginToken(thisPtr + 0x78);
            readFloat(thisPtr + 0x78);               // m_field6 (float)
            break;
        case 6:
            // Token 6: reads an int from a stream pointer returned by beginToken
            intValue = beginToken(streamPtr);
            *(int *)(thisPtr + 0x88) = *(int *)(intValue + 8); // m_field7
            break;
        }
        
        endToken(streamPtr);
        hasData = streamHasMoreTokens(streamPtr);
    }
}