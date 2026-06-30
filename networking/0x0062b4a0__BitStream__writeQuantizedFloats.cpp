// FUNC_NAME: BitStream::writeQuantizedFloats

int BitStream::writeQuantizedFloats(void)
{
    int numEntries = (m_writeEnd - m_readStart) >> 3; // +8: writeEnd, +0xc: readStart
    int entryIndex = 1;
    uint8* outPtr = m_outBuffer; // local_20c
    int outCount = 0;
    int iVar8 = numEntries;

    if (0 < numEntries) {
        do {
            float fVal = readFloatFromIndex(this, entryIndex); // FUN_006259b0
            if (fVal == 0.0f) {
                if (entryIndex < 1) goto skipSpecial;
                int* entryPtr = (int*)(m_readStart - 8 + entryIndex * 8); // +0xc
                if (entryPtr < (int*)m_writeEnd) {
                    do {
                        debugPrint("number"); // FUN_00627ac0
                        iVar8 = entryIndex;
skipSpecial:
                        if (entryIndex < -9999) {
                            if (entryIndex == -0x2711) {
                                entryPtr = (int*)(this + 0x40); // special buffer
                            }
                            else if (entryIndex == -10000) {
                                entryPtr = (int*)(*(int*)(this + 0x10) + 0x2c); // external stream field
                            }
                            else {
                                int base4 = *(int*)(*(int*)(this + 0xc) - 4);
                                if ((int)(uint)*(byte*)(base4 + 7) < (-0x2711 - entryIndex)) {
                                    entryPtr = NULL;
                                }
                                else {
                                    entryPtr = (int*)(base4 + 8 + (-0x2711 - entryIndex) * 8);
                                }
                            }
                        }
                        else {
                            entryPtr = (int*)(m_writeEnd + entryIndex * 8); // +8
                        }
                    } while ((entryPtr == NULL) ||
                             ((*entryPtr != 3 &&
                               ((*entryPtr != 4 || (iVar8 = validateType4(this), iVar8 = numEntries, iVar8 == 0))))));
                }
            }
            if (((int)fVal & 0xffU) != (int)fVal) {
                errorInvalidValue(this, entryIndex, "invalid value"); // FUN_00627a20
                return 0;
            }
            if (outPtr >= m_localBufferEnd) { // local_c
                if (expandOutBuffer(&outPtr)) { // FUN_00628940, 006289a0
                    // buffer extended
                }
            }
            *outPtr = (uint8)(int)fVal;
            outPtr++;
            entryIndex++;
        } while (entryIndex <= iVar8);
    }

    int bytesWritten = (int)(outPtr - m_outBuffer); // local_20c
    if (bytesWritten != 0) {
        if (*(uint*)(*(int*)(this + 0x10) + 0x20) <= *(uint*)(*(int*)(this + 0x10) + 0x24)) {
            // Stream buffer full handling
            uint uVar5 = flushStream(); // FUN_00627290
            writeStreamSize(this, 0); // FUN_00626f80
            writeStreamType(0); // FUN_00626fd0
            writeStreamSize(this, 0); // FUN_00626f80
            writeStreamData(uVar5); // FUN_00627010
            finalizeStream(); // FUN_006270e0
        }
        // Write a new 8-byte entry to output stream
        int* writePtr = (int*)m_writeEnd; // +8
        *writePtr = 4; // type: byte array
        int handle = writeDataToStream(this, m_outBuffer, bytesWritten); // FUN_00638920
        writePtr[1] = handle;
        m_writeEnd = (uint8*)(m_writeEnd + 8); // advance pointer
        outPtr = m_outBuffer;
        outCount++;
    }
    return 1;
}