// FUNC_NAME: FrameworkObject::destroy
void __thiscall FrameworkObject::destroy(FrameworkObject* thisPtr)
{
    // Reset pending operations or state
    FUN_00983120(0, 0, 0);

    // Wait for pending async operations to complete (offset 0x6c likely flag/pointer)
    int* pendingPtr = *(int**)(thisPtr + 0x6c);
    while (pendingPtr != null) {
        FUN_00982c00(0xffffffff, 1); // yield to system (sleep/allow processing)
        pendingPtr = *(int**)(thisPtr + 0x6c);
    }

    // Register a shutdown callback (offset 0x10 likely a function pointer slot)
    // Pass reference to a static callback function (LAB_00982b20) and a flag (1)
    FUN_005c02f0(thisPtr + 0x10, &FUN_00982b20, 1);

    // Release child object at offset 0x68 if present
    int* childObj = *(int**)(thisPtr + 0x68);
    if (childObj != null) {
        // Call destructor/release via vtable at offset 0x14
        void (*releaseFunc)(int, int*, int) = *(void (**)(int, int*, int))(childObj + 0x14);
        if (releaseFunc != null) {
            releaseFunc(*(int*)(childObj + 8), childObj, 1); // Arg1 from child+8, Arg2 child, Arg3=1
        }
        *(int**)(thisPtr + 0x68) = null; // Clear pointer
    }

    return;
}