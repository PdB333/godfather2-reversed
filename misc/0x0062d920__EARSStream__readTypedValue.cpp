// FUNC_NAME: EARSStream::readTypedValue
void EARSStream::readTypedValue() {
    // Offsets:
    // +0x8: m_outputPos (write pointer, points to current output slot)
    // +0xc: m_inputPos (read pointer, points to current input token)
    // +0x10: m_buffer (pointer to buffer descriptor struct)
    //   buffer +0x20: buffer capacity (in bytes?)
    //   buffer +0x24: buffer used size
    // Each token is 8 bytes: 4-byte type, 4-byte value (or pair)

    int* tokenTypePtr = reinterpret_cast<int*>(*(int*)(this + 0xc) + 8); // advance 8? Actually this is wrong: The decompiled gets piVar3 from (param_1+0xc) + 8, so it's reading the second field of the input token? Let's follow original.
    // Original: piVar3 = (int *)(*(int *)(param_1 + 0xc) + 8);
    // That means it takes the pointer stored at this+0xc, adds 8 (to get the value part of the current token?), then casts to int*.
    float lookahead = DAT_00e2b1a4; // constant, likely 0.0f
    int* inputPos = reinterpret_cast<int*>(*(int*)(this + 0xc));
    int* outputPos = reinterpret_cast<int*>(*(int*)(this + 0x8));
    if ((inputPos < outputPos) && (inputPos != nullptr) && (*inputPos > 0)) {
        // If there is a valid token (type > 0), peek the float value that follows
        lookahead = readFloat(); // FUN_00628080 returns a float from stream
    }

    // Re-read input pointer after potential advance
    inputPos = reinterpret_cast<int*>(*(int*)(this + 0xc));
    outputPos = reinterpret_cast<int*>(*(int*)(this + 0x8));
    int checkFlag = static_cast<int>(lookahead);
    // 64-bit composite: high part = outputPos, low part = inputPos
    uint64_t composite = (static_cast<uint64_t>(reinterpret_cast<uintptr_t>(outputPos)) << 32) |
                          static_cast<uint64_t>(reinterpret_cast<uintptr_t>(inputPos));
    int* compositeHigh = reinterpret_cast<int*>(static_cast<uintptr_t>(composite >> 32));
    int* compositeLow  = reinterpret_cast<int*>(static_cast<uintptr_t>(composite & 0xffffffff));

    // Error condition: if no valid token or token is -1
    if ((outputPos <= inputPos) || (inputPos == nullptr) || (*inputPos == -1)) {
        composite = reportError(this, 1, "value expected"); // FUN_00627a20 returns a 64-bit composite value
        checkFlag = _ECX; // extraout_ECX – likely the flag passed through register
        compositeHigh = reinterpret_cast<int*>(static_cast<uintptr_t>(composite >> 32));
        compositeLow  = reinterpret_cast<int*>(static_cast<uintptr_t>(composite & 0xffffffff));
    }

    // Now compositeLow points to current token, compositeHigh to output position? Actually after error, compositeHigh might be updated.
    // Check for "value" tokens: type 4 (float?) or 3 (int?) and checkFlag non-zero (meaning a float value was read)
    if ((compositeLow < compositeHigh) && (compositeLow != nullptr) &&
        ((*compositeLow == 4) || (*compositeLow == 3)) && (checkFlag != 0)) {
        // This branch handles a typed value that expects a float operand
        // Copy the token's value (the second int) into output position
        copyTokenData(); // FUN_00627b40 – likely copies the 8-byte token from input to output
        int* inputPosAfter = reinterpret_cast<int*>(*(int*)(this + 0xc));
        int* outputPosAfter = reinterpret_cast<int*>(*(int*)(this + 0x8));
        *outputPosAfter = *inputPosAfter;
        *(outputPosAfter + 1) = *(inputPosAfter + 1);
        // Advance output pointer by one token (8 bytes)
        *(int*)(this + 0x8) += 8;

        // Check buffer capacity
        int* bufferDesc = reinterpret_cast<int*>(*(int*)(this + 0x10));
        if (static_cast<uint32_t>(bufferDesc[0x20/sizeof(int)]) <= static_cast<uint32_t>(bufferDesc[0x24/sizeof(int)])) {
            checkBufferOverflow(); // FUN_00627360
        }

        // Update token index: number of tokens written - 1
        int tokenCount = (*(int*)(this + 0x8) - *(int*)(this + 0xc)) / 8 - 1;
        adjustBufferIndex(this, 2, tokenCount); // FUN_006343b0

        // Move output pointer back one token? This is odd.
        *(int*)(this + 0x8) -= 8;
        advanceStream(); // FUN_006338a0 – likely moves input pointer forward
        return;
    }

    // Default: copy the current token (type and value) directly to output
    *compositeHigh = *compositeLow;
    *(compositeHigh + 1) = *(compositeLow + 1);
    *(int*)(this + 0x8) += 8;
    advanceStream(); // FUN_006338a0
}