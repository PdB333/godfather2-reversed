// FUNC_NAME: hashCombine
// Address: 0x0056d6b0
// Role: Combines three hash inputs by chaining two calls to FUN_0056cba0 (likely a hash update function).
// The function takes four parameters: input1, input2, input3, and a pointer to output.
// It first hashes input1 and input2 into a temporary buffer (28 bytes), then hashes that buffer with input3 into the final output.
void hashCombine(uint32_t input1, uint32_t input2, uint32_t input3, uint32_t* output)
{
    uint8_t tempBuffer[28]; // Intermediate hash result (size matches typical hash digest, e.g., SHA-224? or custom 28-byte hash)

    // First hash: combine input1 and input2 into tempBuffer
    FUN_0056cba0(input1, input2, tempBuffer);

    // Second hash: combine tempBuffer and input3 into final output
    FUN_0056cba0(tempBuffer, input3, output);
}