// FUNC_NAME: PlayerPhysicsComponent::integrateVelocityComponents
// Address: 0x00955910
// Role: Updates velocity components (X and Y) from heading angle and speed using Euler integration,
//       then optionally processes the velocity vector via a game handle check.

void __thiscall PlayerPhysicsComponent::integrateVelocityComponents(float dt)
{
    // +0x94: heading angle in radians (yaw)
    float heading = *(float *)(this + 0x94);
    // +0xC8: forward speed magnitude
    float speed = *(float *)(this + 200); // 0xC8

    // +0xD0: x-velocity component (or lateral)
    float *velocityX = (float *)(this + 0xD0);
    double dHeading = (double)heading;

    // integrate: velocityX += sin(heading) * speed * dt
    *velocityX = (float)(sin(dHeading) * (double)speed * (double)dt) + *velocityX;

    // +0xD8: y-velocity component (or forward/vertical)
    dHeading = (double)heading;
    float *velocityY = (float *)(this + 0xD8);
    *velocityY = (float)(cos(dHeading) * (double)speed * (double)dt) + *velocityY;

    // obtain game handle (e.g., SimManager, ControllerManager) – see FUN_00977420
    undefined4 handle = FUN_00977420();
    // check handle validity – see FUN_00849cf0
    int isValid = FUN_00849cf0(handle);
    if (isValid != 0) {
        // process velocity vector (clamp, wrap, or apply friction) – see FUN_00848fb0
        FUN_00848fb0(velocityX);
    }
    return;
}