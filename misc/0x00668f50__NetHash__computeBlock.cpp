// FUNC_NAME: NetHash::computeBlock
// Function address: 0x00668f50
// Purpose: Computes a 28-bit polynomial hash (CRC-like) over a block of uint32 data.
// The multiplication uses GF(2^28) reduction; each step multiplies data by a polynomial (param_2) and accumulates carry.
// Result stored in output structure with capacity checking and trailing zero trimming.

int NetHash::computeBlock(int* inputBlock, unsigned int multiplier, int* outputBlock) {
    // InputBlock layout:
    //   [0] - count (number of uints to hash)
    //   [1] - unknown (not used directly)
    //   [2] - some value (copied to output)
    //   [3] - pointer to data array
    // OutputBlock layout:
    //   [0] - current count (updated after hashing)
    //   [1] - capacity (max elements)
    //   [2] - some value (copied from input)
    //   [3] - pointer to result array

    int inputCount = inputBlock[0];
    int outputCapacity = outputBlock[1];
    int result;

    // Check if we can fit inputCount+1 elements into output (carry needs extra slot)
    // If not, try to resize via ensureCapacity()
    if ((inputCount + 1 <= outputCapacity) || (result = ensureCapacity(), result == 0)) {
        // Set output's value field from input
        outputBlock[2] = inputBlock[2];

        unsigned int* inputData = (unsigned int*)inputBlock[3];
        unsigned int* outputData = (unsigned int*)outputBlock[3];
        int index = 0;
        unsigned int carry = 0;

        // Process each input word with polynomial multiplication and carry
        while (index < inputCount) {
            // 64-bit multiply: inputData[index] * multiplier (both 32-bit), then add carry
            unsigned long long product = __allmul(inputData[index], 0, multiplier, 0);
            unsigned long long sum = product + (unsigned long long)carry;
            unsigned int lowPart = (unsigned int)(sum & 0xFFFFFFFF);
            // Carry is high 4 bits of low part? Actually: sum >> 32 gives high 32 bits,
            // but the code does: carry = (lowPart >> 28) | ((highPart) * 16)
            // This seems to be a GF(2^28) reduction: lowPart & 0xFFFFFFF is result,
            // and high part (including carry) is reduced by shifting.
            // Likely the modulus is 0x10000000 (2^28), so high 4 bits of low part + high*16 become new carry.
            unsigned int highPart = (unsigned int)(sum >> 32);
            carry = (lowPart >> 28) | (highPart * 16);
            outputData[index] = lowPart & 0xFFFFFFF;  // store modulo 2^28
            index++;
        }

        // Store final carry in next slot
        outputData[index] = carry;

        // Zero out remaining slots up to original output capacity (if any)
        int originalOutputCount = outputBlock[0];
        if (index < originalOutputCount) {
            for (int i = index; i < originalOutputCount; i++) {
                outputData[i] = 0;
            }
        }

        // Update output count: inputCount + 1 (for carry)
        outputBlock[0] = inputCount + 1;

        // Trim trailing zeros from the result (to reduce size)
        int newCount = outputBlock[0];
        while (newCount > 0 && outputData[newCount - 1] == 0) {
            newCount--;
        }
        outputBlock[0] = newCount;

        // If completely trimmed, also clear the copied value
        if (outputBlock[0] == 0) {
            outputBlock[2] = 0;
        }

        result = 0;  // success
    }
    return result;  // 0 on success, non-zero on failure (resize failed)
}