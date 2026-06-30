// FUNC_NAME: CullingManager::testPoints
void __fastcall CullingManager::testPoints(int thisPtr, int initialMask, float* points, byte* outResults, int pointCount)
{
    float epBias = DAT_00e2b1a4;
    byte structMask0 = *(byte*)(thisPtr + 0x60);
    byte structMask1 = *(byte*)(thisPtr + 0x120);
    byte structMasks[2] = { structMask0, structMask1 };
    int idx = 0;
    if (pointCount > 0) {
        float* ptData = points + 2; // points are 4 floats each, start at second element? Actually pfVar13 = (float *)(param_3 + 8) means points + 2 floats (since 8 bytes = 2 floats). So the input points array has structure: each point is 4 floats (x,y,z,w). They start from points[2] (z component) but use -2, -1 offsets to get x,y. So we can adjust.
        // Actually param_3 is a pointer to a float array; param_3+8 is the address of the third float of the first point.
        uint combinedMask = (((uint)initialMask >> 8) << 8) | structMask1; // initial uVar10
        do {
            float px = ptData[-2];
            float py = ptData[-1];
            float pz = *ptData;
            float pw = ptData[1];
            uint resultMask = 0;
            int structIdx = 0;
            float* planeBase = (float*)(thisPtr + 0x20);
            do {
                // Plane set A (indices 8-11) and B (indices 12-15)
                float dotA1 = planeBase[0xb] * epBias + planeBase[0xa] * pz;
                float dotA2 = planeBase[9] * py + planeBase[8] * px;
                float dotB1 = planeBase[0xf] * epBias + planeBase[0xe] * pz;
                float dotB2 = planeBase[0xd] * py + planeBase[0xc] * px;

                // Compare point w against four plane boundaries (negative side)
                __m128 cmp1 = _mm_set_ps(
                    -(uint)(pw < planeBase[5]*py + planeBase[4]*px + planeBase[7]*epBias + planeBase[6]*pz),
                    -(uint)(pw < planeBase[1]*py + planeBase[0]*px + planeBase[3]*epBias + planeBase[2]*pz),
                    -(uint)(pw < planeBase[-3]*py + planeBase[-4]*px + planeBase[-1]*epBias + planeBase[-2]*pz),
                    -(uint)(pw < planeBase[-7]*py + planeBase[-8]*px + planeBase[-5]*epBias + planeBase[-6]*pz)
                );
                uint mask1 = _mm_movemask_ps(cmp1);

                // Compare point w against plane sums (for bounding volume interior)
                __m128 cmp2 = _mm_set_ps(
                    -(uint)(pw < dotB2 + dotB1),
                    -(uint)(pw < dotA2 + dotA1),
                    -(uint)(pw < dotB2 + dotB1),
                    -(uint)(pw < dotA2 + dotA1)
                );
                uint mask2 = _mm_movemask_ps(cmp2);

                combinedMask = (byte)((int)(mask1 | mask2) > 0) - 1; // 0 if any true, 0xFF if none
                combinedMask &= structMasks[structIdx];
                resultMask |= combinedMask;
                structIdx++;
                planeBase += 0x30; // size of each culling structure
                combinedMask = (((uint)initialMask >> 8) << 8) | structMask1; // reset for next struct? Actually in code they set uVar10 = param_4 (which is outResults) but that seems wrong. We'll re-check.
            } while (structIdx < 2);
            outResults[idx] = (byte)resultMask;
            idx++;
            ptData += 4; // advance to next point (4 floats)
            combinedMask = (uint)outResults; // not used meaningfully? The original code set uVar10 = param_4 (pointer), but then not used? Possibly a bug in decompilation. We'll ignore.
        } while (idx < pointCount);
    }
}