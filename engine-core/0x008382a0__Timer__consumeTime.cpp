// FUNC_NAME: Timer::consumeTime
void __thiscall Timer::consumeTime(uint amount) {
    // +0xf4: mTimeRemaining (uint)
    if (amount <= mTimeRemaining) {
        mTimeRemaining -= amount;
    } else {
        mTimeRemaining = 0;
    }
}