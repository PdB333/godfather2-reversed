// FUNC_NAME: EARSVariant::operator==
// Address: 0x00636800
// Compares two variant values by type discriminator and value union.

enum EARSVariantType : int {
    kTypeNone  = 0,   // null/void type – always equal if both same type
    kTypeFloat = 3,   // value stored as float
    // other types are treated as integer
};

struct EARSVariant {
    int               type;   // +0x00 discriminator
    union {
        int   intValue;       // +0x04
        float floatValue;     // +0x04
    } value;
};

// __fastcall: first argument in ECX, second in EDX
bool __fastcall operator==(const EARSVariant* thisVariant, const EARSVariant* otherVariant) {
    // Quick type mismatch test
    if (thisVariant->type != otherVariant->type) {
        return false;
    }

    // Based on type, compare the value field appropriately
    switch (thisVariant->type) {
    case kTypeNone:         // type 0: always equal (presumably “null”)
        return true;

    default:                // integer types: compare as signed integers
        return thisVariant->value.intValue == otherVariant->value.intValue;

    case kTypeFloat:        // type 3: compare as floats
        // Fall through to float comparison outside switch
        break;
    }

    // Float comparison for kTypeFloat
    if (thisVariant->value.floatValue != otherVariant->value.floatValue) {
        return false;
    }
    return true;
}