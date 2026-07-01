// FUNC_NAME: computeWorldOffsetPosition
// Address: 0x007c6f70
// Computes a world position from a relative offset, used for camera/object placement.
// param_1: output position (float[3])
// param_2: entity pointer (or -0x2770 sentinel for player object)

extern float g_referenceX;          // DAT_00e44564
extern float g_defaultScale;        // DAT_00d5ccf8
extern float g_alternateScale;      // _DAT_00d5780c
extern float g_yOffset;             // _DAT_00d577a0
extern float g_correctionFactor;    // DAT_00d6e92c

void* getSomeGlobalObject();        // FUN_00471610 - returns pointer to a transform/global state
void someUpdateFunction();          // FUN_00800ad0 - possibly a debug or update call

void computeWorldOffsetPosition(float* outPosition, int entity)
{
    float* baseVector;
    float zComponent, xDiff, scaleFactor;
    bool useAlternateScale;

    if (entity == -0x2770) {
        // Use player object's base vector at offset +0x20
        void* globalObj = getSomeGlobalObject();
        baseVector = (float*)((int)globalObj + 0x20);
    } else {
        // Use entity's base vector at offset +0x277c
        baseVector = (float*)(entity + 0x277c);
    }

    zComponent = baseVector[2];               // Z component of base vector
    xDiff = g_referenceX - baseVector[0];     // X difference from reference

    someUpdateFunction();

    // Check bit 30 of entity's flag at offset +0x8e0
    useAlternateScale = ((*(int*)(entity + 0x8e0) >> 30) & 1) != 0;
    if (useAlternateScale) {
        scaleFactor = g_alternateScale;
    } else {
        scaleFactor = g_defaultScale;
    }

    void* globalObj = getSomeGlobalObject();
    float* baseOffset = (float*)((int)globalObj + 0x30); // Base offset (x, y, z)

    outPosition[0] = zComponent * scaleFactor + baseOffset[0];
    outPosition[1] = scaleFactor * g_yOffset + baseOffset[1];
    outPosition[2] = xDiff * scaleFactor + baseOffset[2];

    if (useAlternateScale) {
        // Apply correction when using alternate scale
        outPosition[0] -= baseVector[0] * g_correctionFactor;
        outPosition[2] -= baseVector[2] * g_correctionFactor;
    }
}