// FUNC_NAME: ChaseCamera::updateCameraPosition
void __thiscall ChaseCamera::updateCameraPosition(Vector3* outPos, CameraTarget* target, float deltaTime) {
    // Get the current camera transform position from the engine
    CameraData* camData = getEngineCameraData(); // FUN_00471610, returns pointer to camera data struct
    outPos->x = *(float*)((int)camData + 0x30);
    outPos->y = *(float*)((int)camData + 0x34);
    outPos->z = *(float*)((int)camData + 0x38);

    // Check if a certain mode flag is set (e.g., "fixed y" or "chase active")
    if ((*(byte*)(*(int*)((int)this + 0x2d0) + 0x8e3) & 1) != 0) {
        // Directly add an offset to the Y component from target
        outPos->y += *(float*)((int)target + 0x150); // +0x150: fixedYOffset?
    } else {
        // Interpolated Y offset: currentYOffset + (desiredYOffset - currentYOffset) * dt
        float desiredY = *(float*)((int)target + 0x5c);   // +0x5c: desiredYOffset
        float currentY = *(float*)((int)target + 0x7c);   // +0x7c: currentYOffset
        outPos->y += (desiredY - currentY) * deltaTime + currentY;
    }
}