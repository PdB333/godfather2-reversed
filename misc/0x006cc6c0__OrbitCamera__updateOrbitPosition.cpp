// FUNC_NAME: OrbitCamera::updateOrbitPosition
void OrbitCamera::updateOrbitPosition(const float* focusPos, const float* cameraPos, float spinAngle, float* outPos) {
    // Compute horizontal differences (ignoring Y axis)
    float dx = cameraPos[0] - focusPos[0];  // +0x00
    float dz = cameraPos[2] - focusPos[2];  // +0x08 (third component)

    // If horizontal distance is too small, return default forward direction
    const float kMinDistance = *(float*)0x00d5f168;  // ~0.1f
    if (sqrtf(dz * dz + dx * dx) < kMinDistance) {
        const float kDefaultForwardX = *(float*)0x00d5780c;  // 1.0f
        outPos[0] = kDefaultForwardX;
        outPos[1] = 0.0f;
        outPos[2] = 0.0f;
        return;
    }

    // Normalize horizontal direction vector (dx, dz)
    // FUN_0056afa0 is likely a 2D vector normalize function
    Math::normalize2D(&dx, &dz);  // modifies dx and dz in-place

    // Compute rotation from horizontal direction and spin angle
    // local_20 is a 28-byte buffer, likely a quaternion or 3x3 rotation matrix
    char rotationMatrix[28];
    Math::makeRotationFromDirectionAndAngle(dx, 0.0f, dz, spinAngle, rotationMatrix);

    // Target offset vector: (dz, 0, kOrbitRadius - dx)
    const float kOrbitRadius = *(float*)0x00e44564;  // fixed distance from focus
    float targetOffset[3] = { dz, 0.0f, kOrbitRadius - dx };

    // Apply rotation to offset and store result
    // FUN_0056ce80 likely multiplies a vector by a rotation matrix
    Math::rotateVector(rotationMatrix, targetOffset, outPos);
}