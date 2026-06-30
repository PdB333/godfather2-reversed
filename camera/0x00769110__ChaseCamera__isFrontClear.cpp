// FUNC_NAME: ChaseCamera::isFrontClear
bool ChaseCamera::isFrontClear()
{
    // Check if camera is currently active/controlled; if not, return clear
    if (!isCameraControlled()) {
        return true;
    }

    // Retrieve the active camera object (global singleton)
    Camera* camera = getActiveCamera();

    // Read the camera's forward direction vector from offset 0 (struct offset +0x0, +0x4, +0x8)
    Vector3 forward = camera->forward;  // Assume Vector3 starting at offset 0

    // Scale the forward vector by a global tuning constant (DAT_00d65bc4)
    float scale = kCameraForwardCheckScale;
    forward.x *= scale;
    forward.y *= scale;
    forward.z *= scale;

    // Read camera position from offset +0x30
    Vector3 camPos = camera->position;  // offset +0x30

    // Compute the target point: camera position + scaled forward
    Vector3 targetPos;
    targetPos.x = camPos.x + forward.x;
    targetPos.y = camPos.y + forward.y;
    targetPos.z = camPos.z + forward.z;

    // Execute a raycast from camera position to target point,
    // ignoring actors and self (flags = 0)
    bool hit = performRaycast(camPos, targetPos, 0, 0, 0);

    // Return true if no collision (raycast returns false)
    return !hit;
}