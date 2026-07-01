// FUNC_NAME: Timer::subtractTime
void __thiscall Timer::subtractTime(Timer* this, uint timeToSubtract)
{
    // +0xF0: remaining time in milliseconds
    if (timeToSubtract <= *(uint*)((int)this + 0xF0)) {
        *(uint*)((int)this + 0xF0) -= timeToSubtract;
        FUN_00839930(); // likely Timer::onTimeChanged or similar callback
        return;
    }
    *(uint*)((int)this + 0xF0) = 0;
    FUN_00839930();
    return;
}