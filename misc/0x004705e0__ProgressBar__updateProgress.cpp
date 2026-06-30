// FUNC_NAME: ProgressBar::updateProgress
void __thiscall ProgressBar::updateProgress(void)
{
    float delta;           // calculated movement for this frame
    float currentValue;    // this->currentProgress (+0x150)
    float newValue;
    uint16_t flags;

    // Global frame time (scaled?), wrapped if negative
    delta = *(float*)0x01206804;
    if (*(float*)0x01206804 < 0.0f) {
        delta += *(float*)0x00e44578;   // wrap around
    }
    delta *= this->speed;               // +0x154

    currentValue = this->currentProgress;   // +0x150

    if (this->speed <= 0.0f) {
        // Speed is zero or negative (decreasing)
        if (currentValue <= 0.0f) {
            // Already at or below zero
            flags = *(uint16_t*)((uint32_t)this + 0x15e);
            this->speed = 0.0f;

            if ((flags & 0x4) != 0) {
                // Flag5 (bit2): call some callback
                FUN_00449e90();
                return;
            }
            if ((flags & 0x8) != 0) {
                // Flag6 (bit3): if repeat flag (bit4) not set, trigger vtable callback
                if ((flags & 0x10) == 0) {
                    *(uint16_t*)((uint32_t)this + 0x15e) |= 0x10;   // set bit4
                    (*(void (**)(void))(*(uint32_t*)this + 0x6c))(); // vtable+0x6c callback
                }
                return;
            }
            // No special flags: call another method with 0
            FUN_004706f0(0);
            return;
        }
        // Positive currentValue, decrease it
        newValue = currentValue + delta;
        if (newValue >= 0.0f && newValue <= *(float*)0x00e2b1a4) {
            goto LAB_0047066d;
        }
        // Clamp to 0
        newValue = 0.0f;
    }
    else {
        // Speed is positive (increasing)
        if (*(float*)0x00e2b1a4 <= currentValue) {
            this->speed = 0.0f;          // Already at max, stop
            return;
        }
        newValue = currentValue + delta;
        if (newValue >= 0.0f) {
            if (newValue > *(float*)0x00e2b1a4) {
                newValue = *(float*)0x00e2b1a4;
            }
            goto LAB_0047066d;
        }
        newValue = 0.0f;
    }

LAB_0047066d:
    if (currentValue == newValue) {
        return;
    }
    this->currentProgress = (int)newValue;
    *(uint16_t*)((uint32_t)this + 0x15e) |= 0x100;  // dirty flag (bit8)
}