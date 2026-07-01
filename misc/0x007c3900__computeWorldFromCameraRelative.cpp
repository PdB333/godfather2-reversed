// FUNC_NAME: computeWorldFromCameraRelative
void computeWorldFromCameraRelative(float* outWorldPos, float* outCameraSpacePos) {
    float* tmpTransform = (float*)getTransformBuffer();     // temporary matrix?
    float* cameraData = (float*)getTransformBuffer();        // camera struct (+0x30 = position)
    float* rotationData = (float*)getTransformBuffer();      // rotation struct (+0x20 = orientation)
    float* transformedPoint = (float*)getTransformBuffer();  // output of matrix multiply

    char invertFlag = transformPointWithMatrix(tmpTransform + 0x30, cameraData + 0x30, transformedPoint, g_transformFlag);

    float clipDist = g_clipDistance;
    float scale1 = g_scaleFactor1;
    float scale2 = g_scaleFactor2;

    if (invertFlag == 0) {
        // Copy transformed point directly to camera-relative output
        *(undefined8*)outCameraSpacePos = *(undefined8*)transformedPoint; // copy first two floats (x,y)
        outCameraSpacePos[2] = transformedPoint[2];

        // Compute world position: cameraPos + scale * (clipDist - cameraRelative)
        outWorldPos[0] = scale1 * (clipDist - outCameraSpacePos[0]) + *(cameraData + 0x30);
        outWorldPos[1] = scale1 * (clipDist - outCameraSpacePos[1]) + *(cameraData + 0x34);
        outWorldPos[2] = scale1 * (clipDist - outCameraSpacePos[2]) + *(cameraData + 0x38);
    } else {
        // Invert sign: cameraRelative = clipDist - transformedPoint
        outCameraSpacePos[0] = clipDist - transformedPoint[0];
        outCameraSpacePos[1] = clipDist - transformedPoint[1];
        outCameraSpacePos[2] = clipDist - transformedPoint[2];

        // Compute world position directly from transformedPoint
        outWorldPos[0] = scale1 * transformedPoint[0] + *(cameraData + 0x30);
        outWorldPos[1] = scale1 * transformedPoint[1] + *(cameraData + 0x34);
        outWorldPos[2] = scale1 * transformedPoint[2] + *(cameraData + 0x38);
    }

    // Apply rotation adjustment (e.g., from character or camera rotation)
    outWorldPos[0] += scale2 * *(rotationData + 0x20);
    outWorldPos[1] += scale2 * *(rotationData + 0x24);
    outWorldPos[2] += scale2 * *(rotationData + 0x28);
}