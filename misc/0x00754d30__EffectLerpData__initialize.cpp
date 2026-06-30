// FUNC_NAME: EffectLerpData::initialize
void __thiscall EffectLerpData::initialize(float *sourcePos, float *targetDir, uint flags, float speed, bool noRotate, bool startActive)
{
    // +0x50: active flag
    *(byte *)(this + 0x50) = 1;
    
    // +0x58: flags
    *(uint *)(this + 0x58) = flags;
    
    // If bit 0 set, call some allocation/creation function and store result at +0x5c
    if ((flags & 1) != 0) {
        *(int *)(this + 0x5c) = FUN_0045eea0(); // likely creates a child object or handle
    }
    
    // Store source position at +0x68 (x,y) and +0x70 (z)
    *(Vector2 *)(this + 0x68) = *(Vector2 *)sourcePos; // copy first two floats
    *(float *)(this + 0x70) = sourcePos[2];
    
    // Compute time to reach player at current speed
    float time = 0.0f;
    if (speed > 0.0f) {
        int *playerObj = FUN_00471610(); // pointer to player object
        float dx = sourcePos[0] - *(float *)(playerObj + 0x30); // player pos.x
        float dy = sourcePos[1] - *(float *)(playerObj + 0x34); // player pos.y
        float dz = sourcePos[2] - *(float *)(playerObj + 0x38); // player pos.z
        time = sqrt(dz*dz + dy*dy + dx*dx) / speed; // distance / speed
    }
    // +0x64: computed time
    *(float *)(this + 100) = time;
    
    // +0x60: speed
    *(float *)(this + 0x60) = speed;
    
    // Store target direction at +0x74 (x,y) and +0x7c (z)
    *(Vector2 *)(this + 0x74) = *(Vector2 *)targetDir;
    *(float *)(this + 0x7c) = targetDir[2];
    
    // Compute angular difference between targetDir.x and player's facing
    double targetYawDeg = (double)targetDir[0];
    FUN_00b9a9fa(); // FPU setup? (likely no effect)
    float targetYawRad = (float)targetYawDeg * DAT_00e44748; // degrees to radians
    
    int *playerObj = FUN_00471610();
    double playerYawDeg = (double)*(float *)(playerObj + 0x20); // player facing angle in degrees
    FUN_00b9a9fa(); // FPU setup?
    float playerYawRad = (float)playerYawDeg * DAT_00e44748;
    
    // Normalize angular difference to [-PI, PI]
    if (DAT_00e44600 < targetYawRad - playerYawRad) { // if difference > max allowed
        targetYawRad -= DAT_00d5f4b4; // subtract 2*PI
    }
    if (targetYawRad - playerYawRad < DAT_00d5f4b0) { // if difference < -PI
        targetYawRad += DAT_00d5f4b4; // add 2*PI
    }
    
    float angularDiff = (targetYawRad - playerYawRad) * DAT_00e445c8; // scale by factor
    
    // If flags include bit 2, adjust angularDiff based on bit 3
    if ((*(uint *)(this + 0x58) & 2) != 0) {
        if ((*(uint *)(this + 0x58) >> 2 & 1) == 0) {
            if (angularDiff > 0.0f) {
                angularDiff -= DAT_00d5d70c; // subtract small angle step
            }
        } else {
            if (angularDiff < 0.0f) {
                angularDiff += DAT_00d5d70c; // add small angle step
            }
        }
    }
    
    // Set angular velocity (angle/time) if speed > 0 and noRotate is false
    if ((speed <= 0.0f) || noRotate) {
        *(int *)(this + 0x84) = 0;
    } else {
        *(float *)(this + 0x84) = angularDiff / speed; // angular velocity
    }
    // Store final angular difference
    *(float *)(this + 0x88) = angularDiff;
    
    // Initialize remaining fields
    *(int *)(this + 0x8c) = 0;
    *(byte *)(this + 0x90) = 0;
    *(byte *)(this + 0x80) = 0;
    
    // Set start active flag at bit 0 of +0x94
    if (startActive) {
        *(uint *)(this + 0x94) |= 1;
    } else {
        *(uint *)(this + 0x94) &= 0xfffffffe;
    }
}