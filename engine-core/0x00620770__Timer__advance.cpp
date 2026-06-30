// FUNC_NAME: Timer::advance
void __thiscall Timer::advance(float deltaTime)
{
    // Profile/scoped timing marker for this update
    ProfileBegin(&gProfileTimer);      // FUN_00ab4db0

    // Accumulate elapsed time
    mElapsedTime += deltaTime;         // +0x48

    // If the "done" flag is set, clear it (reset for next interval)
    if (mIsDone) {                     // +0x80
        mIsDone = false;               // +0x80 cleared
    }

    ProfileEnd();                      // FUN_00ab4e70
}