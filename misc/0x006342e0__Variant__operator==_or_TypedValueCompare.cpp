// FUNC_NAME: Variant::operator== or TypedValueCompare
// Address: 0x006342e0
// Compares two typed values (type stored at +0x00, value at +0x04)
// param_1: context object (used for resolution in reference types), param_2: pointer to other value structure
// Returns non-zero if equal, zero otherwise

typedef unsigned int uint;

uint __thiscall TypedValueCompare(int param1, int param2)
{
    // Assume 'this' is passed via ESI; treat as fields at offset 0 and 4
    struct TypedValue {
        int type;       // +0x00: 0,2,3,5,7
        union {
            int i;
            float f;
        } value;        // +0x04
    };

    TypedValue* thisVal;
    TypedValue* otherVal;

    thisVal = (TypedValue*) /*ESI*/; // implicit this
    otherVal = (TypedValue*) param2;

    switch (thisVal->type) {
    case 0:
        goto default_return;
    default:
        return (uint)(thisVal->value.i == otherVal->value.i);
    case 2:
        return (uint)(thisVal->value.i == otherVal->value.i);
    case 3:
        if (thisVal->value.f != otherVal->value.f) {
            return 0;
        }
        return 1;
    case 5:
    case 7: {
        // Reference types: if values differ, resolve and check further
        if (thisVal->value.i != otherVal->value.i) {
            int resolved = FUN_00633fb0(param1); // resolve reference?
            if (resolved == 0) {
                return 0;
            }
            FUN_00633ac0(param1, resolved); // additional step
            uint* pFlags = *(uint**)(param1 + 8);
            if (pFlags == 0) {
                return 0;
            }
            if (*pFlags != 1) {
                return 1;
            }
            // If flag is 1, check second uint
            if (pFlags[1] == 0) {
                return 0;
            }
            return 1;
        }
        // Fall through to return 1 if values equal
        }
    }
    return 1; // from switch default/fallthrough
}