// FUNC_NAME: RandomBigInt::generateNext

int RandomBigInt::generateNext(int* state, int* digitCountPtr, uint32_t multiplier) {
    int digitCount = *digitCountPtr;
    // Check if we have enough capacity for double-sized result (product of two n-digit numbers)
    if (state[1] < digitCount * 2) {
        int result = ensureCapacity(state);  // FUN_00667740, possibly reallocate digits
        if (result == 0) {
            return result;
        }
    }

    do {
        uint32_t* digits = (uint32_t*)state[3];  // +0x0C: pointer to limb array
        uint32_t* src = digits + digitCount;       // high part of state

        uint32_t carryOut = 0;
        for (int i = 0; i < digitCount; i++) {
            // 64-bit multiply: limb at src[i] * multiplier
            uint64_t product = (uint64_t)src[i] * (uint64_t)multiplier;
            uint32_t sum = (uint32_t)product + digits[i];
            // Carry is composed of:
            // - low 28-bit overflow (sum >> 28)
            // - high 32 bits of product shifted by 4 bits (multiplied by 16) 
            //   plus carry from the low addition
            uint32_t newCarry = (sum >> 28) | 
                                ((uint32_t)(product >> 32) + (sum < (uint32_t)product ? 1 : 0)) * 16;
            digits[i] = sum & 0x0FFFFFFF;  // store 28-bit limb
            carryOut = newCarry;
        }
        digits[digitCount] = carryOut;   // store final carry as next limb

        // Zero out remaining digits up to current length
        int originalLen = state[0];
        for (int k = digitCount + 1; k < originalLen; k++) {
            digits[k] = 0;
        }

        // Trim leading zeros (normalize)
        int newLen = originalLen;
        while (newLen > 0 && digits[newLen - 1] == 0) {
            newLen--;
        }
        state[0] = newLen;
        if (newLen == 0) {
            state[2] = 0;  // +0x08: clear extra field
        }

        // Check external randomness source
        int status = getNextRandomByte();  // FUN_00665c30
        if (status == -1) {
            return 0;  // source exhausted, stop generation
        }
        updateState(state);  // FUN_0066c8d0 - mix state further
    } while (true);
}