// FUNC_NAME: ParameterStream::readFloatParam

bool __thiscall ParameterStream::readFloatParam(int thisPtr) {
    // thisPtr offsets:
    // +0x8: current write position pointer (m_writePos)
    // +0xC: end of buffer pointer (m_endPos)
    static const float s_undefinedFloat = DAT_00e2b05c; // sentinel value for undefined
    float value;
    int* tokenPtr = *(int**)(thisPtr + 0xC);
    
    if (*(int**)(thisPtr + 0x8) <= tokenPtr) // write position >= end
        goto error;
    if (tokenPtr == nullptr)
        goto error;
    
    if (*tokenPtr == 3) {
        // type 3: immediate float
        value = (float)tokenPtr[1];
    } else if (*tokenPtr == 4) {
        // type 4: variable reference
        int varIndex;
        if (!resolveVariable(&varIndex)) // FUN_00636850
            goto error;
        // simulate inline conversion (stack temp)
        value = (float)varIndex; // actual conversion may differ
    } else {
        goto error;
    }
    
    if (value == s_undefinedFloat) {
        // Loop until a valid token appears or buffer is exhausted
        while (true) {
            tokenPtr = *(int**)(thisPtr + 0xC);
            if (*(int**)(thisPtr + 0x8) <= tokenPtr || tokenPtr == nullptr) break;
            if (*tokenPtr == 3) break;
            if (*tokenPtr == 4 && resolveVariable(&varIndex)) break;
            debugPrintf("number"); // FUN_00627ac0
error:
            value = 0.0f;
        }
    }
    
    uint* writePos = *(uint**)(thisPtr + 0x8);
    *writePos = 3; // write type tag
    double dval = (double)value;
    writeChecksum(); // FUN_00d3d645 - unknown but important for stream integrity
    writePos[1] = (float)dval;
    *(int*)(thisPtr + 0x8) = (int)(writePos + 2); // advance by 8 bytes
    return true;
}