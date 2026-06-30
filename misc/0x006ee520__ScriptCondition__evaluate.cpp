// FUNC_NAME: ScriptCondition::evaluate
// Address: 0x006ee520
// The condition structure appears to hold two sub-conditions (each a pair of ints) and a type field (0=bool,1=int,2=float).
// param_2 is a reference value (likely context-dependent).
// Helper functions evaluate each sub-condition against param_2.
// Returns 1 (true) if both sub-conditions pass according to the type's logic, 0 otherwise.

// Helper function declarations (inferred from callees)
// FUN_006ebff0: returns char (bool) – likely checks a boolean sub-condition.
// FUN_006eb7b0: returns int – likely checks an integer sub-condition (e.g., equality or range).
// FUN_006eb7c0: returns float – likely retrieves a float value for comparison.

// Global constant used in float case (address 0x00d577a0)
const float FLOAT_SENTINEL = *(float*)0x00d577a0; // value unknown, likely FLT_MAX or similar

bool __thiscall ScriptCondition::evaluate(int* this, unsigned int refValue) {
    int type = *this; // +0x00
    int subCond1_a = this[1]; // +0x04
    int subCond1_b = this[2]; // +0x08
    int subCond2_a = this[3]; // +0x0C
    int subCond2_b = this[4]; // +0x10

    if (type == 0) {
        // bool-type condition
        char res1 = evaluateBoolCondition(subCond1_a, subCond1_b, refValue);
        char res2 = evaluateBoolCondition(subCond2_a, subCond2_b, refValue);
        // true when both return false (i.e., conditions are not met)
        if (res1 == 0 && res2 == 0) {
            return true;
        }
    } else if (type == 1) {
        // int-type condition
        int res1 = evaluateIntCondition(subCond1_a, subCond1_b, refValue);
        int res2 = evaluateIntCondition(subCond2_a, subCond2_b, refValue);
        // true when both return 0 (i.e., conditions are satisfied)
        if (res1 == 0) {
            if (res2 == 0) {
                return true;
            }
            return false;
        }
    } else if (type == 2) {
        // float-type condition
        float res1 = (float)evaluateFloatCondition(subCond1_a, subCond1_b, refValue);
        float res2 = (float)evaluateFloatCondition(subCond2_a, subCond2_b, refValue);
        // true when first result is 0.0 and second equals a sentinel value
        if ((res1 == 0.0f) && (res2 == FLOAT_SENTINEL)) {
            return true;
        }
    }
    return false;
}