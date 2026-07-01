// FUNC_NAME: DataStreamProcessor::deserializeDataStream
void __thiscall DataStreamProcessor::deserializeDataStream(void* thisPtr, uint32_t streamId)
{
    char hasMoreData;
    int tokenType;
    uint32_t dataValue;

    FUN_0046c710(streamId); // initialize stream
    FUN_0043aff0(streamId, 0x656df767); // set stream magic/identifier

    hasMoreData = FUN_0043b120(); // check end of stream (returns 0 if more data)
    while (hasMoreData == '\0') {
        FUN_0043b210(); // advance to next token/chunk

        tokenType = FUN_0043ab70(); // get current token type (0,1,2)
        if (tokenType == 0) {
            FUN_0043b210(); // read again? maybe skip delimiter
            dataValue = FUN_0043ab90(); // read value
            // +0x50: pointer or value member, setting via setter
            FUN_004089b0((int)thisPtr + 0x50, dataValue); // set member at this+0x50
        } else if (tokenType == 1) {
            int sourcePtr = FUN_0043b210(); // get pointer to data chunk
            // +0x60: integer member, copy from source offset 8
            *(int*)((int)thisPtr + 0x60) = *(int*)(sourcePtr + 8);
        } else if (tokenType == 2) {
            FUN_0043b210(); // read again
            dataValue = FUN_0043ab90(); // read value
            // +0x58: another member
            FUN_00408980((int)thisPtr + 0x58, dataValue); // set member at this+0x58
        }
        FUN_0043b1a0(); // finalize token read, advance internal state
        hasMoreData = FUN_0043b120(); // check for more data
    }
    return;
}