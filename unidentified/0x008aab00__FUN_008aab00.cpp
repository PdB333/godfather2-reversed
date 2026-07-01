// FUNC_NAME: SomeClass::setFlagAndResetTimer
void __fastcall SomeClass::setFlagAndResetTimer(int thisPtr)
{
    // Stack-based timer structure initialized with global DAT_0112f534
    struct TimerStruct {
        undefined4 field_0; // +0x00: timer value or ID
        undefined4 field_4; // +0x04: counter/state (initialized to 0)
        undefined1 field_8; // +0x08: flag (initialized to 0)
    } timer;

    timer.field_0 = DAT_0112f534; // Global timer base value
    timer.field_4 = 0;
    timer.field_8 = 0;

    // Initialize/reset the timer (likely a countdown or cooldown)
    FUN_00408a00(&timer, 0);

    // Set bit 0x20 (5th bit) in the flags at offset +0x7C
    *(uint32_t *)(thisPtr + 0x7C) |= 0x20;

    // Call some update/cleanup function
    FUN_0094dc20();
}