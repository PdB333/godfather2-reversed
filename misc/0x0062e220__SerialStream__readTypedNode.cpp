// FUNC_NAME: SerialStream::readTypedNode
unsigned int SerialStream::readTypedNode() {
    // +0x08: current write pointer (destination)
    // +0x0C: current read pointer (source)
    // +0x10: pointer to size/length struct (offset +0x20 and +0x24)
    int* pReadPtr = *(int**)(this + 0x0C);
    if ( (*(int**)(this + 0x08) <= pReadPtr) || (pReadPtr == (int*)0x0) || (*pReadPtr != 5) ) {
        // assert or error with string table
        FUN_00627ac0(PTR_s_table_00e2a8b0);
    }
    // Check buffer size
    int* pSizeStruct = *(int**)(this + 0x10);
    if ( *(unsigned int*)(pSizeStruct + 0x20) <= *(unsigned int*)(pSizeStruct + 0x24) ) {
        FUN_00627360(); // size overflow assertion
    }

    // Write type tag 4 (probably "typed" or "reference")
    unsigned int* pWritePos = *(unsigned int**)(this + 0x08);
    *pWritePos = 4;
    // Read 4-byte value from stream (DAT_00e3ebc0 is temporary read buffer?)
    unsigned int readValue = FUN_00638920(this, &DAT_00e3ebc0, 4);
    pWritePos[1] = readValue;
    // Advance write pointer by 8 bytes
    *(int*)(this + 0x08) = *(int*)(this + 0x08) + 8;

    // Now examine what was just written (at position writePointer - 8)
    int writtenPrimitive = *(int*)(*(int*)(this + 0x08) - 8);
    int* pFactoryResult;
    if (writtenPrimitive == 3) {
        // Float? Check if integer-to-float conversion is exact
        if ( (float)(int)*(float*)(*(int*)(this + 0x08) - 4) == *(float*)(*(int*)(this + 0x08) - 4) ) {
            pFactoryResult = (int*)FUN_00637f10(); // factory for type 3
            goto LAB_0062e2c3;
        }
    } else if (writtenPrimitive == 4) {
        pFactoryResult = (int*)FUN_00637f90(); // factory for type 4
        goto LAB_0062e2c3;
    }
    // Default factory
    pFactoryResult = (int*)FUN_00637ea0(); // fallback
LAB_0062e2c3:
    // Overwrite the type/size fields with factory result (writtenPrimitive is overwritten)
    *(int*)(*(int*)(this + 0x08) - 8) = *pFactoryResult;
    *(int*)(*(int*)(this + 0x08) - 4) = pFactoryResult[1];

    // Copy 8 bytes from read pointer to write pointer
    unsigned int* pReadCopy = *(unsigned int**)(this + 0x0C);
    unsigned int* pWriteCopy = *(unsigned int**)(this + 0x08);
    *pWriteCopy = *pReadCopy;
    pWriteCopy[1] = pReadCopy[1];
    *(int*)(this + 0x08) = *(int*)(this + 0x08) + 8;

    // Write null (likely terminator) at new write position
    **(unsigned int**)(this + 0x08) = 0;
    *(int*)(this + 0x08) = *(int*)(this + 0x08) + 8;

    return 3;
}