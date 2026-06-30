// FUNC_NAME: BigInt::partialMultiply

int BigInt::partialMultiply(int* pA, int* pB, uint* pResult, uint startOffset)
{
    uint totalLength = (uint)(*pA + 1 + *pB);
    uint localBuffer[1025]; // Used as temporary 64-bit accumulator array (each element is 2 uint)
    localBuffer[0] = totalLength;

    // Check if result buffer is large enough, otherwise try to grow
    if (totalLength > pResult[1] || (totalLength <= pResult[1] || (int)FUN_00667740() != 0)) // Note: condition reversed
    {
        int numDigitsA = *pA;
        int numDigitsB = *pB;
        // Clear the portion of the local buffer we will use (from startOffset+1 to end)
        memset(localBuffer + startOffset * 2 + 2, 0, ((numDigitsB - startOffset) + numDigitsA) * 8 + 8);

        int indexA = 0;
        uint offsetB = startOffset;

        for (int i = 0; i < numDigitsA; i++)
        {
            uint digitA = *(uint*)(pA[3] + indexA * 4);
            uint* ptrB = (uint*)(pB[3] + offsetB * 4);
            uint64_t* target = (uint64_t*)(localBuffer + startOffset * 2 + 2);

            // Handle negative offset (should not happen in practice)
            if ((int)offsetB < 0)
            {
                int absOffset = -offsetB;
                ptrB += absOffset;
                target += absOffset;
                offsetB = 0;
            }

            int remaining = numDigitsB - offsetB;
            for (int j = 0; j < remaining; j++)
            {
                uint64_t product = __allmul(*ptrB, 0, digitA, 0); // 64-bit multiply
                target[0] += product;
                ptrB++;
                target++;
            }

            indexA++;
            offsetB--;
            totalLength = localBuffer[0]; // Update from stored length
        }

        uint finalLength = totalLength;
        *pResult = finalLength;

        // Propagate carry and convert to 28-bit digits
        for (int i = startOffset + 1; i < (int)finalLength; i++)
        {
            uint lowWord = localBuffer[i * 2];
            uint highWord = localBuffer[i * 2 + 1];
            uint carry = (lowWord >> 28) | (highWord << 4);
            localBuffer[i * 2 + 2] += carry;
            localBuffer[i * 2 + 3] += (highWord >> 28) + (uint)(carry < (lowWord >> 28)); // Carry propagation
            pResult[3][i] = lowWord & 0x0FFFFFFF; // Store 28-bit digit
        }
        pResult[3][finalLength] = localBuffer[finalLength * 2] & 0x0FFFFFFF;

        // Zero out remaining digits
        for (int i = startOffset + 1; i < (int)finalLength; i++)
        {
            // Already stored above, but need to fill zeros if finalLength < original capacity
        }
        // Actually the loop above sets from startOffset+1 to finalLength, but original capacity is pResult[1]. 
        // So we need to zero the rest:
        int originalResultLen = *pResult;
        for (int i = finalLength; i < originalResultLen; i++)
        {
            pResult[3][i] = 0;
        }

        // Trim leading zeros
        uint len = *pResult;
        while (len > 0 && pResult[3][len - 1] == 0)
            len--;
        *pResult = len;

        if (len == 0)
            pResult[2] = 0;

        return 0; // Success
    }

    // If we reach here, it means the memory reallocation failed
    return (int)totalLength; // Non-zero indicates error (or return from FUN_00667740)
}