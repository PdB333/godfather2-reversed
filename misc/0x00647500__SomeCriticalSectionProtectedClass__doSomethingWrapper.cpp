// FUNC_NAME: SomeCriticalSectionProtectedClass::doSomethingWrapper
undefined4 FUN_00647500(undefined4 param_1, undefined4 param_2, undefined4 param_3)
{
    LPCRITICAL_SECTION lock;
    undefined4 result;
    
    lock = *(LPCRITICAL_SECTION *)(in_EAX + 0x4e8);  // this + 0x4e8, critical section pointer field
    
    if (lock != (LPCRITICAL_SECTION)0x0) {
        EnterCriticalSection(lock);
        lock[1].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)((int)&(lock[1].DebugInfo)->Type + 1);  // increment some debug/lock counter
    }
    
    result = FUN_00647550(param_3);  // actual work function
    
    if (lock != (LPCRITICAL_SECTION)0x0) {
        lock[1].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)((int)&lock[1].DebugInfo[-1].SpareWORD + 1);  // decrement counter
        LeaveCriticalSection(lock);
    }
    
    return result;
}