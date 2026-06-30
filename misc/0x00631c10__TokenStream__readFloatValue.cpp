// FUNC_NAME: TokenStream::readFloatValue
// Function at 0x00631c10: reads a floating-point token from a token-based stream,
// handling reference tokens (type 4) and skipping any token whose value equals
// a special sentinel (likely INF or NaN). Writes the resulting float token back
// to the stream's write position.

// Based on EA EARS engine, likely part of serialization subsystem.
// Structure offsets:
// +0x00: unknown (maybe vtable or size)
// +0x04: unknown
// +0x08: pointer to end of read area (write position? or buffer end)
// +0x0c: pointer to current read position (read pointer)
// Tokens are 8-byte entries: uint32 type, float value.

int TokenStream::readFloatValue(int thisPtr)
{
    int* readPtr;
    int result;
    double dVar;
    float value;
    int fakeTokenType;
    float fakeTokenValue;
    
    readPtr = *(int**)(thisPtr + 0xc); // current read position
    
    // Validate read position
    if (*(int**)(thisPtr + 0x8) <= readPtr) // read pointer >= end?
        goto endWithZero;
    if (readPtr == (int*)0x0)
        goto endWithZero;
    
    // Check token type
    if (*readPtr != 3) // 3 = float token
    {
        if (*readPtr != 4) // 4 = reference token
            goto endWithZero;
        
        // Resolve reference to a float value
        result = resolveFloatReference(&value); // FUN_00636850
        if (result == 0)
            goto endWithZero;
        
        // Create a synthetic token of type 3 with the resolved value
        fakeTokenType = 3;
        fakeTokenValue = value;
        readPtr = &fakeTokenType; // point to local stack token
    }
    
    // Extract the float value from the token
    value = (float)readPtr[1]; // second word of token
    
    // Check if the value equals the special skip sentinel
    if (value == specialSkipValue) // DAT_00e2b05c
    {
        // Loop until we find a valid token that isn't the skip value
        while ( (readPtr = *(int**)(thisPtr + 0xc), 
                 *(int**)(thisPtr + 0x8) <= readPtr || readPtr == (int*)0x0) ||
                ( *readPtr != 3 && (*readPtr != 4 || 
                     (result = resolveFloatReference(&fakeTokenType), result == 0) ) ) )
        {
            logError("number"); // FUN_00627ac0
endWithZero:
            value = 0.0f;
        }
    }
    
    // Write a float token (type 3) with the final value to the stream
    int* writePtr = *(int**)(thisPtr + 0x8);
    *writePtr = 3; // token type
    dVar = (double)value;
    performFloatAdjustment(); // FUN_00d3d645 - possibly converts double back to float
    writePtr[1] = (float)dVar;
    *(int*)(thisPtr + 0x8) = *(int*)(thisPtr + 0x8) + 8; // advance write pointer
    
    return 1;
}