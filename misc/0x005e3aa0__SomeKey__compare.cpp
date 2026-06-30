// FUNC_NAME: SomeKey::compare
// Function address: 0x005e3aa0
// Role: Compare two key structures for equality with tolerance on floating-point fields.
// Returns 0 if equal (same type and floating-point values within epsilon), 1 otherwise.

// External constants from data section (assumed)
extern const uint32 kAbsMask = 0x7FFFFFFF;   // Mask for absolute value of float bit difference (likely DAT_00e44680)
extern const float kEpsilon = 0.001f;        // Tolerance for float comparison (likely DAT_00e44598)

struct SomeKey {
    int32  type;      // +0x00: Key type identifier
    float  values[4]; // +0x04: Four floating-point values (e.g., position components)
};

// Compare two keys: type must match exactly; each float must be within epsilon (using ULP tolerance via bit masking).
int __fastcall SomeKey::compare(const SomeKey* other) const {
    // ECX points to this, EDX points to other? Actually param_1 is this, in_EAX is other.
    // But decompiler shows param_1 as first pointer, in_EAX as second.
    // We'll treat it as a member function with one explicit parameter (other).
    // However, the signature shows __fastcall with one param, so we adapt.

    // Check type equality
    if (this->type != other->type) {
        return 1; // Not equal
    }

    // Check each float using ULP comparison
    for (int i = 0; i < 4; ++i) {
        float diff = this->values[i] - other->values[i];
        uint32 absDiffBits = reinterpret_cast<uint32&>(diff) & kAbsMask;
        if (reinterpret_cast<float&>(absDiffBits) >= kEpsilon) {
            return 1; // Difference exceeds tolerance
        }
    }

    return 0; // Equal within tolerance
}