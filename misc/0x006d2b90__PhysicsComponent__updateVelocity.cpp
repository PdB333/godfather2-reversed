// FUNC_NAME: PhysicsComponent::updateVelocity
void __thiscall PhysicsComponent::updateVelocity(int* thisPtr, float* targetPos, float maxSpeed, uint flags)
{
    // Load velocity components from fixed-point ints at this+0x60,0x64,0x68,0x6C
    float vx = (float)thisPtr[0x18]; // +0x60
    float vy = (float)thisPtr[0x19]; // +0x64
    float vz = (float)thisPtr[0x1a]; // +0x68
    float vw = (float)thisPtr[0x1b]; // +0x6C (might be extra component or prev value)

    // Compute current speed magnitude (3D vector)
    float speed = sqrt(vx*vx + vy*vy + vz*vz);

    // Global epsilon to avoid division by zero / jitter
    extern float g_speedEpsilon; // _DAT_00d577a0

    // Clamp velocity magnitude if it exceeds maxSpeed but not below epsilon
    if ((g_speedEpsilon < speed) && (speed < maxSpeed)) {
        float scale = maxSpeed / speed;
        thisPtr[0x22] = (int)maxSpeed; // store max speed as int at +0x88
        thisPtr[0x18] = (int)(scale * vx);
        thisPtr[0x19] = (int)(scale * vy);
        thisPtr[0x1a] = (int)(scale * vz);
        thisPtr[0x1b] = (int)(scale * vw); // scale the fourth component as well
    }

    // Compute delta vector = targetPos - current velocity? (puzzling, but following code)
    // pfVar1 = &thisPtr[4] (offset 0x10, treat as float[3])
    float* delta = (float*)(thisPtr + 4); // +0x10

    delta[0] = targetPos[0] - vx;
    delta[1] = targetPos[1] - vy;
    delta[2] = targetPos[2] - vz;

    // Attempt to resolve delta with collision functions
    // FUN_006d0ee0 may test or adjust delta against targetPos
    if (FUN_006d0ee0(targetPos, delta, 0) == 0) {
        // If first test fails, try second function
        if (FUN_006d1890(delta, targetPos) != 0) {
            // If second succeeds, recompute velocity from corrected delta
            // Actually: new velocity = targetPos - corrected delta
            thisPtr[0x18] = (int)(targetPos[0] - delta[0]);
            thisPtr[0x1b] = (int)(targetPos[3] - 0.0f); // note: targetPos[3] might be unused
            // Note: the original code only updates y and z components using stored delta values
            // This is a literal reconstruction of the decompiled logic.
        }
    }

    // Call virtual method on sub-object at offset +8 (embedded component)
    // vtable index 0x18/4 = 6 (some update/move function)
    (*(void (__thiscall **)(int*, float*, uint))(*(int*)(thisPtr + 8) + 0x18))(thisPtr + 8, targetPos, flags);
}