// FUNC_NAME: Entity::deserializeFromStream

void __thiscall Entity::deserializeFromStream(int this, void* bitStream)
{
    char isEnd;
    int tokenType;
    int tokenValue;
    int tokenData;

    bitStreamInit(bitStream);                                 // initialize bitstream reader
    bitStreamSetMagic(bitStream, 0x4f5ece85);                 // set magic number for validation
    isEnd = bitStreamIsEnd(bitStream);                        // check if stream is already at end

    do {
        if (isEnd != '\0') {
            return;                                           // exit when end of stream
        }

        // read the next token header
        bitStreamReadTokenHeader(bitStream);                  // advance to next token, may return pointer but unused here

        tokenType = bitStreamReadTokenType(bitStream);        // token type determines field to set

        switch (tokenType) {
        case 0:
            // token type 0: reads an integer value and stores it at this+0x50
            bitStreamReadTokenHeader(bitStream);               // read sub-token?
            tokenValue = bitStreamReadTokenValue(bitStream);   // get integer value
            setFieldAtOffset(this + 0x50, tokenValue);         // set field at offset 0x50
            break;

        case 1:
            // token type 1: similar but stores at this+0x58
            bitStreamReadTokenHeader(bitStream);
            tokenValue = bitStreamReadTokenValue(bitStream);
            setFieldAtOffset(this + 0x58, tokenValue);
            break;

        case 2:
            // token type 2: reads a substream into the object at this+0x60
            bitStreamReadSubStreamInto(bitStream, this + 0x60);
            break;

        case 3:
            // token type 3: reads a token and copies its offset+8 into this+0x8c
            tokenData = bitStreamReadTokenData(bitStream);      // returns pointer to token data
            *(int*)(this + 0x8c) = *(int*)(tokenData + 8);     // copy from token data + 8
            break;

        case 4:
            // token type 4: similar, stores into this+0x74
            tokenData = bitStreamReadTokenData(bitStream);
            *(int*)(this + 0x74) = *(int*)(tokenData + 8);
            break;

        case 5:
            // token type 5: reads an integer value and passes it to some processing function
            bitStreamReadTokenHeader(bitStream);
            tokenValue = bitStreamReadTokenValue(bitStream);
            processValue(tokenValue);                          // possibly a callback or event
            break;

        case 6:
            // token type 6: reads a substream into the object at this+0x90
            bitStreamReadSubStreamInto(bitStream, this + 0x90);
            break;
        }

        bitStreamAdvanceToNextToken(bitStream);                // advance to next token
        isEnd = bitStreamIsEnd(bitStream);                     // check for end after advancing
    } while (true);
}