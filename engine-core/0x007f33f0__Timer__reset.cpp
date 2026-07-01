// FUNC_NAME: Timer::reset
void __thiscall Timer::reset(int thisPtr, uint param)
{
    *(uint *)(thisPtr + 0x10) = (uint)DAT_01205228; // +0x10: maximum timer value (global constant)
    *(uint *)(thisPtr + 0x14) = 0;                   // +0x14: elapsed time, reset to zero
    *(uint *)(thisPtr + 0xc) = param;                // +0xc: duration / target time
    return;
}