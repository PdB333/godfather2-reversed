// FUNC_NAME: Entity::updateTimerTick
// Address: 0x00977250
// Role: Decrements a timer field (at +0x150) each frame if non-zero. Uses a float interpretation to detect zero, possibly due to sign-bit handling.
void __fastcall Entity::updateTimerTick()
{
    // Timer stored as int at +0x150, but interpreted as float for zero comparison
    float timer = static_cast<float>(this->field_0x150); // Convert raw int to float
    // If int is negative, adjust by global constant (likely 0.0f)
    if (this->field_0x150 < 0) {
        timer += DAT_00e44578; // Probably 0.0f, but kept as variable
    }
    // Only decrement if float value is not exactly zero
    if (timer != 0.0f) {
        int newCount = FUN_00494d10(); // Returns current frame count or random value
        this->field_0x150 = newCount - 1; // Set timer to (count - 1)
    }
}