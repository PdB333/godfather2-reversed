// FUNC_NAME: updateAndNotifyPositionChange
void __fastcall updateAndNotifyPositionChange(int unused_param, float* newPosition)
{
    float x = newPosition[0];
    float y = newPosition[1];
    float z = newPosition[2];
    float w = newPosition[3]; // Possibly angle or unused w component

    // Compare each component against the previously cached position
    // Store results as all-ones (true) or zero (false) for SSE movmskps extraction
    __m128 cmpResult;
    cmpResult.m128_u32[0] = (x == gCachedPosX) ? 0xFFFFFFFF : 0;
    cmpResult.m128_u32[1] = (y == gCachedPosY) ? 0xFFFFFFFF : 0;
    cmpResult.m128_u32[2] = (z == gCachedPosZ) ? 0xFFFFFFFF : 0;
    cmpResult.m128_u32[3] = (w == gCachedPosW) ? 0xFFFFFFFF : 0;

    // Extract sign bits: bit set if component matches (true = -1 -> sign bit = 1)
    int mask = _mm_movemask_ps(cmpResult);

    // Update cache with new position
    gCachedPosX = x;
    gCachedPosY = y;
    gCachedPosZ = z;
    gCachedPosW = w;

    // If any component changed (mask != 0xF) and a global manager is active
    if (mask != 0xF && gManagerObject != nullptr && *(int*)(gManagerObject + 0x70) != 0)
    {
        // Notify position change to audio/streaming system
        // gManagerObject + 0x14: some identifier/handle
        // gManagerObject + 0x70: target object pointer
        notifyPositionChanged(*(int*)(gManagerObject + 0x14), *(int*)(gManagerObject + 0x70), newPosition);
    }
}