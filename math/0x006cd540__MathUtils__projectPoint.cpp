// FUNC_NAME: MathUtils::projectPoint
float MathUtils::projectPoint(float* outScreenPos, float* outScaleX, float* outScaleY, const float* inWorldPos)
{
    float fVar1;
    float fVar2;
    int cameraPtr;
    float fVar4;
    float local_20;
    float local_1c;
    float local_18;
    float local_14;

    // Get camera object (likely from a singleton or global)
    cameraPtr = getCameraObject(0); // FUN_004262f0

    // Copy input world position (x, y, z)
    local_20 = inWorldPos[0];
    local_1c = inWorldPos[1];
    local_18 = inWorldPos[2];

    // Global projection factor (e.g., viewport width or FOV scale)
    local_14 = g_projectionFactor; // _DAT_00d5780c

    // Transform world position by camera view/projection matrix
    transformVector(cameraPtr, &local_20, &local_20); // FUN_0056b420

    // Get some time/angle value (e.g., frame time or camera rotation)
    fVar4 = getTimeOrAngle(); // FUN_0040c390

    // Compute screen X coordinate
    *outScreenPos = local_20 / local_14;

    // Compute screen Y coordinate with additional scaling
    fVar1 = g_projectionFactor; // _DAT_00d5780c
    local_1c = local_1c / ((fVar1 - (fVar4 + fVar4)) * local_14);
    outScreenPos[1] = local_1c;

    // Compute output scale values
    fVar2 = g_screenScale; // _DAT_00d5c458
    *outScaleX = (local_20 / local_14 + fVar1) * fVar2;
    *outScaleY = (local_1c + fVar1) * fVar2;

    // Return depth value from camera object (+0x150)
    return *(float*)(cameraPtr + 0x150);
}