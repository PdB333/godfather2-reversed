// FUNC_NAME: TimerManager::updateTimer

// Address: 0x00799590
// Role: Updates a countdown timer. When the timer exceeds two thresholds, triggers a virtual callback and resets the timer.
// Member variable at offset +0xB20 (float) stores the elapsed time (likely in seconds or milliseconds).
// Globals:
//   _DAT_00d577a0 - upper threshold (may be a large sentinel value)
//   DAT_00d6a54c - lower threshold (trigger point)
//   DAT_00d5ccf8 - reset value (likely 0.0f)
// Virtual function at vtable offset 0x2E4 (vtableIndex 185) called with argument 3 when timer exceeds both thresholds.

void __thiscall TimerManager::updateTimer(float deltaTime)
{
    float currentTime = *(float *)((char *)this + 0xB20); // treat as float member

    if (_DAT_00d577a0 <= currentTime)
    {
        if (DAT_00d6a54c <= currentTime)
        {
            // Timer exceeded both thresholds: trigger action and reset.
            FUN_007f6db0(0);
            (this->vtable[0x2E4 / 4])(3); // call virtual function at index 185
            FUN_007f63b0(1);
            *(float *)((char *)this + 0xB20) = DAT_00d5ccf8; // reset timer to default value
            return;
        }
        // Timer between lower and upper threshold: increment by deltaTime
        *(float *)((char *)this + 0xB20) = currentTime + deltaTime;
    }
    // If below lower threshold, nothing happens (timer remains unchanged?)
}