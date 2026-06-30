// FUNC_NAME: ResourceLoader::readBinaryData
void __thiscall ResourceLoader::readBinaryData(void* streamPtr) {
    // Initialize stream and verify hash
    readHeader(streamPtr);
    checkHash(streamPtr, 0x29306bd5);

    // Main parse loop: read tokens until end
    while (!isEndOfData()) {
        nextToken(); // Advance to next token
        int tokenType = getTokenType();
        switch (tokenType) {
            case 0: {
                // Token type 0: add value to list at 0x50
                nextToken();
                int value = getTokenValue();
                addToList(m_someList, value); // +0x50: list pointer
                break;
            }
            case 1: {
                // Token type 1: nested block using sub-loader at 0x58
                int* subLoader = reinterpret_cast<int*>(m_subLoader); // +0x58
                nextToken(subLoader);
                readSubData(subLoader);
                break;
            }
            case 2: {
                // Token type 2: read value into 0x68
                int* dataPtr = reinterpret_cast<int*>(nextToken());
                m_value1 = *(dataPtr + 2); // +0x68
                break;
            }
            case 3: {
                // Token type 3: read value into 0x6c
                int* dataPtr = reinterpret_cast<int*>(nextToken());
                m_value2 = *(dataPtr + 2); // +0x6c
                break;
            }
            case 4: {
                // Token type 4: read value into 0x70
                int* dataPtr = reinterpret_cast<int*>(nextToken());
                m_value3 = *(dataPtr + 2); // +0x70
                break;
            }
        }
        endToken(); // Close current token
    }
}