// FUNC_NAME: PlayerF2FSM::setShowF2FTarget
void __thiscall PlayerF2FSM::setShowF2FTarget(void *thisPtr, int x, int y, int z, int w) {
    byte* flagsByte = (byte*)((int)thisPtr + 0x49);
    
    // Store the four parameters – likely a rectangle or two 2D points (x,y) and (z,w)
    *(int*)((int)thisPtr + 0x54) = x; // +0x54: targetX or left
    *(int*)((int)thisPtr + 0x58) = y; // +0x58: targetY or top
    *(int*)((int)thisPtr + 0x5C) = z; // +0x5C: targetZ or right
    *(int*)((int)thisPtr + 0x60) = w; // +0x60: targetW or bottom
    
    // Set the "showF2F" flag (bit 2 only) – clears other flags in that byte
    *flagsByte = *flagsByte & 4;
    
    // Mark this F2F state as active (offset +0x50 = 1)
    *(byte*)((int)thisPtr + 0x50) = 1;
    
    // If the flag was already set (bit 2 was 1) before we cleared others,
    // print a debug message and trigger some script
    if (*flagsByte != 0) {
        FUN_005a04a0("ShowF2F", 0, &DAT_00d88584, 0);
        // Build a ScriptArg struct (likely 3 ints) from global DAT_01130420
        ScriptArg arg;
        arg.value0 = DAT_01130420;
        arg.value1 = 0;
        arg.value2 = 0;
        FUN_00408a00(&arg, 0); // Execute script event with these args
    }
}