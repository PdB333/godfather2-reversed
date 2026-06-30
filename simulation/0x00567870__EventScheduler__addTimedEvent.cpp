// FUNC_NAME: EventScheduler::addTimedEvent
void __thiscall EventScheduler::addTimedEvent(int* thisPtr, void* callbackObject, int param3, int param4, int param5)
{
    // param3 is stored but not used in this snippet (maybe for future use)
    int storedParam3 = param3;

    // Combine param4 and param5 into a 64-bit value (likely a timeout or data)
    long long combinedData = (static_cast<long long>(param5) << 32) | static_cast<unsigned int>(param4);

    // Pointer to a static callback function (defined at 0x00567930)
    // This is likely the timer callback trampoline
    void (*callbackTrampoline)(void) = reinterpret_cast<void (*)(void)>(0x00567930);

    // Call virtual function at vtable offset 8 (index 2)
    // Signature: void (__thiscall *)(void* callbackObj, void** trampolinePtr, int zero, int delayMs)
    void (__thiscall *vfunc)(void*, void**, int, int) = reinterpret_cast<void (__thiscall *)(void*, void**, int, int)>((*(int**)thisPtr)[2]);

    vfunc(callbackObject, reinterpret_cast<void**>(&callbackTrampoline), 0, 120000);  // 120000 ms = 2 minutes
}