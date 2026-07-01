// FUNC_NAME: DataStreamReader::readNamedProperties
void __thiscall DataStreamReader::readNamedProperties(int thisPtr, int streamHandle)
{
    char tokenType;
    int streamPos;
    int value;

    initStreamReader(streamHandle);
    setStreamContext(streamHandle, 0xed3e2b73); // Magic constant for this property set

    while (!isStreamAtEnd()) {
        streamPos = readNextToken(); // advance and get position
        tokenType = getTokenType();

        if (tokenType == 0) {
            // String/value type
            readNextToken();
            value = readTokenValue();            // e.g. read int/string ref
            value = resolveDataReference(value); // 0x004dafd0
            *(int *)(thisPtr + 0x5c) = value;   // field2
        }
        else if (tokenType == 1) {
            // Integer type
            streamPos = readNextToken();
            *(int *)(thisPtr + 0x58) = *(int *)(streamPos + 8); // field1
        }
        else if (tokenType == 2) {
            // Another integer type
            streamPos = readNextToken();
            *(int *)(thisPtr + 0x60) = *(int *)(streamPos + 8); // field3
        }
        endTokenBlock();
    }
}
// Known offsets: this+0x58, this+0x5c, this+0x60 are property fields.
// Stream format: magic = 0xed3e2b73; tokens encode types 0,1,2.