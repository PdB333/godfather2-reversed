// FUNC_NAME: BigInt::divideByUint32
// Function address: 0x00666670
// Purpose: Divide a big integer (stored in this) by a 32-bit divisor.
//   Returns quotient (overwrites the digits in place) and remainder via param_4.
//   Special cases: divisor == 0 -> -3; divisor == 1 or number is zero -> trivial.
//   Uses internal helper to find highest non-zero digit for optimization.

struct BigInt { // +0x00: int numDigits; +0x04: int unknown; +0x08: int accumulator; +0x0C: uint32* digits
    int numDigits;
    int field_4; // unknown, possibly padding or used internally
    int accumulator;
    uint32* digits;
};

// Forward declarations of helper functions (not provided but assumed)
int __fastcall getHighestNonZeroDigit(BigInt* self, int* outIndex); // FUN_00666640 - returns 1 if found, outputs index
int __fastcall extractRange(BigInt* self, int index, int param, uint32* outMask); // FUN_00666300 - extracts bits based on index
int __fastcall quickDivByThree(BigInt* self, int param, uint32* outRem); // FUN_006664b0 - optimization for divisor == 3
int __fastcall checkErrorState(); // FUN_006678c0 - checks some error flag
int __fastcall storeResult(int param); // FUN_00665b10 - stores result
int __fastcall finalize(); // FUN_00666970 - finalize operation
void __fastcall cleanup(); // FUN_00665b40 - cleanup after division
int __fastcall trivialRandom(); // FUN_00665ce0 - returns 0 for trivial case

int __fastcall BigInt::divideByUint32(BigInt* self, uint32 divisor, int outputBuffer, uint32* outRemainder)
{
    int result;
    int highestIndex;
    uint32 mask;

    if (divisor == 0) {
        return -3; // division by zero
    }

    // Trivial cases: divisor == 1 or self is zero (numDigits == 0)
    if (divisor == 1 || self->numDigits == 0) {
        if (outRemainder != nullptr) {
            *outRemainder = 0;
        }
        if (outputBuffer != 0) {
            // Return some trivial random value? (call to FUN_00665ce0)
            return trivialRandom();
        }
        return 0;
    }

    // Non-trivial division
    result = getHighestNonZeroDigit(self, &highestIndex);
    if (result == 1) {
        // Fast path: extract bits based on the highest non-zero digit
        if (outRemainder != nullptr) {
            // Compute mask: (1 << (highestIndex & 0x1f)) - 1, then AND with self->digits[3]? Wait: self->digits[3] doesn't make sense.
            // The decompiled code does: *(uint *)(param_1[3] + ???)
            // Actually it used *(uint *)param_1[3]? No, it was: *param_4 = (1 << ((byte)local_14 & 0x1f)) - 1U & *(uint *)param_1[3];
            // param_1[3] is the pointer to digits, but it's dereferenced as a single uint? That seems incorrect.
            // Probably the intended code: *param_4 = ((1 << (highestIndex & 0x1f)) - 1) & self->digits[0]; // mask with first digit?
            // But that's still odd. Maybe it's a different interpretation: highestIndex is used to set bitmask for remainder.
            // We'll follow the decompiled logic closely with comments.
            uint32 rawMask = (1 << (highestIndex & 0x1f)) - 1;
            // self->digits is a uint32*, but the code reads *(uint *)(self->digits) which would be the first digit.
            // However the original had param_1[3] which is the pointer itself, so reading *param_1[3] gets the first digit.
            *outRemainder = rawMask & *(uint32*)self->digits;
            // Note: this is likely a bug or confusion; we preserve the logic.
        }
        if (outputBuffer != 0) {
            // Extract a range of bits from the big integer using highestIndex
            return extractRange(self, highestIndex, outputBuffer, 0);
        }
    } else {
        // Fallback: if getHighestNonZeroDigit returned 0 (meaning number is zero? but we already checked)
        if (divisor == 3) {
            // Optimization for division by 3
            return quickDivByThree(self, outputBuffer, outRemainder);
        }

        // Check error state
        int error = checkErrorState();
        if (error != 0) {
            return error;
        }

        // Perform general multi-precision division by a single digit divisor
        int numDigits = self->numDigits;
        int accumulator = self->accumulator; // used as high part
        uint32 remainderLow = 0; // low part of remainder (64-bit)
        int remainderHigh = 0;   // high part of 64-bit remainder (actually stores the high word beyond low)
        int index = numDigits;

        // Division loop: process digits from most significant to least
        while (index--) {
            // Combine current remainder with next digit (shift in 32 bits, but actually we shift by 28? The code uses <<0x1c (28) and >>4? That is odd.)
            // The decompiled code uses shifts of 0x1c (28 bits) and 4 bits? That might be a decompiler artifact due to 64-bit handling.
            // Actually the original code likely maintained a 64-bit accumulator: (remainderHigh:remainderLow) shifted left by 32 bits per digit.
            // But due to decompilation, it's split into two 32-bit chunks with 28-bit shifts? That doesn't match standard bigint division.
            // We'll follow the original logic as reconstructed.
            // Let uVar3 = high part (remainderHigh) shifted left by 28? or combined.
            // Actually the expression: uVar3 = iVar1 << 0x1c | uVar4 >> 4; is unusual.
            // Given typical bigint division, it's more like: combine the current 64-bit remainder (iVar1:uVar4) with the next digit.
            // The shift amounts (28 and 4) might be a result of using 64-bit intrinsic that doesn't match the actual algorithm.
            // We'll keep the original arithmetic to preserve correctness.
            uint32 combinedHigh = (uint32)((remainderHigh << 0x1c) | (remainderLow >> 4));
            uint32 combinedLow = self->digits[index] | (remainderLow << 0x1c);

            uint32 quotientDigit;
            if (combinedHigh == 0 && combinedLow < divisor) {
                quotientDigit = 0;
                remainderHigh = 0;
                remainderLow = combinedLow;
            } else {
                // Full 64-bit division: combinedHigh:combinedLow / divisor
                uint64 dividend = ((uint64)combinedHigh << 32) | combinedLow;
                uint64 quotient = dividend / divisor;
                uint64 product = quotient * divisor;
                uint64 newRem = dividend - product;
                quotientDigit = (uint32)quotient;
                remainderHigh = (uint32)(newRem >> 32);
                remainderLow = (uint32)(newRem);
            }

            // Store quotient digit into output buffer (assumed to be the same array? But outputBuffer is an int, possibly a buffer pointer)
            // The decompiled code used: *(undefined4 *)(local_4 + index * 4) = uVar2;
            // local_4 was uninitialized; we assume outputBuffer is that pointer.
            if (outputBuffer != 0) {
                ((uint32*)outputBuffer)[index] = quotientDigit;
            } else {
                // If no output buffer, quotient overwrites self->digits? The original code didn't have a separate buffer.
                // Maybe outputBuffer is the same as self->digits in some calls? We'll store into self->digits as fallback.
                self->digits[index] = quotientDigit;
            }
        }

        // After loop, remainder is in (remainderHigh:remainderLow), but remainderHigh should be 0 for single-word divisor.
        if (outRemainder != nullptr) {
            *outRemainder = remainderLow;
        }

        // Post-processing: call FUN_00665b10 and FUN_00666970 if outputBuffer is non-zero? The original code:
        // if (param_3 != 0) { FUN_00665b10(); FUN_00666970(); }
        // Probably these functions finalize the output buffer.
        if (outputBuffer != 0) {
            storeResult(outputBuffer);
            finalize();
        }

        // Cleanup
        cleanup();
    }

    return 0;
}