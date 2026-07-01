// FUNC_NAME: spinWaitOnFlag
void __fastcall spinWaitOnFlag(int thisPtr)
{
    // +0x12: short pendingFlag (non-zero means operation in progress)
    short flag = *(short *)(thisPtr + 0x12);
    while (flag != 0) {
        // Process pending work; likely decrements or clears the flag
        FUN_00408090();
        flag = *(short *)(thisPtr + 0x12);
    }
}