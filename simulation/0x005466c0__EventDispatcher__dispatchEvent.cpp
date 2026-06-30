// FUNC_NAME: EventDispatcher::dispatchEvent

void __thiscall EventDispatcher::dispatchEvent(int thisPtr, int* eventParams)
{
    int* handler;
    int paramCopy[3]; // copies of eventParams[0..2]
    int extraParam;   // from global

    paramCopy[0] = eventParams[0];
    paramCopy[1] = eventParams[1];
    paramCopy[2] = eventParams[2];

    handler = *(int*)(thisPtr + 0x2e8); // pointer to handler object

    extraParam = DAT_00e2b1a4; // global extra parameter (e.g., sequence number or timestamp)

    FUN_009f2000();                // likely a debug hook or spinlock

    // Call virtual function at vtable offset 0x40 (index 16) on handler's embedded vtable pointer
    // handler+0xd0 holds a pointer to a polymorphic object's vtable,
    // then +0x40 is the function pointer
    (**(code **)(*(int*)(handler + 0xd0) + 0x40))(&paramCopy);
}