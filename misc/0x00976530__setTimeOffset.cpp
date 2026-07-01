// FUNC_NAME: setTimeOffset
void __thiscall setTimeOffset(int offset)
{
    // Get base time value from global function
    int currentTime = getCurrentTime();  // FUN_00494d10
    
    // Store base time + offset into member at +0x18
    *(int *)(this + 0x18) = currentTime + offset;
}