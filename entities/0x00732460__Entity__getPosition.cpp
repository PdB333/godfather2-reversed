// FUNC_NAME: Entity::getPosition
// Address: 0x00732460
// This function retrieves the 3D position of an entity (likely player or camera target).
// It outputs to a Vector3 struct (float[3]). The offset 0x1c78 is a state/type field;
// if it's non-zero and not 0x48 (likely "invalid" or "none"), or if param_force is true,
// it fetches position from a global source (FUN_00471610) with a height offset added.
// Otherwise, the output is zeroed.

struct Vector3 {
    float x, y, z;
};

// External global height offset (e.g., eye height or world adjustment)
extern float g_HeightOffset; // _DAT_00d62be0

// External function that returns a pointer to a structure containing position data
// (e.g., player camera or entity base position). Offsets: +0x30 = x, +0x34 = y, +0x38 = z
extern int* getPositionSource(); // FUN_00471610

void __thiscall Entity::getPosition(int thisPtr, Vector3* outPos, bool bForce) {
    // Zero the output by default
    outPos->x = 0.0f;
    outPos->y = 0.0f;
    outPos->z = 0.0f;

    // Check condition: either bForce is true, or the state at +0x1c78 is valid (non-zero and not 0x48)
    int state = *(int*)(thisPtr + 0x1c78);
    if (bForce || (state != 0 && state != 0x48)) {
        int* source = getPositionSource(); // returns pointer to a struct with position at +0x30
        outPos->x = *(float*)(source + 0x30);        // +0x30: x
        outPos->y = *(float*)(source + 0x34) + g_HeightOffset; // +0x34: y + height offset
        outPos->z = *(float*)(source + 0x38);        // +0x38: z
    }
}