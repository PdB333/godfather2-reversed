// FUNC_NAME: EventDispatcher::dispatchByBitmask

void __thiscall EventDispatcher::dispatchByBitmask(int thisPtr, int *targetObj)
{
    uint *eventMask = (uint *)lookupEventMask(0xb284d27b);
    if (eventMask != (uint *)0x0) {
        if ((*eventMask & *(uint *)(thisPtr + 4)) != 0) {
            // vtable offset 100 (0x64) - handler for matching bit
            (**(code **)(*targetObj + 100))();
            return;
        }
        // vtable offset 104 (0x68) - default handler
        (**(code **)(*targetObj + 0x68))();
    }
    return;
}