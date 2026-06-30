// FUNC_NAME: BinaryStreamParser::parseProperties
void __thiscall BinaryStreamParser::parseProperties(int thisObj, undefined4 streamHandle)
{
    char isEOF;
    int tokenIdx;
    undefined4 *tokenBlockPtr;
    undefined4 tokenBlock[32]; // size depends on struct, but approximated
    undefined4 compactBlock[32];
    
    // Initialize stream: open, verify first magic, set endianness
    Stream::open(streamHandle);
    Stream::checkMagic(streamHandle, 0xb390b11a);
    Stream::setEndian(1);
    
    // Prepare token block pointer and initial fill
    tokenBlockPtr = &tokenBlock[3]; // points to local_120 from decompiled
    tokenBlock[0] = 0;
    tokenBlock[4] = 0;
    tokenBlock[8] = 0;
    tokenBlock[12] = gSeedValue; // _DAT_00d5780c
    
    // Read token block from stream
    Stream::readTokenBlock(tokenBlockPtr);
    Stream::skipPadding(tokenBlockPtr);
    
    // Compact and copy to object's buffer at offset +0x60
    compactBlock[0] = tokenBlock[0];
    compactBlock[1] = tokenBlock[1];
    compactBlock[2] = tokenBlock[2];
    compactBlock[3] = 0;
    compactBlock[4] = tokenBlock[4];
    compactBlock[5] = 0;
    compactBlock[6] = 0;
    compactBlock[7] = tokenBlock[7];
    compactBlock[8] = tokenBlock[8];
    compactBlock[9] = tokenBlock[9];
    compactBlock[10] = tokenBlock[10];
    compactBlock[11] = tokenBlock[11];
    compactBlock[12] = tokenBlock[12];
    compactBlock[13] = tokenBlock[13];
    compactBlock[14] = tokenBlock[14];
    compactBlock[15] = gSeedValue; // _DAT_00d5780c
    Stream::copyData(&compactBlock, thisObj + 0x60);
    
    // Check closing magic
    Stream::checkMagic(streamHandle, 0x3782a961);
    
    // Parse token entries until EOF
    isEOF = Stream::eof(streamHandle);
    while (isEOF == 0) {
        Stream::readTokenBlock();
        tokenIdx = Stream::getTokenType();
        if (tokenIdx == 0) {
            Stream::readTokenBlock();
            *(uint32_t *)(thisObj + 0xa0) = *(uint32_t *)(tokenBlock + 2); // tokenBlock+8 in decompiled, but offset unknown
        }
        else if (tokenIdx == 1) {
            Stream::readTokenBlock();
            *(uint32_t *)(thisObj + 0xa4) = *(uint32_t *)(tokenBlock + 2);
        }
        Stream::advanceToken();
        isEOF = Stream::eof(streamHandle);
    }
    return;
}