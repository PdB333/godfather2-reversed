// FUNC_NAME: TimerComponent::isExpired
// Address: 0x005098a0
// Checks if a timer value has expired (value <= 0 or > threshold)
// Access: member function __thiscall
// Class: TimerComponent (presumed)
// Fields: this+0x24 -> pointer to sub-object, sub+0xCC -> float timer

bool TimerComponent::isExpired() const
{
    // Retrieve timer value from nested structure
    float timerValue = *(float*)(*(int*)((uintptr_t)this + 0x24) + 0xCC); // +0x24: pointer to timer data, +0xCC: timer duration/remaining

    // If timer is positive and within threshold, it's still active (not expired)
    // Return false (0) in this case, true (1) otherwise
    // Global threshold DAT_00e2e714 defines maximum valid timer value
    if ((0.0f < timerValue) && (timerValue <= DAT_00e2e714))
    {
        return false;
    }
    return true;
}