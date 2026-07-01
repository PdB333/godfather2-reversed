// FUNC_NAME: isDistanceLessThanThreshold
// Function at 0x007f81c0
// Checks if the squared distance between two entity positions (obtained from FUN_00471610) is <= radius squared.
// param_1 is likely a pointer to a structure containing references to two entities, or a "this" pointer for a manager.
// param_2 is the radius to compare.
// FUN_00471610 likely returns a transform pointer; position offsets at +0x30, +0x34, +0x38.

bool isDistanceLessThanThreshold(void* entityPair, float radius) {
    if (entityPair == nullptr) {
        return false;
    }

    // NOTE: Ghidra decompilation shows FUN_00471610() called with no arguments.
    // It is possible that FUN_00471610 actually takes entityPair as its argument,
    // or that it returns global transform pointers (e.g., player and target).
    // For reconstruction, we keep the calls as-is but document the ambiguity.
    void* transform1 = reinterpret_cast<void*>(FUN_00471610()); // +0x30 = x, +0x34 = y, +0x38 = z
    void* transform2 = reinterpret_cast<void*>(FUN_00471610());

    float dx = *reinterpret_cast<float*>((int)transform2 + 0x30) - *reinterpret_cast<float*>((int)transform1 + 0x30);
    float dy = *reinterpret_cast<float*>((int)transform2 + 0x34) - *reinterpret_cast<float*>((int)transform1 + 0x34);
    float dz = *reinterpret_cast<float*>((int)transform2 + 0x38) - *reinterpret_cast<float*>((int)transform1 + 0x38);

    float distSq = dx*dx + dy*dy + dz*dz;
    return distSq <= radius*radius;
}