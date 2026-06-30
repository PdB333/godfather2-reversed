// FUNC_NAME: CameraManager::setOrbitAngles
void CameraManager::setOrbitAngles(float pitch, float yaw)
{
    // Store the angles into global tracking variables
    gCameraOrbitPitch = pitch;   // _DAT_01219a10
    gCameraOrbitYaw = yaw;       // _DAT_01219a14

    // Check if the camera system is in the correct state
    // DAT_012058e8 is a pointer to the current camera object
    // DAT_01219940 is the expected object (likely a singleton)
    if ((gCurrentCameraPtr == &gExpectedCamera) && 
        (gCameraTargetObject == gCameraTargetID))   // DAT_01219954 == DAT_01219a48
    {
        int targetX = 0;   // local_18
        int targetY = 0;   // local_14
        // If there is a valid target handle
        if (gCameraTargetHandle != 0)   // DAT_01219a18
        {
            // Compute the target position relative to the camera
            // This function reads from the target entity and writes an 8-byte world position
            FUN_0060add0(gCameraTargetObject, gCameraTargetHandle, (undefined (*) [8])&targetX);
        }
    }
}