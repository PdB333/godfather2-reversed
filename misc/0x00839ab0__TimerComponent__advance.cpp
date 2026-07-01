// FUNC_NAME: TimerComponent::advance
// Address: 0x00839ab0
// Role: Advances an internal timer by a delta; if the timer reaches or exceeds the maximum threshold,
//        caps the timer and triggers the timeout callback (FUN_008397a0), otherwise calls the update callback (FUN_00839930).
void __thiscall TimerComponent::advance(int thisPtr, int delta)
{
    int *currentTime = (int *)(thisPtr + 0xf0);   // +0xf0: current accumulator
    uint *maxTime = (uint *)(thisPtr + 0x90);     // +0x90: maximum time value

    *currentTime = *currentTime + delta;

    if (*maxTime != 0 && *maxTime <= (uint)*currentTime) {
        *currentTime = (int)*maxTime;             // cap at max
        FUN_008397a0();                           // timeout reached handler
        return;
    }
    FUN_00839930();                               // continue update handler
}