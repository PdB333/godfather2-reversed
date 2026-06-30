// FUNC_NAME: updateFrameTimer
void __fastcall updateFrameTimer(void* this, uint32_t flags)
{
    // If bit 0 is set, perform an alternative update (likely stepped/paused update)
    if ((flags & 1) != 0) {
        FUN_0052cbd0();   // stepped/paused update
        return;
    }

    // Normal continuous update: call another function and accumulate delta time
    FUN_0052b770();                     // perform normal update logic
    DAT_01125280 += DAT_00e2b1a4;       // accumulate frame delta time into global timer
}