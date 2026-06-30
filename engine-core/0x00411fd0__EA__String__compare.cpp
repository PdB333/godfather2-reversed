// FUNC_NAME: EA::String::compare
// Address: 0x00411fd0
// This function compares two wide-character strings (2-byte characters). 
// param_1 points to a structure with: +0x00: pointer to string data, +0x04: length or flag (0 = empty?).
// param_2 points to a null-terminated wide string (byte pointer to first character).
// Returns true if the strings are equal or when this string ends first (?) – see comments.
// The final return expression is ambiguous; likely a decompiler artifact for (bVar1 < *param_2).

struct EAString {
    wchar_t* data;   // +0x00
    uint32_t length; // +0x04 (or possibly boolean "is empty")
};

bool EA::String::compare(EAString* self, byte* other) {
    byte* thisPtr;
    uint8_t bVar1;
    bool bVar3;

    // If the other string is null or its first byte is zero (empty string)
    if ((other == (byte*)0x0) || (*other == 0)) {
        // Return true if this string's length field is zero (i.e., this string is also empty)
        return self->length == 0;
    }

    // If this string's length field is zero (empty) but other is non‑empty, return false
    if (self->length == 0) {
        return false;
    }

    thisPtr = (byte*)self->data; // treat data as byte array for comparison

    while (true) {
        bVar1 = *thisPtr;                     // first byte of this character
        bVar3 = bVar1 < *other;               // compare first bytes
        if (bVar1 != *other) break;           // if first bytes differ, exit loop

        // First bytes equal
        if (bVar1 == 0) {                     // both characters are null → end of strings
            return true;                      // equality
        }

        bVar1 = thisPtr[1];                   // second byte of this character
        bVar3 = bVar1 < other[1];             // compare second bytes
        if (bVar1 != other[1]) break;         // if second bytes differ, exit loop

        thisPtr += 2;                         // advance to next character
        other += 2;

        if (bVar1 == 0) {                     // second byte zero? Actually bVar1 holds the second byte,
            return true;                      // if zero → end of string (both characters zero since first was already zero? unreachable? preserved for accuracy)
        }
    }

    // After loop exit (characters differed) – this expression always evaluates to false in C.
    // It is likely intended to be: return (bVar1 < *other) ? true : false; (i.e., return bVar3)
    return 1 - bVar3 == (uint)(bVar3 != 0);
}