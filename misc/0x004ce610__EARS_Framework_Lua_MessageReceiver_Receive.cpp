// Xbox PDB: EARS::Framework::Lua::MessageReceiver::Receive
// FUNC_NAME: MessageReceiver::processReceivedString
void __thiscall MessageReceiver::processReceivedString(int thisPtr, const char* messageType, const char* messageBody, int value) {
    // Access logger (member at +0x2c)
    int logger = *(int*)(thisPtr + 0x2c);
    // Log the start of this handler with a fixed string
    logString(logger, "MessageReceiverReceive");
    // Log the message type string
    logString(logger, messageType);

    // Allocate space for a pending packet/command from buffer manager
    int bufMgr = *(int*)(thisPtr + 0x2c); // same logger object? Actually +0x2c holds a buffer manager? Let's assume it's a buffer manager.
    // Actually the code uses iVar2 = *(int*)(param_1+0x2c) twice; so it's a single object with both logging and buffer management.
    // Let's call it mCommBuffer.
    unsigned int* writePos = (unsigned int*)allocateBuffer(bufMgr, bufMgr + 0x40, *(int*)(bufMgr + 8) + -8, 0);
    int bufPos = *(int*)(bufMgr + 8);
    *(unsigned int*)(bufPos - 8) = *writePos;
    *(unsigned int*)(bufPos - 4) = writePos[1];
    // Now write header: type=3 (event/float), then a float value from member at +0x30
    int bufMgr2 = *(int*)(thisPtr + 0x2c);
    unsigned int* buffer = *(unsigned int**)(bufMgr2 + 8);
    int floatValue = *(int*)(thisPtr + 0x30);
    *buffer = 3;
    buffer[1] = *(unsigned int*)&floatValue; // store as raw bits (float)
    *(int*)(bufMgr2 + 8) += 8; // advance write pointer

    // Log the message body (if non-empty, write it into buffer; if empty, write a null token)
    if (*messageBody == '\0') {
        int bufMgr3 = *(int*)(thisPtr + 0x2c);
        *(unsigned int**)(bufMgr3 + 8)[0] = 0;
        *(int*)(bufMgr3 + 8) += 8;
    } else {
        logString(*(int*)(thisPtr + 0x2c), messageBody);
    }

    // Write the integer value as a token (type=2) or null if zero
    int bufMgr4 = *(int*)(thisPtr + 0x2c);
    if (value == 0) {
        *(unsigned int**)(bufMgr4 + 8)[0] = 0;
    } else {
        unsigned int* buf = *(unsigned int**)(bufMgr4 + 8);
        *buf = 2;
        buf[1] = value;
    }
    *(int*)(bufMgr4 + 8) += 8;

    // Calculate size and send the buffer
    int headerSize = 0x28; // guessed constant
    int currentOffset = *(int*)(*(int*)(thisPtr + 0x2c) + 8);
    int baseOffset = *(int*)(*(int*)(thisPtr + 0x2c) + 0x1c);
    int payloadSize = (currentOffset - headerSize) - baseOffset;
    int localArray[2] = { currentOffset - headerSize, 0 };
    sendBuffer(&LAB_006261e0, localArray, payloadSize); // LAB_006261e0 is probably a format/type string
    flushOutput();
}