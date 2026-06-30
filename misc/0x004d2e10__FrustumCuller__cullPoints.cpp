// FUNC_NAME: FrustumCuller::cullPoints
void __thiscall FrustumCuller::cullPoints(uint initMask, float* points, uint8* outMasks, int count)
{
    float globalFloat = DAT_00e2b1a4; // global scaling factor or clip plane constant
    byte maskPresets[4];
    maskPresets[0] = *(byte*)(this + 0x60);   // preset bitmask for frustum 0
    maskPresets[1] = *(byte*)(this + 0x120);  // preset bitmask for frustum 1
    int processed = 0;

    if (0 < count) {
        float* pointData = points + 2; // skip first two floats? Actually offset +8 bytes: two floats before the four we use
        uint combinedMask = initMask >> 8;  // shift out lower 8 bits, combine with maskPresets[1]
        // Actually the original: uVar10 = CONCAT31((int3)((uint)param_2 >> 8),*(undefined1 *)(in_EAX + 0x120));
        // We'll reconstruct as: uint combinedMask = (initMask >> 8) | ((uint)maskPresets[1] << 24);
        // But simpler: approximate
        uint combinedMask = (initMask >> 8) | (maskPresets[1] << 24);

        do {
            // Extract 4 floats from each point (position + some extra component)
            float x = pointData[-2];
            float y = pointData[-1];
            float z = pointData[0];
            float w = pointData[1];

            uint resultMask = 0;
            int frustumIndex = 0;
            float* frustumData = (float*)(this + 0x20);  // array of 2 frustum structures (each 48 bytes = 12 floats)

            do {
                // Frustum plane equations are stored in the structure at [frustumData -8] through [frustumData +7]?
                // Four planes per frustum? Actually we have four comparisons per frustum
                float planeDot1 = frustumData[0xb] * globalFloat + frustumData[10] * z;
                float planeDot2 = frustumData[9] * y + frustumData[8] * x;
                float planeDot3 = frustumData[0xf] * globalFloat + frustumData[0xe] * z;
                float planeDot4 = frustumData[0xd] * y + frustumData[0xc] * x;

                // Perform 4 plane tests (w less than dot products)
                // These comparisons generate masks via movmskps
                // Using SSE intrinsics for clarity
                __m128 planeValues1 = _mm_set_ps(
                    frustumData[1] * y + frustumData[0] * x + frustumData[3] * globalFloat + frustumData[2] * z,
                    frustumData[5] * y + frustumData[4] * x + frustumData[7] * globalFloat + frustumData[6] * z,
                    frustumData[-3] * y + frustumData[-4] * x + frustumData[-1] * globalFloat + frustumData[-2] * z,
                    frustumData[-7] * y + frustumData[-8] * x + frustumData[-5] * globalFloat + frustumData[-6] * z
                );
                __m128 planeValues2 = _mm_set_ps(
                    planeDot2 + planeDot1,
                    planeDot4 + planeDot3,
                    planeDot4 + planeDot3,
                    planeDot2 + planeDot1
                );
                // Compare with w
                __m128 wVec = _mm_set1_ps(w);
                __m128 cmp1 = _mm_cmplt_ps(wVec, planeValues1);
                __m128 cmp2 = _mm_cmplt_ps(wVec, planeValues2);
                int mask1 = _mm_movemask_ps(cmp1);
                int mask2 = _mm_movemask_ps(cmp2);

                // Combine masks with the preset bitmask for this frustum
                combinedMask = (0 < (int)(mask2 | mask1)) ? 0 : maskPresets[frustumIndex];
                resultMask |= (uint)combinedMask;

                frustumIndex++;
                frustumData += 12; // 12 floats per frustum structure (0x30 bytes)
                combinedMask = (uint)outMasks; // Reset? Actually original resets to param_4 (outMasks pointer) which is weird
            } while (frustumIndex < 2);

            *(outMasks + processed) = (uint8)resultMask;
            processed++;
            pointData += 4; // advance to next point (4 floats)
        } while (processed < count);
    }
}