// FUNC_NAME: SpatialQuery::isPointInSphere
typedef signed int BOOL;
typedef float Vector3[3];

// Global pointer to spatial data, accessed via TLS offset 0x2c (commonly GameManager)
#define GET_GLOBAL_SPATIAL_DATA() (*(int *)(*(int *)(*(int *)(*(int *)(__readfsdword(0x2c)) + 0)) + 8))

BOOL __fastcall isPointInSphere(float *point, int spatialHandle, float radius)
{
    int globalData = GET_GLOBAL_SPATIAL_DATA();
    int positionIndex = *(int *)(spatialHandle + 0x10); // offset of index into array
    float rangeAdjustment = *(float *)(*(int *)(spatialHandle + 0x24) + 0xC); // get range modifier from another object
    float totalRadius = rangeAdjustment + radius;

    // Array of position vectors starts at offset 0x80 in globalData, each vector is 12 bytes (3 floats)
    float dx = point[0] - *(float *)(globalData + 0x80 + positionIndex);                // +0x80: x
    float dy = point[1] - *(float *)(globalData + 0x84 + positionIndex);                // +0x84: y
    float dz = point[2] - *(float *)(globalData + 0x88 + positionIndex);                // +0x88: z

    float distSq = dx*dx + dy*dy + dz*dz;
    if (distSq < totalRadius * totalRadius) {
        return 1;
    }
    return 0;
}