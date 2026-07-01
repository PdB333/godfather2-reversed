// FUNC_NAME: DataLoader::loadFromStream

void __thiscall DataLoader::loadFromStream(void* this, void* stream)
{
    // Initialize stream reader
    beginRead(stream);
    // Verify magic number
    checkMagic(stream, 0xFF04E3AE);

    // Process elements until end of data
    while (!isEndOfData())
    {
        // Read next token type
        int tokenType = readTokenType();

        switch (tokenType)
        {
            case 0:
            {
                // String element: read and store at offset +0x50
                readToken(); // consume prefix
                char* str = readString();
                setText(reinterpret_cast<void*>(reinterpret_cast<int>(this) + 0x50), str);
                break;
            }
            case 1:
            {
                // Container element: read sub-block into offset +0x58
                int subBlock = reinterpret_cast<int>(this) + 0x58;
                readToken(subBlock);  // initialize sub-reader
                readSubBlock(subBlock);
                break;
            }
            case 2:
            {
                // Another container element: read sub-block into offset +0x68
                int subBlock = reinterpret_cast<int>(this) + 0x68;
                readToken(subBlock);
                readSubBlock(subBlock);
                break;
            }
            case 3:
            {
                // Value element: read integer and store at offset +0x7c
                int tokenData = readToken();
                *(reinterpret_cast<int*>(reinterpret_cast<int>(this) + 0x7c)) = *(reinterpret_cast<int*>(tokenData + 8));
                break;
            }
            case 4:
            {
                // Boolean element: set flag bit 0 at offset +0x78
                int tokenData = readToken();
                if (*(reinterpret_cast<int*>(tokenData + 8)) == 0)
                {
                    *(reinterpret_cast<char*>(reinterpret_cast<int>(this) + 0x78)) &= ~1;
                }
                else
                {
                    *(reinterpret_cast<char*>(reinterpret_cast<int>(this) + 0x78)) |= 1;
                }
                break;
            }
            case 5:
            {
                // Boolean element: set flag bit 1 at offset +0x78
                int tokenData = readToken();
                if (*(reinterpret_cast<int*>(tokenData + 8)) == 0)
                {
                    *(reinterpret_cast<char*>(reinterpret_cast<int>(this) + 0x78)) &= ~2;
                }
                else
                {
                    *(reinterpret_cast<char*>(reinterpret_cast<int>(this) + 0x78)) |= 2;
                }
                break;
            }
        }

        // Skip to end of current element
        skipToken();
    }
}