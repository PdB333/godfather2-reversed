// FUNC_NAME: GameUtils::isPointWithinTargetRange
bool __fastcall isPointWithinTargetRange(float* point, void* object, float baseRange)
{
    // Get a global pointer from thread-local storage (FS segment offset 0x2c)
    int globalBase = *(int*)(*(int*)(__readfsdword(0x2c) + 8));

    // object + 0x10: byte offset into an array of positions (presumably vec3)
    int posIndex = *(int*)((char*)object + 0x10);

    // object + 0x24 -> pointer to something with a float at +0x0c (range modifier)
    float rangeMod = *(float*)(*(int*)((char*)object + 0x24) + 0x0c);
    float effectiveRange = rangeMod + baseRange;

    // Position array starts at globalBase + 0x80
    float* targetPos = (float*)(globalBase + 0x80 + posIndex);
    float dx = point[0] - targetPos[0];
    float dy = point[1] - targetPos[1];
    float dz = point[2] - targetPos[2];
    float distSq = dx*dx + dy*dy + dz*dz;

    return distSq < (effectiveRange * effectiveRange);
}