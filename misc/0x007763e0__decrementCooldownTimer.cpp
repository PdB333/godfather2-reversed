// FUNC_NAME: decrementCooldownTimer
void __thiscall SomeClass::decrementCooldownTimer() {
    // +0xe80 is a cooldown/timer counter (int). Decrement if non-zero.
    if (this->field_0xe80 != 0) {
        this->field_0xe80--;
    }
}