// FUNC_NAME: ScriptValue::compare
// Function address: 0x00634150
// This function compares two ScriptValue objects (this and rhs) for an ordering relationship.
// The first int of each is a type tag (enum). Type-specific comparisons are performed.
// Returns 1 if the comparison (less-than-or-equal? see logic) holds, 0 otherwise.
// On type mismatch, an error is reported via FUN_00633920.

struct ScriptValue {
    int type;          // +0x00: type tag (e.g., 3 = float, 4 = unknown)
    union {
        float f;       // +0x04: float value for type 3
        int i;         // +0x04: integer/pointer value for other types
    } value;
};

// External helper functions (addresses inferred):
// FUN_00634030: generic comparison (returns -1, 0, 1 or -1 for error)
// FUN_006337e0: fallback comparison
// FUN_006340e0: comparison for type 4 (returns negative if less)
// FUN_00633920: error reporting function (takes context, format, ...)

int __thiscall ScriptValue::compare(ScriptValue* this, ScriptValue* rhs) {
    int lhsType = this->type;
    int rhsType = rhs->type;

    if (lhsType == rhsType) {
        // Same type: compare based on type
        if (lhsType == 3) {
            // Float comparison: return 1 if lhs <= rhs and they are not equal
            if (this->value.f <= rhs->value.f && rhs->value.f != this->value.f) {
                return 1;
            }
        } else if (lhsType == 4) {
            // Type 4: use specialized comparison; return 1 if result < 0
            int cmpResult = FUN_006340e0();
            return (cmpResult < 0) ? 1 : 0;
        } else {
            // Generic comparison
            uint cmpResult = FUN_00634030(this, rhs);
            if (cmpResult == 0xFFFFFFFF) {
                // If generic comparison fails, use fallback
                cmpResult = FUN_006337e0();
            }
            return cmpResult;
        }
    } else {
        // Type mismatch: attempt to compare type names? (third character of type string)
        // Global table PTR_DAT_00e2a89c maps type tags to type name strings.
        char* lhsTypeName = (char*)PTR_DAT_00e2a89c[lhsType];
        char* rhsTypeName = (char*)PTR_DAT_00e2a89c[rhsType];
        if (lhsTypeName[2] == rhsTypeName[2]) {
            // If the third character (likely a category byte) matches, report error
            FUN_00633920(this, "attempt to compare two %s values", lhsTypeName);
        } else {
            // Different categories: report error with both type names
            FUN_00633920(this, "attempt to compare %s with %s", lhsTypeName, rhsTypeName);
        }
    }
    return 0;
}