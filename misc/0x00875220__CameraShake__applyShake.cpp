// FUNC_NAME: CameraShake::applyShake
void CameraShake::applyShake(float param2) {
    // Get global camera manager or similar singleton
    int* globalPtr = getGlobalManager(); // FUN_00471610, returns pointer to some global

    // Read current camera position (or target) from global at offsets +0x30 (x,y) and +0x38 (z)
    // local_18 is a 64-bit value representing two floats (x and y)
    // local_10 is the z component
    float currentX = *(float*)(globalPtr + 0x30);       // +0x30: x
    float currentY = *(float*)(globalPtr + 0x34);       // +0x34: y (second half of undefined8)
    float currentZ = *(float*)(globalPtr + 0x38);       // +0x38: z

    // Generate a random offset vector (local_c, local_8, local_4)
    float offsetX, offsetY, offsetZ;
    getRandomDirection(&offsetX, &offsetY, &offsetZ);   // FUN_008750c0

    // Read shake intensity from this object: this->someSubObject->intensity
    // this + 0x360 is a pointer to a sub-object, +0x104 is the intensity float
    float shakeIntensity = *(float*)(*(int*)(this + 0x360) + 0x104); // +0x360: pointer, +0x104: float

    // Apply scaled random offset to current position
    float newX = currentX + offsetX * shakeIntensity;
    float newY = currentY + offsetY * shakeIntensity;
    float newZ = currentZ + offsetZ * shakeIntensity;

    // Call function to actually set the camera offset (or shake effect)
    // Passes the new position, the random offset, param2, and a constant string/ID
    applyCameraShake(&newX, &offsetX, param2, &DAT_00d76320); // FUN_004a0cd0
}