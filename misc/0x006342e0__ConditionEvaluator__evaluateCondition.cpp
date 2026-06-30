// FUNC_NAME: ConditionEvaluator::evaluateCondition

// Function at 0x006342e0
// Evaluates a condition by comparing a stored value with a given value.
// The condition type determines the comparison method.
// param_1: this pointer (ConditionEvaluator*)
// param_2: pointer to a value to compare against (value at offset +4)
// Returns: 1 if condition true, 0 otherwise.

uint ConditionEvaluator::evaluateCondition(int param_1, int param_2)
{
    // The condition data is stored as a pointer at offset 0 of this object.
    struct ConditionData {
        int type;   // +0x00: comparison type (0=int, 2=int, 3=float, 5=complex, 7=complex)
        int value;  // +0x04: value to compare (interpreted as int or float)
    };
    ConditionData* condData = *(ConditionData**)param_1;
    int type = condData->type;
    int condValue = condData->value;

    switch (type) {
    case 0:
        // Fall through to default (integer equality)
        goto defaultCase;
    default:
    case 2:
        // Integer equality
        return (uint)(condValue == *(int*)(param_2 + 4));
    case 3:
        // Float equality
        if (*(float*)&condValue != *(float*)(param_2 + 4)) {
            return 0;
        }
        return 1;
    case 5:
    case 7:
        // Complex comparison: if values don't match, try resolving a variable
        if (condValue != *(int*)(param_2 + 4)) {
            int resolvedVar = FUN_00633fb0(param_1); // resolve variable from context
            if (resolvedVar == 0) {
                return 0;
            }
            FUN_00633ac0(param_1, resolvedVar); // evaluate variable
            uint result = **(uint**)(param_1 + 8); // get result from variable resolver
            if (result == 0) {
                return 0;
            }
            if (result != 1) {
                return 1;
            }
            // result == 1: check additional condition
            if (*(uint**)(param_1 + 8)[1] == 0) {
                return 0;
            }
            return result;
        }
        // Values match, condition true
        return 1;
    }
}