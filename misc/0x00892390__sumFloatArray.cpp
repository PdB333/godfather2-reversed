// FUNC_NAME: sumFloatArray
// Function address: 0x00892390
// Role: Sum all floats in an array stored in a structure.
// The structure has a count at offset +0x2c and an array of floats starting at offset +0x08.
// The function returns the sum as a long double (80-bit extended precision).

#include <cstdint>

struct FloatArray
{
    // +0x00: unknown (vtable pointer or other)
    // +0x08: float data[];  // inline array
    // +0x2c: uint32_t count;
};

long double __fastcall sumFloatArray(FloatArray* pArray)
{
    uint32_t count = *(uint32_t*)(reinterpret_cast<uint8_t*>(pArray) + 0x2c);
    float* base = reinterpret_cast<float*>(reinterpret_cast<uint8_t*>(pArray) + 8);
    float sum = 0.0f;
    uint32_t processed = 0;

    // Unrolled loop: process 4 floats per iteration
    if (count > 3)
    {
        int32_t iter = ((count - 4) >> 2) + 1;
        float* ptr = base;
        do
        {
            // Add 4 consecutive floats with pointer offset of -2 relative to base+2
            sum += ptr[-2] + ptr[-1] + ptr[0] + ptr[1];
            ptr += 4;
            --iter;
        } while (iter != 0);
        processed = ((count - 4) >> 2) * 4 + 4;
    }

    // Process remaining elements
    for (uint32_t i = processed; i < count; ++i)
    {
        sum += base[i];
    }

    return static_cast<long double>(sum);
}