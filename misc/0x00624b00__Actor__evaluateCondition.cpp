// FUNC_NAME: Actor::evaluateCondition
// Function at 0x00624b00: Evaluates a condition based on type (param_4) against the actor's state.
// Conditions:
//   Type 1: Returns true if actor's state flag (offset 0x20) is 0.
//   Type 2: Returns true if actor's health (float at offset 0x30) exceeds a given threshold (float at param_5+4).
//   Type 3: Returns true if actor's health exceeds global threshold DAT_00e2b05c.
//   Type 4: Always returns true.
//   Default: Returns false.

bool __thiscall Actor::evaluateCondition(int thisPtr, int unused1, int unused2, int conditionType, int comparisonData) {
    bool result = false;
    switch (conditionType) {
        case 1: // Check state flag
            return *(int *)(thisPtr + 0x20) == 0;
        case 2: // Compare health with given threshold
        {
            float health = *(float *)(thisPtr + 0x30);
            float threshold = *(float *)(comparisonData + 4);
            if (health < threshold || health == threshold) {
                return false;
            }
            break;
        }
        case 3: // Compare health with global constant
        {
            float health = *(float *)(thisPtr + 0x30);
            if (health <= DAT_00e2b05c) { // global threshold
                return false;
            }
            break;
        }
        case 4: // Always true
            break;
        default:
            goto switch_default;
    }
    result = true;
switch_default:
    return result;
}