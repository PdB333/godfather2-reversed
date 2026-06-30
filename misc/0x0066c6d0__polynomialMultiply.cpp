// FUNC_NAME: polynomialMultiply
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// Input descriptor for a polynomial with 28-bit coefficients
typedef struct {
    int32_t count;           // +0x00: number of coefficients
    int32_t pad[2];          // +0x04, +0x08: padding
    uint32_t* data;          // +0x0C: pointer to coefficient array
} BigIntPoly;

// Result structure: allocated size (in 32-bit words), actual used length, and data pointer
typedef struct {
    uint32_t allocatedSize;  // +0x00: number of allocated words
    uint32_t usedLength;     // +0x04: actual length without leading zeros
    uint32_t* data;          // +0x08: pointer to result buffer
} BigIntPolyResult;

// Multiplies two polynomials with coefficients modulo 2^28 (28-bit limbs)
// Returns 0 on success, -2 on memory allocation failure
int32_t polynomialMultiply(const BigIntPoly* input, BigIntPolyResult* output) {
    int32_t count = input->count;
    uint32_t* inputData = input->data;

    // Raw result length: count*2 + 1 (to accommodate carry)
    uint32_t rawLen = count * 2 + 1;

    // Align size to a multiple of 64 (for cache or alignment purposes)
    uint32_t remainder = rawLen & 0x8000003F; // sign-agnostic remainder mod 64 (decompiler artifact)
    if ((int32_t)remainder < 0) {
        remainder = (remainder - 1 | 0xFFFFFFC0) + 1;
    }
    uint32_t allocSize = rawLen + (0x80 - remainder);

    // Allocate result buffer (zeroed)
    uint32_t* result = (uint32_t*)calloc(allocSize, sizeof(uint32_t));
    if (result == NULL) {
        return -2;
    }

    // Outer loop: for each coefficient of the first polynomial
    for (int32_t i = 0; i < count; ++i) {
        uint32_t ai = inputData[i];
        uint32_t carry = 0;

        // Multiply by ai and accumulate into result[i..i+count-1]
        for (int32_t j = i; j < count; ++j) {
            uint64_t product = (uint64_t)ai * inputData[j];
            // Double the product? (decompiled shows multiplication by 2)
            product *= 2;

            uint64_t sum = (uint64_t)result[j - i] + product + carry;
            carry = (uint32_t)(sum >> 28);  // 28-bit limb; carry is upper bits
            result[j - i] = (uint32_t)(sum & 0x0FFFFFFF);
        }

        // Propagate remaining carry through extra positions
        for (uint32_t idx = count - i; carry != 0; ++idx) {
            uint64_t sum = (uint64_t)result[idx] + carry;
            result[idx] = (uint32_t)(sum & 0x0FFFFFFF);
            carry = (uint32_t)(sum >> 28);
        }
    }

    // Trim leading zeros from the raw result
    uint32_t used = rawLen;
    uint32_t* ptr = result + rawLen - 1;
    while (used > 0 && *ptr == 0) {
        --used;
        --ptr;
    }

    // Fill output structure
    output->allocatedSize = allocSize;
    output->usedLength = used;
    output->data = result;

    return 0;
}