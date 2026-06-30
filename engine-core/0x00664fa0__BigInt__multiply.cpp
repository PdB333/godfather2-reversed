// FUNC_NAME: BigInt::multiply
int BigInt::multiply(const BigInt* multiplier, int scalarMultiplier)
{
    // Check if result will fit in capacity; if not, attempt to grow the digit array via FUN_00667740
    if ((multiplier->digitCount + 1 <= this->capacity) || (growCapacityAndRetry(this, multiplier), 1)) // Inline: FUN_00667740
    {
        // Allocate temporary stack storage for the intermediate result (64 bits per digit)
        int aCount = this->digitCount;
        int bCount = multiplier->digitCount;
        int maxResultPairs = (bCount * 2) + 1; // maximum possible digit pairs after convolution (each 64-bit)
        int pairsNeeded = (aCount > maxResultPairs) ? aCount : maxResultPairs;

        // Use alloca to allocate dynamic stack space (as in original code)
        uint32_t* temp = (uint32_t*)alloca(pairsNeeded * 2 * sizeof(uint32_t)); // each pair is low + high uint32

        // Initialize temp with zeros (the stack isn't zeroed, so we clear it)
        memset(temp, 0, pairsNeeded * 2 * sizeof(uint32_t));

        // Copy this->digits into temp, storing each 28-bit digit as a 64-bit pair (low 32 bits = digit, high 32 bits = 0)
        for (int i = 0; i < aCount; i++)
        {
            temp[i * 2] = this->digits[i];       // low word
            temp[i * 2 + 1] = 0;                // high word
        }

        // Extend temp to maxResultPairs pairs by filling with zeros (already done by memset)

        // Main convolution: for each digit of this (a), multiply by each digit of multiplier (b) scaled by scalarMultiplier
        // Outer loop iterates over a digits (only first bCount digits are used, as per original code)
        uint32_t* aPtr = temp;                  // points to current a digit pair
        for (int aIdx = 0; aIdx < bCount; aIdx++) // outer loop runs bCount times (processes only first bCount a digits)
        {
            uint32_t aDigitLow = aPtr[0];       // low word of current a digit
            uint32_t aDigitHigh = aPtr[1];     // high word (should be 0 initially)

            uint32_t* bDigits = multiplier->digits; // pointer to b digits
            uint32_t* resultPtr = aPtr;         // start adding to position of current a digit

            // Inner loop over all b digits
            for (int bIdx = 0; bIdx < bCount; bIdx++)
            {
                uint32_t bDigit = bDigits[bIdx];
                // 64-bit product = bDigit * (aDigitLow * scalarMultiplier) truncated to 28 bits
                // Use 64-bit multiplication via __allmul (emulated here with uint64_t)
                uint64_t product = (uint64_t)bDigit * (uint64_t)(aDigitLow * scalarMultiplier);

                // Add product to current result pair (low and high word)
                uint64_t current = ((uint64_t)resultPtr[1] << 32) | resultPtr[0];
                current += product;
                resultPtr[0] = (uint32_t)(current & 0xFFFFFFFF);
                resultPtr[1] = (uint32_t)(current >> 32);
                // Move to next result position
                resultPtr += 2;
            }

            // After inner loop, propagate the carry from the current a digit to the next digit
            // Compute carry: bits 28-31 of low word and bits 0-3 of high word combine to form an 8-bit value
            uint32_t lowWord = aPtr[0];
            uint32_t highWord = aPtr[1];
            uint32_t carry = (lowWord >> 0x1C) | (highWord << 4); // Extract overflow bits
            // Add carry to the next digit (at aPtr+2)
            uint64_t next = ((uint64_t)aPtr[3] << 32) | aPtr[2];
            next += carry;
            aPtr[2] = (uint32_t)(next & 0xFFFFFFFF);
            aPtr[3] = (uint32_t)(next >> 32);
            // Additionally, add the high word's bits beyond the 28-bit part (bits 4-31) to the next digit's high part
            // Actually the original code does: aPtr[3] += (highWord >> 0x1C) + carry from the addition
            // But this is already included in the carry propagation because we added full carry.
            // However, the original code also adds (highWord >> 0x1C) separately; we must replicate exactly.
            // We'll adjust: after the above addition, we also need to add the top 4 bits of highWord to the high part of next? No, the original code:
            // *puVar8[3] = puVar8[3] + (puVar8[1] >> 0x1c) + (uint)CARRY4(uVar7, uVar4);
            // This adds the highWord>>28 (top 4 bits) and the carry from adding uVar4 to next's low word.
            // We'll handle this by a separate step.
            // Rework: first add the top 4 bits of highWord to aPtr[3] (the high part of next)
            aPtr[3] += (highWord >> 0x1C);
            // Then add the carry from (lowWord>>28) to next and propagate
            uint64_t next2 = ((uint64_t)aPtr[3] << 32) | aPtr[2];
            next2 += (lowWord >> 0x1C);
            aPtr[2] = (uint32_t)(next2 & 0xFFFFFFFF);
            aPtr[3] = (uint32_t)(next2 >> 32);
            // Also we must handle the carry from the addition of the top 4 bits? The code includes CARRY4 from adding that, but our addition already handles full 64-bit carry.

            // Move to next a digit (advance by 2 uint32_t)
            aPtr += 2;
        }

        // Now propagate carries for the remaining digits (from bCount to bCount*2+1)
        // These were not fully processed in the outer loop
        uint32_t* carryPtr = temp + bCount * 2; // start at digit bCount
        for (int idx = bCount; idx <= maxResultPairs; idx++) // loop over digits from bCount to 2*bCount inclusive
        {
            // Compute carry from current digit
            uint32_t low = carryPtr[0];
            uint32_t high = carryPtr[1];
            uint32_t carry = (low >> 0x1C) | (high << 4);
            // Add to next digit if it exists
            if (idx < maxResultPairs)
            {
                uint64_t next = ((uint64_t)carryPtr[3] << 32) | carryPtr[2];
                next += carry;
                carryPtr[2] = (uint32_t)(next & 0xFFFFFFFF);
                carryPtr[3] = (uint32_t)(next >> 32);
                // Also add the top 4 bits of high to next's high part (as before)
                carryPtr[3] += (high >> 0x1C);
            }
            carryPtr += 2;
        }

        // Copy result from temp back to this->digits, truncating to 28 bits per digit
        int resultLength = bCount + 1; // as per original code: *param_1 = iVar9+1 where iVar9=*param_2
        for (int i = 0; i < resultLength; i++)
        {
            this->digits[i] = temp[i * 2] & 0xFFFFFFF; // keep only low 28 bits
        }
        // Zero out remaining digits up to original aCount
        for (int i = resultLength; i < aCount; i++)
        {
            this->digits[i] = 0;
        }

        // Update digit count
        this->digitCount = resultLength;

        // Trim leading zeros
        while (this->digitCount > 0 && this->digits[this->digitCount - 1] == 0)
        {
            this->digitCount--;
        }
        if (this->digitCount == 0)
        {
            this->signOrFlags = 0; // offset +0x08
        }

        // Call normalization functions (hypothetical)
        if (normalizeSign() != -1) // FUN_00665c30
        {
            return normalizeDigits(this); // FUN_0066c8d0
        }
        return 0;
    }
    return 0;
}