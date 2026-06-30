// FUNC_NAME: ChaseCamera::GetCameraPositionAndTarget

struct Vector3 {
    float x, y, z;
};

// Forward declaration: returns pointer to player instance with position at +0x30
int __cdecl GetPlayerInstance(void);

// Function at address 0x0071add0
// Retrieves camera position and either a fixed target or a direction toward the player
// offsets: this+0x10 -> pointer to camera data (position at +0x44, fixed target at +0x38)
//          this+0xc  -> pointer to camera mode container (mode at +0x24CC)
void __thiscall ChaseCamera::GetCameraPositionAndTarget(Vector3* outPosition, Vector3* outTarget)
{
    int cameraData = *(int*)(this + 0x10);

    // Camera world position
    outPosition->x = *(float*)(cameraData + 0x44);
    outPosition->y = *(float*)(cameraData + 0x48);
    outPosition->z = *(float*)(cameraData + 0x4c);

    int cameraMode = *(int*)(*(int*)(this + 0xc) + 0x24CC);
    // Modes 0 and 0x48 (72) use a fixed look-at target from camera data
    // Other modes compute a direction from camera to the player
    if ((cameraMode != 0) && (cameraMode != 0x48)) {
        int player = GetPlayerInstance(); // Returns pointer to player object
        outTarget->x = *(float*)(player + 0x30) - outPosition->x;
        outTarget->y = *(float*)(player + 0x34) - outPosition->y;
        outTarget->z = *(float*)(player + 0x38) - outPosition->z;
    } else {
        // Fixed target from camera data
        outTarget->x = *(float*)(cameraData + 0x38);
        outTarget->y = *(float*)(cameraData + 0x3c);
        outTarget->z = *(float*)(cameraData + 0x40);
    }
}