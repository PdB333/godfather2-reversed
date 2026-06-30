// FUNC_NAME: applyDamageStateModifiers

void applyDamageStateModifiers(undefined4 *vec4Param, undefined4 param2, undefined4 param3, undefined4 param4,
                               undefined4 param5, undefined4 param6, undefined4 param7, undefined4 param8,
                               undefined4 param9, char isInstant)
{
    char *stringPtr;
    
    stringPtr = (char *)in_EAX; // in_EAX is a register variable, likely this pointer or first parameter
    
    // Condition: if the string is empty or the flag at offset +0x1e of the structure pointed by stringPtr+4 is non-zero
    if ((*stringPtr == '\0') || (*(char *)(*(int *)(stringPtr + 4) + 0x1e) != '\0'))
    {
        // Set global state variables
        DAT_0121a204 = DAT_0121a36c;
        DAT_0121a200 = DAT_0121a368;
        
        // If a certain global pointer matches, free objects
        if (DAT_012058e8 == &DAT_0121a1f0)
        {
            FUN_0060a460(DAT_0121a36c);
            FUN_0060a460(DAT_0121a200);
        }
        
        // Branch based on global flag DAT_0120575b
        if (DAT_0120575b == '\0')
        {
            if (*stringPtr == '\0')
            {
                _DAT_0121a300 = 0;
            }
            else
            {
                _DAT_0121a300 = *(undefined4 *)(*(int *)(stringPtr + 4) + 0x24);
            }
        }
        else
        {
            FUN_00536990(); // some float operation
            if (*stringPtr == '\0')
            {
                FUN_00536a40(0, param4, param5, 0x3f800000); // set something with 1.0f
            }
            else
            {
                // Calculate float: (byte at offset 0x1d + DAT_00e2cd54) * DAT_00e2ee80
                float factor = ((float)*(byte *)(*(int *)(stringPtr + 4) + 0x1d) + DAT_00e2cd54) * DAT_00e2ee80;
                FUN_00536a40(factor, param4, param5, 0);
            }
        }
        
        // Clamp values and set state flags (likely health/timer/state variables)
        // These repeated patterns suggest a state machine update
        if (DAT_012058d0 < 0x19) { DAT_012058d0 = 0x19; }
        if (0x19 < DAT_00f15988) { DAT_00f15988 = 0x19; }
        _DAT_011f3a3c = 7;
        
        if (DAT_012058d0 < 0x18) { DAT_012058d0 = 0x18; }
        if (0x18 < DAT_00f15988) { DAT_00f15988 = 0x18; }
        _DAT_011f3a38 = 0;
        
        if (DAT_012058d0 < 0xf) { DAT_012058d0 = 0xf; }
        if (0xf < DAT_00f15988) { DAT_00f15988 = 0xf; }
        _DAT_011f3a14 = 0;
        
        if (DAT_012058d0 < 0xe) { DAT_012058d0 = 0xe; }
        if (0xe < DAT_00f15988) { DAT_00f15988 = 0xe; }
        _DAT_011f3a10 = 0;
        
        if (DAT_012058d0 < 0x1b) { DAT_012058d0 = 0x1b; }
        if (0x1a < DAT_00f15988) { DAT_00f15988 = 0x1b; }
        _DAT_011f3a44 = 1;
        
        FUN_004ec7a0(); // another update
        
        if (DAT_012058d0 < 0x16) { DAT_012058d0 = 0x16; }
        if (0x16 < DAT_00f15988) { DAT_00f15988 = 0x16; }
        _DAT_011f3a30 = 1;
        
        FUN_005368e0(); // more processing
        
        // Copy the first 4 values of vec4Param to globals (appears to be a vector/color)
        _DAT_0121a2b0 = *vec4Param;
        _DAT_0121a2b4 = vec4Param[1];
        _DAT_0121a2b8 = vec4Param[2];
        _DAT_0121a2bc = vec4Param[3];
        
        // If condition holds, call a transform function
        if ((DAT_012058e8 == &DAT_0121a1f0) && (DAT_0121a200 == DAT_0121a368))
        {
            FUN_0060add0(DAT_0121a368, DAT_0121a31c, &DAT_0121a2b0);
        }
        
        FUN_00536550(); // final update
        
        // Branch based on isInstant flag
        if (isInstant == '\0')
        {
            FUN_00506e40(param2, param3, param6, param7, param8);
        }
        else
        {
            FUN_00506fa0();
        }
        
        FUN_00612e00(); // cleanup
        
        // Reset some globals to zero
        _DAT_0121a310 = 0;
        _DAT_0121a314 = 0;
        _DAT_0121a318 = 0;
        
        // Another set of clamping and state flags (second phase)
        if (DAT_012058d0 < 0x19) { DAT_012058d0 = 0x19; }
        if (0x19 < DAT_00f15988) { DAT_00f15988 = 0x19; }
        _DAT_011f3a3c = 7;
        
        if (DAT_012058d0 < 0x18) { DAT_012058d0 = 0x18; }
        if (0x18 < DAT_00f15988) { DAT_00f15988 = 0x18; }
        _DAT_011f3a38 = 0;
        
        if (DAT_012058d0 < 0xf) { DAT_012058d0 = 0xf; }
        if (0xf < DAT_00f15988) { DAT_00f15988 = 0xf; }
        _DAT_011f3a14 = 0;
        
        if (DAT_012058d0 < 0xe) { DAT_012058d0 = 0xe; }
        if (0xe < DAT_00f15988) { DAT_00f15988 = 0xe; }
        _DAT_011f3a10 = 1; // note different value
        
        if (DAT_012058d0 < 0x1b) { DAT_012058d0 = 0x1b; }
        if (0x1a < DAT_00f15988) { DAT_00f15988 = 0x1b; }
        _DAT_011f3a44 = 0; // different value
        
        FUN_00417cf0(1, 5, 6); // animation or event call
        
        if (DAT_012058d0 < 0x16) { DAT_012058d0 = 0x16; }
        if (0x16 < DAT_00f15988) { DAT_00f15988 = 0x16; }
        _DAT_011f3a30 = 1;
    }
}