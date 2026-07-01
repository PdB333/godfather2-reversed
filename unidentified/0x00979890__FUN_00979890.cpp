// FUNC_NAME: UnknownClass::setStateIdle
void __thiscall UnknownClass::setStateIdle(int this)
{
    // Check if current state at offset 0x158 is not 3 (idle)
    if (*(int *)(this + 0x158) != 3) {
        // Set state to 3 (idle)
        *(int *)(this + 0x158) = 3;
        // Schedule callback with timer/data at +0x14
        startTimer(this + 0x14, &onStateEntryCallback, 0);
    }
}