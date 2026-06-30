// FUNC_NAME: typeSafeCompare
// Function at 0x006229f0: Compares two objects using a type ID at offset 0 and a value at offset 4.
// Returns a 32-bit composite: lower byte = (value2 == other->value2), upper 24 bits = value2 >> 8 (from this object).
// If type IDs differ or are null, calls error handler (assertion failure).

uint32 __cdecl typeSafeCompare(const int* obj1, const int* obj2) {
    // obj1 and obj2 are passed via registers ESI/EDI (decompiler unaff_EDI/unaff_ESI)
    // obj1 corresponds to unaff_EDI, obj2 to unaff_ESI

    // Check type IDs at offset 0 (+0x00)
    if (obj1[0] == 0 || obj1[0] != obj2[0]) {
        // Assertion fail: type mismatch or null
        assertionFailure();
    }

    // Compare second field at offset 4 (+0x04)
    bool valuesEqual = (obj1[1] == obj2[1]);

    // Build return value: upper 24 bits = obj1[1] >> 8, lower 8 bits = equality flag
    uint32 result = (obj1[1] >> 8) & 0xFFFFFF;   // shift right 8, mask to 24 bits
    result = (result << 8) | (valuesEqual ? 1 : 0);

    return result;
}