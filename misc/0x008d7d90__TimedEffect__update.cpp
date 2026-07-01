// FUNC_NAME: TimedEffect::update

// 0x008d7d90
// Purpose: Advance internal elapsed time counter by deltaTime and call an update function
// with scaled delta time (speed multiplier at this+0x28).
// This appears to be part of a timed effect system (e.g., particle lifespan, animation duration).
class TimedEffect {
    // Offsets (relative to this):
    // +0x00: vtable pointer (or unknown base)
    // +0x18: int elapsedTime – accumulated time in engine units (likely ms)
    // +0x28: float speedMultiplier – scales deltaTime passed to child update
    // Other members unknown

public:
    void __thiscall update(int param1, int param2, int deltaTime) {
        // Increment internal timer
        *(int *)(this + 0x18) += deltaTime;

        // Call internal update routine; param1 and param2 might be context IDs or pointers.
        // The third argument is deltaTime scaled by the speed multiplier.
        // FUN_008d7c90 is likely a virtual method or a static function handling actual animation/effect logic.
        FUN_008d7c90(param1, param2, (float)deltaTime * *(float *)(this + 0x28));
    }
};