// FUNC_NAME: SomeClass::updateTimerOrSomething
void __fastcall SomeClass::updateTimerOrSomething(int thisPtr)
{
    undefined4 local_c;
    undefined4 local_8;
    undefined1 local_4;

    // +0x60: some float timer/value, +0x58: some data (likely a vector or struct)
    if (*(float *)(thisPtr + 0x60) < DAT_00e44598) {
        local_c = *(undefined4 *)(thisPtr + 0x58);
        local_8 = 0;
        local_4 = 0;
        FUN_00408a00(&local_c); // likely a reset or stop function
        *(undefined1 *)(thisPtr + 0x80) = 1; // +0x80: flag (e.g., completed)
        return;
    }
    // +0x58: some data, +0x60: float value (e.g., time remaining)
    FUN_00440590(thisPtr + 0x58, 0, *(float *)(thisPtr + 0x60), 0, 0); // likely an update/lerp function
    *(undefined1 *)(thisPtr + 0x80) = 1; // +0x80: flag
    return;
}