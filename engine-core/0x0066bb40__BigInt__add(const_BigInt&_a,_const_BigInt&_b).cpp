// FUNC_NAME: BigInt::add(const BigInt& a, const BigInt& b)
// Address: 0x0066bb40
// This function adds two big integers (base 2^28) and stores the result in 'this'.
// The operands are passed by pointer to their digitCount fields.
// Member offsets:
// +0x00: digitCount (int32_t)
// +0x04: capacity (int32_t)
// +0x08: sign (int32_t, 0 when zero)
// +0x0C: digits (uint32_t*)

#include <cstdint>

class BigInt {
public:
    int32_t digitCount;
    int32_t capacity;
    int32_t sign;
    uint32_t* digits;

    // Reallocates or expands digit array to hold at least needed digits
    // Returns 0 on success, non-zero on failure
    int32_t ensureCapacity(int32_t needed);
};

int32_t BigInt::add(const BigInt& a, const BigInt& b) {
    BigInt* self = this;                        // in_EAX

    int32_t lenA = a.digitCount;                // *param_1
    int32_t lenB = b.digitCount;                // *param_2

    // Determine which operand is longer
    const uint32_t* shortDigits;
    const uint32_t* longDigits;
    int32_t minLen;
    int32_t maxLen;
    const BigInt* longerObj;

    if (lenB < lenA) {
        minLen = lenB;
        maxLen = lenA;
        shortDigits = b.digits;
        longDigits = a.digits;
        longerObj = &a;
    } else {
        minLen = lenA;
        maxLen = lenB;
        shortDigits = a.digits;
        longDigits = b.digits;
        longerObj = &b;
    }

    // Check capacity: need maxLen + 1 digits (for possible carry)
    if (!(maxLen + 1 <= self->capacity)) {
        if (self->ensureCapacity(maxLen + 1) != 0) {
            // Allocation failed; function returns 0 regardless (decompiler shows both paths return 0)
            return 0;
        }
    }

    int32_t oldDigitCount = self->digitCount;   // original for size changes
    self->digitCount = maxLen + 1;              // temporary maximum, will be trimmed

    uint32_t* result = self->digits;            // in_EAX[3]
    uint32_t carry = 0;

    // Sum common digits
    int32_t i = 0;
    while (i < minLen) {
        uint32_t sum = shortDigits[i] + longDigits[i] + carry;
        result[i] = sum & 0x0FFFFFFF;           // mask to 28 bits
        carry = sum >> 28;                      // carry for next digit
        i++;
    }

    // Add remaining digits from the longer operand
    while (i < maxLen) {
        uint32_t sum = longerObj->digits[i] + carry;
        result[i] = sum & 0x0FFFFFFF;
        carry = sum >> 28;
        i++;
    }

    // Store final carry (most significant digit)
    result[i] = carry;   // carry is at most 1 (for 28-bit base)

    // Trim leading zeros
    while (self->digitCount > 0 && result[self->digitCount - 1] == 0) {
        self->digitCount--;
    }

    // If result is zero, set sign to 0
    if (self->digitCount == 0) {
        self->sign = 0;
    }

    return 0;   // always returns 0 (no error condition exposed)
}