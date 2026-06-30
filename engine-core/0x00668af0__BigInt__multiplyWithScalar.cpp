// FUNC_NAME: BigInt::multiplyWithScalar
// Function address: 0x00668af0
// Performs in-place multiplication of a big integer (param_1) by another big integer (param_2)
// and a scalar factor (param_3). The result replaces param_1.
// Uses 28-bit limbs (masked with 0x0FFFFFFF) to allow carry propagation with 4 spare bits.

#include <cstdint>

struct BigInt {
    int32_t size;       // +0x00: number of limbs
    int32_t capacity;   // +0x04: allocated limb count
    int32_t flags;      // +0x08: internal flags (e.g. zero flag)
    uint32_t* digits;   // +0x0C: pointer to limb array
};

extern "C" int64_t __allmul(int64_t a, int64_t b); // compiler helper

// Forward declarations
int32_t fastMultiply(BigInt* result, BigInt* multiplier, uint32_t scalar); // FUN_00664fa0
int32_t ensureCapacity(int32_t needed); // FUN_00667740, returns 0 if OK
void freeBigInt(int32_t size); // FUN_0066a4d0, frees temporary? 
int32_t checkReductionState(); // FUN_00665c30, returns -1 if reduction not needed
int32_t reduceBigInt(BigInt* value); // FUN_0066c8d0, final reduction step

int32_t BigInt::multiplyWithScalar(BigInt* result, BigInt* multiplier, uint32_t scalar) {
    // Fast path: if product size fits in a small buffer
    int32_t newSize = multiplier->size * 2 + 1;
    if (newSize < 0x200 && multiplier->size < 0x100) {
        return fastMultiply(result, multiplier, scalar);
    }

    // Ensure result has sufficient capacity
    if (newSize <= result->capacity || ensureCapacity(newSize) == 0) {
        result->size = newSize;

        // Initialize the result limb array to zero (implicitly done by the algorithm)
        // Outer loop: iterate over each multiplier limb (j)
        for (int32_t j = 0; j < multiplier->size; ++j) {
            uint32_t* resPtr = result->digits + j;
            uint32_t multiplicandDigit = *resPtr; // original digit from result (the multiplicand)
            uint32_t* mulPtr = multiplier->digits;

            uint32_t carry = 0;
            // Inner loop: multiply each multiplier limb by the current multiplicand digit and scalar
            for (int32_t i = 0; i < multiplier->size; ++i) {
                uint64_t product = (uint64_t)(*mulPtr) * (uint64_t)(multiplicandDigit * scalar);
                // __allmul does not exist in portable C++; use direct 64-bit multiplication
                // uVar9 = __allmul(*local_18, 0, uVar1 * param_3 & 0xfffffff, 0);
                // Equivalent to product = (uint64_t)((*mulPtr) & 0x0FFFFFFF) * (uint64_t)((multiplicandDigit * scalar) & 0x0FFFFFFF)
                uint64_t mul = (uint64_t)(*mulPtr & 0x0FFFFFFF) * (uint64_t)((multiplicandDigit * scalar) & 0x0FFFFFFF);
                
                uint32_t oldDigit = *resPtr;
                uint64_t sum = mul + oldDigit + carry;
                *resPtr = (uint32_t)(sum & 0x0FFFFFFF);
                carry = (uint32_t)(sum >> 28);
                
                // Correct the carry handling based on the original code:
                // uVar6 = uVar5 + uVar7; where uVar5 = (uint)uVar9 + uVar2, uVar7 is old carry
                // Then uVar7 = uVar6 >> 0x1c | ...; This code matches.
                // The extra complicated part: ((int)((ulonglong)uVar9 >> 0x20) + ...) * 0x10
                // That term accounts for the high 32 bits of the 64-bit product (if any).
                // In our simplified version, we assume the high bits are zero because we masked to 28 bits.
                // However, the original mask is applied to *mulPtr and to (uVar1*scalar) separately.
                // Given the mask, both are < 2^28, so product < 2^56, and the high 8 bits of the 64-bit product are zero.
                // So the carry propagation is simply sum >> 28.
                // To be safe, reimplement the exact logic:
                // product = (uint64_t)(*mulPtr) * (uint64_t)( (multiplicandDigit * scalar) & 0x0FFFFFFF );
                // But the original uses: __allmul(*local_18,0,uVar1 * param_3 & 0xfffffff,0)
                // That means the first operand is a 64-bit value with low 32 bits = *mulPtr, high = 0.
                // Second operand low 32 = (uVar1 * scalar) & 0x0FFFFFFF, high = 0.
                // So it's a 32x32 -> 64 multiplication.
                // We'll use uint64_t cast.
                // Also note the original carry calculation involves the high 32 bits of the product.
                // We'll preserve that using __allmul behavior.
                // For portability, we can manually compute:
                uint32_t mulLow = *mulPtr;
                uint32_t mulHigh = 0; // since __allmul second argument is 0
                uint32_t scalarLow = (multiplicandDigit * scalar) & 0x0FFFFFFF;
                uint32_t scalarHigh = 0;
                // 64-bit multiply:
                uint64_t fullProduct = (uint64_t)mulLow * (uint64_t)scalarLow;
                uint32_t prodLow = (uint32_t)fullProduct;
                uint32_t prodHigh = (uint32_t)(fullProduct >> 32);
                // Now the sum:
                uint32_t tempSum = prodLow + oldDigit;
                uint32_t resultDigit = tempSum + carry;
                carry = (resultDigit >> 28) | ( (prodHigh + (tempSum < oldDigit ? 1 : 0) + (resultDigit < tempSum ? 1 : 0)) << 4 );
                // This is exactly the code: uVar7 = uVar6 >> 0x1c | ((int)((ulonglong)uVar9 >> 0x20) + (uint)CARRY4((uint)uVar9,uVar2) + (uint)CARRY4(uVar5,uVar7)) * 0x10;
                // Simplified: carry = (resultDigit >> 28) | ((prodHigh + (tempSum < oldDigit) + (resultDigit < tempSum)) << 4);
                // But the mask is 0x0FFFFFFF, so it's equivalent to shifting right 28.
                // I'll use the clearer version.
                
                resPtr++;
                mulPtr++;
            }

            // Propagate remaining carries beyond the current limb row
            while (carry != 0) {
                *resPtr = *resPtr + carry;
                carry = *resPtr >> 28;
                *resPtr &= 0x0FFFFFFF;
                resPtr++;
            }

            // Reset iVar3 for next iteration (in original code it's reloaded each time)
        }

        // Trim leading zero limbs from result
        while (result->size > 0 && result->digits[result->size - 1] == 0) {
            result->size--;
        }
        if (result->size == 0) {
            result->flags = 0; // set zero flag
        }

        // Cleanup and final reduction
        freeBigInt(multiplier->size); // may free temporary buffers

        int32_t reduceFlag = checkReductionState();
        if (reduceFlag != -1) {
            return reduceBigInt(result);
        }
    }
    return 0; // failure
}