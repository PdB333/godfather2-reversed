// FUNC_NAME: CameraTargetInterpolator::interpolatePosition
void __thiscall CameraTargetInterpolator::interpolatePosition(
    float *outPos,          // output position
    const float *fromPos,   // source position
    const float *toPos,     // target position
    const SpringParams *params, // parameters with blend and clamp settings
    float dt                 // delta time / blend factor
) {
    float blendFactor;
    float diffX, diffY, diffZ;
    float maxDistance;

    // Check if override speed flag is set in component data (this+0x2d0 is some pointer, offset 0x8e3)
    if ((*(byte*)(*(int*)(this + 0x2d0) + 0x8e3) & 1) != 0) {
        // Use alternate speed from params offset 0x154
        blendFactor = *(float*)(params + 0x154);
    } else {
        // Lerp between two speed values: 0x80 is base, 0x60 is target
        float baseSpeed = *(float*)(params + 0x80);
        float targetSpeed = *(float*)(params + 0x60);
        blendFactor = (targetSpeed - baseSpeed) * dt + baseSpeed;
    }

    // Compute direction vector from 'to' towards 'from' (since from - to)
    diffX = (fromPos[0] - toPos[0]) * blendFactor;
    diffY = (fromPos[1] - toPos[1]) * blendFactor;
    diffZ = (fromPos[2] - toPos[2]) * blendFactor;

    maxDistance = *(float*)(params + 0x14); // radius at offset 0x14
    // Check if squared length of diff vector is under maxDistance^2
    if (diffX*diffX + diffY*diffY + diffZ*diffZ < maxDistance * maxDistance) {
        // Clamp direction to exactly maxDistance
        mathVecNormalize(&diffX);    // normalize vector, expects float* (first component)
        diffX *= maxDistance;
        diffY *= maxDistance;
        diffZ *= maxDistance;
    }

    // Output = 'to' position + clamped direction
    outPos[0] = toPos[0] + diffX;
    outPos[1] = toPos[1] + diffY;
    outPos[2] = toPos[2] + diffZ;
}