// FUNC_NAME: compareAngleKeyStructs
//
// Address: 0x0056dfd0
// Role: Compares two 20-byte structures (likely a key with an angle field) for equality.
//       Uses bitwise sign masking on float difference to get absolute value, then compares
//       against a tolerance. Returns 1 if all fields match.

#pragma pack(push, 4)
struct AngleKeyStruct {
    int   id;        // +0x00
    int   pad;       // +0x04 – not used in comparison
    float angle;     // +0x08
    int   field3;    // +0x0C
    int   field4;    // +0x10
};
#pragma pack(pop)

// DAT_00e44680 likely holds 0x7FFFFFFF (mask for sign bit)
// DAT_00e2e780 likely holds a small tolerance value (e.g., 0.01f)
bool __fastcall compareAngleKeyStructs(AngleKeyStruct* thisPtr, AngleKeyStruct* otherPtr)
{
    // Compare the first integer field (ID)
    if (thisPtr->id != otherPtr->id) {
        return false;
    }

    // Compare angles with tolerance using absolute value via sign-bit masking
    float angleDiff = thisPtr->angle - otherPtr->angle;
    uint32_t diffBits = *(uint32_t*)&angleDiff;
    uint32_t absMask  = 0x7FFFFFFF;                    // preserve magnitude, clear sign
    float absDiff     = *(float*)&(diffBits & absMask); // reinterpret as float (positive)

    float tolerance = 0.01f;                           // approximate (DAT_00e2e780)
    if (absDiff >= tolerance) {                       // original "<", so reject if not less
        return false;
    }

    // Compare remaining two fields
    if (thisPtr->field3 != otherPtr->field3) {
        return false;
    }
    if (thisPtr->field4 != otherPtr->field4) {
        return false;
    }

    return true;
}