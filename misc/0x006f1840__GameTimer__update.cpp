// FUNC_NAME: GameTimer::update
// Address: 0x006f1840
// Role: Updates a timer, calls a virtual callback on completion, and clears the active flag.
// Structure offsets:
//   +0x00: vtable pointer
//   +0x23: byte flags (bit 2 = active)
//   +0x78: float timerRemaining (stored as int in decompiler but semantically float)
//   +0x8d: byte callbackParameter (passed to virtual callback)
class GameTimer {
public:
    // Virtual function table entry at offset 0x28 (index 10) is the callback.
    // This function is invoked when the timer expires.
    // Parameter: byte from offset 0x8d.
    virtual void onTimerExpired(unsigned char param) = 0;

    // Update the timer by delta time
    // param_1: this pointer, param_2: deltaTime
    void update(float deltaTime) {
        // Check if the timer is active (bit 2 of flags at +0x23)
        if ((flags_ & 0x04) != 0) {
            // If timer has expired (remaining <= 0.0)
            if (timerRemaining_ <= 0.0f) {
                // Call virtual callback with byte from +0x8d
                this->onTimerExpired(callbackParameter_);
                // Clear the active flag
                flags_ &= ~0x04;
                return;
            }
            // Decrement timer by delta time (store back as float)
            timerRemaining_ -= deltaTime;
        }
    }

private:
    unsigned char flags_;        // +0x23: bit 2 indicates timer active
    float timerRemaining_;       // +0x78: countdown time (interpreted as float)
    unsigned char callbackParameter_; // +0x8d: parameter for the completion callback
};

// Decompiled original:
// void __thiscall FUN_006f1840(GameTimer* this, float deltaTime) {
//     if ((this->flags_ & 4) != 0) {
//         if (this->timerRemaining_ <= 0.0f) {
//             this->onTimerExpired(this->callbackParameter_);
//             this->flags_ &= ~4;
//             return;
//         }
//         this->timerRemaining_ -= deltaTime;
//     }
// }