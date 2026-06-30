// FUNC_NAME: FindClosestVectorIndex
uint32_t FindClosestVectorIndex(const Vector3* vectors, uint32_t count, float* outDistances)
{
    uint32_t bestIndex = 0;
    if (vectors == nullptr || count == 0)
        return bestIndex;

    float bestDist = DAT_00e2e50c; // likely FLT_MAX (global constant)
    uint32_t uVar4 = 0;
    uint8_t bVar5 = 0;

    do {
        // vector stride 0xC (x, y, z floats)
        float x = *(float*)(vectors + uVar4 * 0xC + 0x0);
        float y = *(float*)(vectors + uVar4 * 0xC + 0x4);
        float z = *(float*)(vectors + uVar4 * 0xC + 0x8);
        float dist = sqrt(x * x + y * y + z * z);
        outDistances[uVar4] = dist;
        if (dist < bestDist)
        {
            bestIndex = uVar4;
            bestDist = dist;
        }
        bVar5 = bVar5 + 1;
        uVar4 = (uint32_t)bVar5;
    } while (uVar4 < count);

    return bestIndex;
}