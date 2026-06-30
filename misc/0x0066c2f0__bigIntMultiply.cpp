// FUNC_NAME: bigIntMultiply
#include <cstdint>
#include <cstdlib>
#include <cstring>

struct BigIntInput {
    uint32_t length;       // number of digits (0x00)
    uint32_t unknown1;     // +0x04
    uint32_t unknown2;     // +0x08
    uint32_t* digits;      // +0x0C pointer to digit array
};

struct BigIntOutput {
    uint64_t info;         // +0x00: (allocSize << 32) | usedLength
    uint64_t bufferContainer; // +0x08: buffer pointer in high 32 bits (low 32 unused)
};

// Forward declaration of helper for small multiplications
int32_t smallBigIntMultiply(BigIntInput* multiplier, undefined8* param_3, uint32_t maxResultDigits);

int32_t bigIntMultiply(BigIntInput* multiplicand,
                       BigIntInput* multiplier,
                       BigIntOutput* result,
                       uint32_t maxResultDigits)
{
    uint32_t allocSize;
    uint32_t carry;
    uint32_t multiplicandLen;
    uint32_t multiplierLen;
    uint32_t maxDigits;
    int32_t i, j;
    uint32_t* resultDigits;
    uint64_t mul64;
    uint32_t temp, newCarry;
    uint32_t resultDigit;

    // If maxResultDigits is small (<0x200) and lengths are below threshold, use simpler path
    if ((int32_t)maxResultDigits < 0x200) {
        multiplicandLen = multiplicand->length;
        multiplierLen = multiplier->length;
        if ((int32_t)multiplierLen > (int32_t)multiplicandLen) {
            multiplicandLen = multiplierLen;
        }
        if ((int32_t)multiplicandLen < 0x100) {
            return smallBigIntMultiply(multiplier, (undefined8*)result, maxResultDigits);
        }
    }

    // Align allocation size to 64-byte boundary (mask 0x8000003f with sign adjustment)
    uint32_t align = maxResultDigits & 0x8000003f;
    if ((int32_t)align < 0) {
        align = (align - 1 | 0xffffffc0) + 1;
    }
    allocSize = (maxResultDigits - align) + 0x80; // number of uint32_t digits to allocate

    resultDigits = (uint32_t*)calloc(allocSize, sizeof(uint32_t));
    if (resultDigits == nullptr) {
        return -2; // 0xfffffffe
    }

    // Main schoolbook multiplication: outer loop over multiplicand digits
    multiplicandLen = multiplicand->length;
    result->info = ((uint64_t)allocSize << 32) | maxResultDigits;
    i = 0;
    maxDigits = maxResultDigits;

    if ((int32_t)multiplicandLen > 0) {
        do {
            carry = 0;
            multiplierLen = multiplier->length;
            if ((int32_t)maxDigits < (int32_t)multiplierLen) {
                multiplierLen = maxDigits;
            }
            uint32_t multiplicandDigit = multiplicand->digits[i];
            uint32_t* mulDigitPtr = multiplier->digits;
            uint32_t* resDigitPtr = resultDigits + i;

            j = 0;
            if ((int32_t)multiplierLen > 0) {
                do {
                    mul64 = (uint64_t)multiplicandDigit * (uint64_t)(*mulDigitPtr);
                    temp = (uint32_t)mul64;
                    resultDigit = temp + *resDigitPtr;
                    newCarry = resultDigit + carry;
                    // New carry: high 32 bits of 64-bit sum + possible carry from low 28 bits?
                    // The original code uses shifting by 28 bits (0x1c) and masking 0xfffffff (28-bit digits?)
                    // This suggests the digits are stored in 28-bit limbs (0xfffffff = 2^28-1).
                    // The carry propagation is done with 28-bit digit size.
                    carry = (newCarry >> 28) | 
                            (((uint32_t)(mul64 >> 32) + (uint32_t)(temp < *resDigitPtr ? 1 : 0) + (uint32_t)(carry > resultDigit ? 1 : 0)) << 4);
                    *resDigitPtr = newCarry & 0xfffffff;
                    mulDigitPtr++;
                    resDigitPtr++;
                    j++;
                    multiplierLen--;
                } while (multiplierLen != 0);
            }

            // If we didn't reach the end of the result array, store final carry as a digit
            if ((int32_t)(j + i) < (int32_t)maxResultDigits) {
                *resDigitPtr = carry;
            }

            maxDigits--;
            i++;
        } while (i < (int32_t)multiplicandLen);
    }

    // Trim leading zero digits from the result
    if ((int32_t)maxResultDigits > 0) {
        int32_t* digit = (int32_t*)(resultDigits + maxResultDigits - 1);
        while (*digit == 0 && (int32_t)maxResultDigits > 0) {
            maxResultDigits--;
            digit--;
        }
        result->info = ((uint64_t)allocSize << 32) | maxResultDigits;
    }

    // Store the result buffer and free any old buffer
    uint64_t oldInfo = result->info;
    void* oldBuffer = (void*)(result->bufferContainer >> 32);
    result->info = ((uint64_t)allocSize << 32) | maxResultDigits;
    result->bufferContainer = (uint64_t)resultDigits << 32;

    if (oldBuffer != nullptr) {
        // Clear and free old buffer (length from oldInfo low 32 bits)
        uint32_t oldLength = (uint32_t)oldInfo;
        memset(oldBuffer, 0, oldLength * sizeof(uint32_t));
        free(oldBuffer);
    }

    return 0;
}