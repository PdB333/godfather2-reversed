// FUNC_NAME: Entity::updateMovement
void __thiscall Entity::updateMovement(float deltaTime)
{
    float angle = *(float *)(this + 0x94);        // +0x94: movement angle in radians
    float speed = *(float *)(this + 0xC8);         // +0xC8: movement speed (units/sec)
    float *positionX = (float *)(this + 0xD0);     // +0xD0: X position
    float *positionY = (float *)(this + 0xD8);     // +0xD8: Y position

    // Update position using angle and speed
    double sinAngle = (double)angle;
    FUN_00b99e20(); // likely sin(angle) – returns via FPU stack
    *positionX = (float)sinAngle * speed * deltaTime + *positionX;

    double cosAngle = (double)angle;
    FUN_00b99fcb(); // likely cos(angle) – returns via FPU stack
    *positionY = *positionY - (float)cosAngle * speed * deltaTime;

    // Check if boundary clamping is needed
    void *manager = FUN_00977420(); // singleton getter (e.g., GameManager)
    int isClampingEnabled = FUN_00849cf0(manager);
    if (isClampingEnabled != 0) {
        FUN_00848fb0(positionX); // clamp position to world bounds
    }
}