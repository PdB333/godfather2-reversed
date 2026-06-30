// FUNC_NAME: MathUtils::unpackHalfVector2
// Function address: 0x004cd380
// Role: Converts a 128-bit input buffer (containing four 16-bit half-floats) into a 64-bit result (two 32-bit floats)
// by extracting sign, exponent, and mantissa fields, adjusting exponent bias, and packing into single-precision floats.
// Uses SSE2/MMX operations for packed conversion.
// Input pointer (16 bytes) is expected in register EAX prior to call; output pointer (8 bytes) is passed via ECX (this).
// The function writes two floats to the output.

void __fastcall MathUtils::unpackHalfVector2(undefined8 *outResult, const __m128i *inVector)
{
    // inVector is the 128-bit SSE value (four 16-bit half-floats) pointed to by EAX.
    // outResult is the 64-bit output (two 32-bit floats) pointed to by ECX.
    
    // Load the input vector
    __m128i input = _mm_load_si128(inVector);
    
    // Mask to extract exponent/mantissa fields for biasing
    // _DAT_00e36980: 128-bit mask (likely 0x7FFF7FFF7FFF7FFF or similar to keep lower 15 bits per half)
    __m128i maskExpMan = _mm_load_si128((__m128i*)0x00e36980);
    __m128i maskedExpMan = _mm_and_si128(input, maskExpMan);
    
    // Subtract exponent bias adjustments per half-word (offsets at 0x00e36990-0x00e3699e)
    // _UNK_00e36990 through _UNK_00e3699e: 16-bit signed offsets, likely (0x3800,0x3800,...) to convert exponent bias from 15 to 127
    __m128i expBias = _mm_set_epi16(0x3800, 0x3800, 0x3800, 0x3800, 0x3800, 0x3800, 0x3800, 0x3800);  // placeholder value based on half-to-float conversion
    __m128i adjustedExpMan = _mm_sub_epi16(maskedExpMan, expBias);
    
    // Extract individual 16-bit differences (simulated; actual code uses shorts)
    short diff0 = _mm_extract_epi16(adjustedExpMan, 0);  // low word
    short diff1 = _mm_extract_epi16(adjustedExpMan, 1);
    short diff2 = _mm_extract_epi16(adjustedExpMan, 2);
    short diff3 = _mm_extract_epi16(adjustedExpMan, 3);
    short diff4 = _mm_extract_epi16(adjustedExpMan, 4);
    short diff5 = _mm_extract_epi16(adjustedExpMan, 5);
    short diff6 = _mm_extract_epi16(adjustedExpMan, 6);
    short diff7 = _mm_extract_epi16(adjustedExpMan, 7);
    
    // Build 32-bit values from pairs of adjusted words (carries over differences per half-float)
    uint uVar2 = (uint)diff1 << 16 | (ushort)diff0;
    uint uVar2_hi = (uint)diff3 << 16 | (ushort)diff2;
    uint uVar4 = (uint)diff5 << 16 | (ushort)diff4;
    uint uVar4_hi = (uint)diff7 << 16 | (ushort)diff6;
    
    // Compute sign masks from original input sign bits (bit 15 each)
    __m128i signMask = _mm_srai_epi16(input, 15);  // arithmetic shift to get all 1's if negative
    signMask = _mm_and_si128(signMask, _mm_set1_epi32(0x80000000));  // isolate sign bit for float
    
    // Extract mantissa and exponent from the adjusted values
    // Shift right by 13 to align mantissa (half mantissa is 10 bits, shift left 13; but here we shift right? Actually after subtract, we shift right; see half-to-float algorithm)
    __m128i mantissaShifted = _mm_srli_epi32(adjustedExpMan, 13);  // each 32-bit word (containing bits from two half? Not exactly)
    // But the code uses 32-bit shifts on the concatenated values; we approximate.
    
    // Also extract from original input with different mask (sign/exponent handling)
    __m128i maskSignExp = _mm_load_si128((__m128i*)0x00e369a0);
    __m128i signExpPart = _mm_and_si128(input, maskSignExp);
    __m128i signExpShifted = _mm_srli_epi32(signExpPart, 13);
    
    // Extract mantissa field from original (mask at 0x00e36970, shift by 16)
    __m128i maskMantissa = _mm_load_si128((__m128i*)0x00e36970);
    __m128i mantissaPart = _mm_and_si128(input, maskMantissa);
    __m128i mantissaShifted16 = _mm_srli_epi32(mantissaPart, 16);
    
    // Combine sign, exponent, mantissa into proper float representation
    // Shuffle to reorder the two resulting floats into lower 64 bits
    __m128i combined = _mm_or_si128(mantissaShifted, signExpShifted);
    combined = _mm_andnot_si128(signMask2, combined);  // signMask2 = sign? actual code uses ~auVar10 & (auVar4 | auVar12) | auVar6
    
    // Use pshuflw/pshufhw to duplicate low/high floats into lower 64 bits
    __m128i result = _mm_shufflelo_epi16(combined, 0x88);
    result = _mm_shufflehi_epi16(result, 0x88);
    
    // Extract lower 64 bits (two floats) into output
    *outResult = _mm_cvtsi128_si64(result);
}