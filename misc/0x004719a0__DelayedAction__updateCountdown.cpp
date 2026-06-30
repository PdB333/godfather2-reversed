// FUNC_NAME: DelayedAction::updateCountdown
// Address: 0x004719a0
// Role: Decrements a countdown byte at +0x162; when it reaches zero, calls a virtual method (vtable+0x70) and a callback stored in a subobject at +0x3C+0xC

void __fastcall DelayedAction::updateCountdown(int* thisPtr)
{
    // +0x162: countdown timer (byte)
    char* countdown = reinterpret_cast<char*>(thisPtr) + 0x162;

    if (*countdown != 0)
    {
        *countdown = *countdown - 1;
    }

    if (*countdown == 0)
    {
        // +0x3C (offset 0xF * 4): pointer to a callback holder struct
        // +0xC from that struct: function pointer to invoke when timer expires
        typedef void (*TimeoutCallback)(void);
        int* callbackHolder = reinterpret_cast<int*>(thisPtr + 0xF); // offset 0x3C
        TimeoutCallback timeoutFunc = *reinterpret_cast<TimeoutCallback*>(*callbackHolder + 0xC);
        timeoutFunc();

        // Virtual function at vtable slot 0x70 (index 28): likely onTimerExpired or update
        typedef void (__thiscall *VFunc)(int*);
        int vtable = *reinterpret_cast<int*>(thisPtr);
        VFunc vfunc = *reinterpret_cast<VFunc*>(vtable + 0x70);
        vfunc(thisPtr);
    }
}