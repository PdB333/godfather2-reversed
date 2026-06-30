// FUNC_NAME: SimObject::savePreviousState
// Function address: 0x0049c9c0
// Copies a 4-byte value from offset +0x14 to +0x1c.
// Likely saves the "current" state (e.g., position, timestamp) as the "previous" state
// for interpolation or delta calculations. Called from many locations across the engine.

class SimObject {
public:
    // Field offsets (relative to this):
    // +0x14: int currentState;  // value to be copied
    // +0x1c: int previousState; // target for the copy

    void __thiscall savePreviousState() {
        // Copy the 4-byte value from offset 0x14 to offset 0x1c
        *(int*)((char*)this + 0x1c) = *(int*)((char*)this + 0x14);
    }
};