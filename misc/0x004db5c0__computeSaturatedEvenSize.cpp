// FUNC_NAME: computeSaturatedEvenSize
void computeSaturatedEvenSize(void)
{
    // Input: pointer to a 32-bit count in EAX (in_EAX)
    uint32_t* countPtr = (uint32_t*)in_EAX;
    uint32_t count = *countPtr;

    // Compute: (count >> 1) + 1, then multiply by 2
    // Equivalent to: count + 2 - (count & 1)
    // This rounds up to the next even number and adds 2 if count is even, or 1 if odd.
    uint64_t temp64 = ((uint64_t)(count >> 1) + 1) * 2ULL;

    // Clamp to UINT32_MAX if overflow (> 0xFFFFFFFF)
    // If high 32 bits of temp64 are non-zero, set result to 0xFFFFFFFF; else take low 32 bits.
    uint32_t result = ((int32_t)(temp64 >> 32) != 0) ? 0xFFFFFFFF : (uint32_t)temp64;

    // Pass the computed saturated size to the actual processing function
    sub_9c8e50(result);  // FUN_009c8e50 - likely a memory allocation or size adjustment routine
}