// FUNC_NAME: TimerComponent::tick
// Function address: 0x0055ba20
// Role: Decrements a byte counter at +0x161; when it reaches zero and a flag at +0x130 is set, calls a virtual method (vtable+300) and then a helper function.

void __thiscall TimerComponent::tick(TimerComponent *this)
{
    // Decrement the timer count if non-zero
    if (this->m_timerCount != 0) {
        this->m_timerCount--;
    }

    // If timer expired and callback is pending, invoke the virtual method
    if (this->m_timerCount == 0 && this->m_callbackPending != 0) {
        (this->vtable[75])(); // vtable+300, likely "onTimerExpired" or "onComplete"
    }

    // Post-tick cleanup or update
    FUN_0055bb70(); // likely a helper (e.g., check destruction or update state)
}