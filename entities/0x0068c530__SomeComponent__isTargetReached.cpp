// FUNC_NAME: SomeComponent::isTargetReached
// Address: 0x0068c530
// Role: Checks if a proportional progression has reached its target based on current value, target, and mode.
// Offsets: +0x54 (byte enabledFlag), +0x58 (int mode), +0x5c (float currentValue), +0x70 (float targetValue)
// Global: _DAT_00d5780c is a constant (likely 1.0f)

extern const float DAT_00d5780c; // Typically 1.0f

bool __fastcall SomeComponent::isTargetReached(void) const {
    byte enabled = *(byte*)((int)this + 0x54);
    if (enabled != 0) {
        float current = *(float*)((int)this + 0x5c);
        float target = *(float*)((int)this + 0x70);
        int mode = *(int*)((int)this + 0x58);

        if (current <= target) {
            if (mode == 0) {
                return true;
            }
        } else {
            float ratio = target / current;
            if (mode != 0) {
                ratio = DAT_00d5780c - ratio;
            }
            if (DAT_00d5780c <= ratio) {
                return true;
            }
        }
    }
    return false;
}