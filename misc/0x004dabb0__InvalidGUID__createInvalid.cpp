// FUNC_NAME: InvalidGUID::createInvalid
undefined4* InvalidGUID::createInvalid(undefined4* thisPtr)
{
    undefined4* curDst;
    undefined4 in_EAX;
    int loopCount;
    const char* guidStr;
    undefined4* nextDst;
    int sehHandler;
    
    guidStr = "{BADBADBA-BEEF-BEEF-555A-C1EA11091091}";
    curDst = thisPtr;
    // Copy GUID string representation: 9 dwords (36 bytes) then short + char (3 bytes) = 39 bytes total
    for (loopCount = 9; (nextDst = curDst + 1, loopCount != 0); loopCount = loopCount + -1) {
        *nextDst = *(undefined4*)guidStr;
        guidStr = guidStr + 4;
        curDst = nextDst;
    }
    // Write remaining 2 bytes (short) at curDst+1 (offset 0x28) and 1 byte at curDst+7 (offset 0x2A)
    *(undefined2*)nextDst = *(undefined2*)guidStr;
    *(char*)((int)curDst + 6) = guidStr[2];
    
    // Set status byte at offset 0x2C to 1 (valid flag?)
    *(char*)(thisPtr + 0x0b) = 1;
    // Clear a dword at offset 0x4C
    thisPtr[0x13] = 0;
    // Set first dword to 1 (object type?)
    *thisPtr = 1;
    
    // Additional initialization calls
    FUN_004d9d60(in_EAX);   // likely vtable setup or another init
    FUN_004d9ff0();         // further setup
    
    // Exception handler cleanup if needed
    if (sehHandler != 0) {
        FUN_004da530();
        FUN_009c8eb0(sehHandler);
    }
    
    return thisPtr;
}