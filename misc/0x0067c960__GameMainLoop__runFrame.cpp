// FUNC_NAME: GameMainLoop::runFrame
int __fastcall GameMainLoop::runFrame(int *thisPtr)
{
    int vtablePtr;          // dereferenced from this (vtable at +0x00)
    void *mainLoopObj;      // result of singleton getter
    vtablePtr = *thisPtr;   // +0x00: vtable pointer
    mainLoopObj = FUN_00683280("GameMainLoop"); // get the game main loop singleton
    // call function pointer at vtable offset 0x14 (5th slot) with mainLoopObj as argument
    (*(void (__fastcall *)(void *))(vtablePtr + 0x14))(mainLoopObj);
    FUN_0067c8b0(); // post‑frame cleanup or update
    return 1;       // success
}