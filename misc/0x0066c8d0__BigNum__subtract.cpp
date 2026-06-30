// FUNC_NAME: BigNum::subtract
// Function at 0x0066c8d0: Performs big integer subtraction with 28-bit digits (base 2^28).
// this stores the result, param_1 is left operand (subtrahend), param_2 is right operand (minuend).
// Operation: *this = param_2 - param_1 (right minus left)
// Fields: +0x00: numDigits, +0x04: maxDigits (capacity), +0x08: flags, +0x0C: digits (uint*, 28-bit per element)

class BigNum {
public:
    int numDigits;          // +0x00
    int maxDigits;          // +0x04
    uint flags;             // +0x08  (e.g., sign)
    uint* digits;           // +0x0C  (array of 28-bit digits stored in uint32)
};

// Forward declaration of the reallocation function (FUN_00667740)
// Returns non-zero on success, zero on failure
int BigNum_reallocate(BigNum* self, int newCapacity); // @ 0x00667740

// __thiscall BigNum::subtract(const BigNum* left, const BigNum* right)
// Returns 0 on success, non-zero on failure (reallocation failure)
int __thiscall BigNum_subtract(BigNum* this, const BigNum* left, const BigNum* right)
{
    int resultNumDigits;
    int leftNumDigits;
    int i;

    int temp;
    uint borrow;
    uint diff;
    int loopCount;
    int initialNumDigits;

    resultNumDigits = right->numDigits;
    leftNumDigits = left->numDigits;

    // Ensure result capacity can hold resultNumDigits, or try to reallocate
    if (resultNumDigits <= this->maxDigits || 
        (temp = BigNum_reallocate(this, resultNumDigits), temp == 0)) 
    {
        // Save old number of digits for later zero-fill
        initialNumDigits = this->numDigits;
        this->numDigits = resultNumDigits;

        const uint* leftDigits = left->digits;
        const uint* rightDigits = right->digits;
        uint* resultDigits = this->digits;

        borrow = 0;
        loopCount = 0;

        // Subtract overlapping digits with borrow
        if (leftNumDigits > 0) {
            for (i = 0; i < leftNumDigits; i++) {
                temp = leftDigits[i];
                diff = (uint)(rightDigits[i] - temp) - borrow;
                // Extract 28-bit digit
                resultDigits[i] = diff & 0x0FFFFFFF;
                // Compute borrow for next iteration (0 or 1)
                borrow = diff >> 31;
                loopCount = leftNumDigits;
            }
        }

        int remaining = resultNumDigits - loopCount;
        if (remaining > 0) {
            for (i = loopCount; i < resultNumDigits; i++) {
                diff = (uint)(rightDigits[i]) - borrow;
                resultDigits[i] = diff & 0x0FFFFFFF;
                borrow = diff >> 31;
            }
        }

        // Zero-fill extra positions if result became smaller than original capacity
        if (resultNumDigits < initialNumDigits) {
            int fillCount = initialNumDigits - resultNumDigits;
            for (i = resultNumDigits; i < resultNumDigits + fillCount; i++) {
                resultDigits[i] = 0;
            }
        }

        // Trim leading zero digits (normalization)
        int newNumDigits = this->numDigits;
        while (newNumDigits > 0 && resultDigits[newNumDigits - 1] == 0) {
            newNumDigits--;
        }
        this->numDigits = newNumDigits;

        if (newNumDigits == 0) {
            this->flags = 0;
        }

        return 0; // Success
    }

    // If capacity insufficient and reallocation failed, return failure code
    return 0; // Actually returns temp (0) from the reallocation call
}