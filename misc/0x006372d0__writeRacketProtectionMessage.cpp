// FUNC_NAME: writeRacketProtectionMessage
// Address: 0x006372d0
// Writes a message containing property racket protection data to a binary stream.
// The stream object is expected in ESI: +0 = base object, +4 = write function pointer, +8 = write parameter.
// Message format: 4-byte constant, 1-byte opcode (0x50), 9 protection levels, 4-byte property ID.

void writeRacketProtectionMessage(void)
{
    // Extract stream components from ESI
    void* baseObj = *unaff_ESI;                                                  // +0x00
    auto writeFunc = (void (*)(void*, const void*, int, int))unaff_ESI[1];       // +0x04
    int writeParam = unaff_ESI[2];                                               // +0x08

    uint8_t byteBuf;
    uint32_t wordBuf;

    // Write 4-byte magic constant (likely message header or signature)
    wordBuf = DAT_00e4151c;  // Global constant, purpose unknown
    writeFunc(baseObj, &wordBuf, sizeof(wordBuf), writeParam);

    // Write message type identifier
    byteBuf = 0x50;          // Opcode for racket protection update
    writeFunc(baseObj, &byteBuf, sizeof(byteBuf), writeParam);

    // Write 9 protection level bytes (one per racket type)
    byteBuf = 1;             // Racket protection level #0
    writeFunc(baseObj, &byteBuf, sizeof(byteBuf), writeParam);
    byteBuf = 4;             // Level #1
    writeFunc(baseObj, &byteBuf, sizeof(byteBuf), writeParam);
    byteBuf = 4;             // Level #2
    writeFunc(baseObj, &byteBuf, sizeof(byteBuf), writeParam);
    byteBuf = 4;             // Level #3
    writeFunc(baseObj, &byteBuf, sizeof(byteBuf), writeParam);
    byteBuf = 6;             // Level #4
    writeFunc(baseObj, &byteBuf, sizeof(byteBuf), writeParam);
    byteBuf = 8;             // Level #5
    writeFunc(baseObj, &byteBuf, sizeof(byteBuf), writeParam);
    byteBuf = 9;             // Level #6
    writeFunc(baseObj, &byteBuf, sizeof(byteBuf), writeParam);
    byteBuf = 9;             // Level #7
    writeFunc(baseObj, &byteBuf, sizeof(byteBuf), writeParam);
    byteBuf = 4;             // Level #8
    writeFunc(baseObj, &byteBuf, sizeof(byteBuf), writeParam);

    // Write 4-byte property ID (or family ID) from global variable
    wordBuf = DAT_00e4471c;  // Global storing current property identifier
    writeFunc(baseObj, &wordBuf, sizeof(wordBuf), writeParam);
}