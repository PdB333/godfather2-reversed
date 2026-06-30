// FUNC_NAME: AnimationSystem::applyWeightBlend

void __fastcall AnimationSystem::applyWeightBlend(ulonglong *packedWeights, int count)
{
    // Global constants used for unpacking and transformation
    // _DAT_00e31ab0: mask for extracting lower 16 bits? (auVar2)
    // _DAT_00e31ac0: mask for high bits? (auVar3)
    // _UNK_00e31ad0: base offset for X component? (iVar4)
    // _UNK_00e31ad4: base offset for Y component? (iVar5)
    // _UNK_00e31ad8: base offset for Z component? (iVar6)
    // _UNK_00e31adc: base offset for W component? (iVar7)

    // unaff_ESI holds the base address of the output vertex buffer (member variable?)
    float *vertexBufferBase = (float *)unaff_ESI;

    // Load the constant masks (128-bit values)
    __m128i maskHigh = _mm_load_si128((__m128i*)&_DAT_00e31ac0);
    __m128i maskLow  = _mm_load_si128((__m128i*)&_DAT_00e31ab0);

    // Base offsets for the identity transformation (used when no weight)
    int baseX = _UNK_00e31ad0;
    int baseY = _UNK_00e31ad4;
    int baseZ = _UNK_00e31ad8;
    int baseW = _UNK_00e31adc;

    // Blend factor from xmm0 (passed implicitly by caller)
    float blendFactor = in_XMM0_Da;

    if (count != 0) {
        do {
            ulonglong packed = *packedWeights;

            // Extract 64-bit packed weight into 4 16-bit components
            // Using shifts and masks to reconstruct a 128-bit value
            ulonglong lower = packed;
            ulonglong upper = packed >> 16;
            __m128i unpacked = _mm_set_epi16(
                (short)(packed >> 48),
                (short)(packed >> 32),
                (short)(packed >> 16),
                (short)(packed),
                (short)(packed >> 48),
                (short)(packed >> 32),
                (short)(packed >> 16),
                (short)(packed)
            );

            // Apply masks to get the real components
            __m128i masked = _mm_and_si128(maskHigh, unpacked);

            // Create a scaled contribution vector from base offsets and packed values
            __m128i contrib;
            contrib = _mm_set_epi32(
                baseW + ((short)(packed >> 48) * 0x2000),
                baseZ + ((short)(packed >> 32) * 0x2000),
                baseY + ((short)(packed >> 16) * 0x2000),
                baseX + ((short)(packed) * 0x2000)
            );

            // Combine with the mask to get final deltas
            __m128i delta = _mm_or_si128(maskLow, contrib);

            // Extract the vertex index from the packed word (offset +6 in the 8-byte entry)
            int vertexIndex = *(unsigned short*)((int)packedWeights + 6);
            float *vertex = vertexBufferBase + vertexIndex * 4; // each vertex is 4 floats?

            // Apply blend: vertex += blendFactor * delta (as float)
            __m128 deltaFloat = _mm_cvtepi32_ps(delta); // convert to float
            __m128 blendVec = _mm_mul_ps(_mm_set1_ps(blendFactor), deltaFloat);
            __m128 current = _mm_loadu_ps(vertex);
            __m128 result = _mm_add_ps(current, blendVec);
            // Preserve the W component from original (based on scale by 0.0)
            // Actually the original code does: pfVar8[3] = auVar13._12_4_ * 0.0 + pfVar8[3]; so W stays unchanged.
            // So we only update X,Y,Z
            result = _mm_blend_ps(current, result, 0x7); // keep W from current
            _mm_storeu_ps(vertex, result);

            packedWeights++;
            count--;
        } while (count != 0);
    }
}