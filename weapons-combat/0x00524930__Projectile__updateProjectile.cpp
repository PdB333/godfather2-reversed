// FUNC_NAME: Projectile::updateProjectile
// Function address: 0x00524930
// Role: Handles projectile lifetime, movement, and child object updates.

void __thiscall Projectile::updateProjectile(
    bool isActive,
    int someId1,
    int someId2,
    float dt)
{
    char randomResult;
    int childIndex;
    int numChildren;
    float scaledDt;
    
    float localPosX;
    int localPosY;
    float localPosZ;
    float localPosW;
    
    // Check if projectile is active and not already flagged as "dead" (bit1 at +0x460)
    if (isActive && !(*(uint16*)(this + 0x460) & 2)) {
        randomResult = this->checkRandomCondition(); // FUN_0051eca0
        if (randomResult == 0) {
            // Increment lifetime counter at +0x462
            *(uint16*)(this + 0x462) = *(uint16*)(this + 0x462) + 1;
            if (*(uint16*)(this + 0x462) < 6) {
                return; // Wait for more frames
            }
            // Apply gravity / movement from base object (offset +0x10 -> +0x6c)
            *(float*)(this + 0x14) = *(float*)(*(int*)(this + 0x10) + 0x6c) + *(float*)(this + 0x14);
            return;
        }
        // Random condition met: reset state and set dead flag
        this->resetProjectileState(); // FUN_00523340
        *(uint16*)(this + 0x460) |= 2;
    }
    
    // Save local transformation (position/rotation) from +0x28..+0x34
    localPosX = *(float*)(this + 0x28);
    localPosY = *(int*)(this + 0x2c); // Actually undefined4, but used as part of vector
    localPosZ = *(float*)(this + 0x30);
    localPosW = *(float*)(this + 0x34);
    
    // Transform local position using world transform (if available)
    if (*(int*)(DAT_01125414 + (uint)(DAT_01125388) * 0x38) != 0) {
        transformPoint(DAT_011252e8,
                       *(int*)(DAT_01125414 + (uint)(DAT_01125388) * 0x38),
                       &localPosX); // FUN_0060add0
    }
    
    // Update local position from base object (offset +0x10->+0x4c), then adjust by projection factors
    localPosX = *(float*)(*(int*)(this + 0x10) + 0x4c);
    localPosY = *(int*)(*(int*)(this + 0x10) + 0x50); // part of vector
    localPosZ = ONE_FLOAT - *(float*)(this + 0x20) * localPosX;
    localPosW = ONE_FLOAT - *(float*)(this + 0x24) * localPosX;
    
    // Second transformation (likely for different coordinate space)
    if (*(int*)(DAT_01125418 + (uint)(DAT_01125388) * 0x38) != 0) {
        transformPoint(DAT_011252e8,
                       *(int*)(DAT_01125418 + (uint)(DAT_01125388) * 0x38),
                       &localPosX); // FUN_0060add0
    }
    
    // Scale delta time by a multiplier from +0x18
    scaledDt = *(float*)(this + 0x18) * dt;
    
    // Update child objects if threshold is met and children exist
    if (THRESHOLD_F64 <= scaledDt && 0 < *(char*)(this + 0x450)) {
        numChildren = *(char*)(this + 0x450);
        for (childIndex = 0; childIndex < numChildren; childIndex++) {
            updateChildObject(this + 0x90 + childIndex * 0xa0,
                              *(int*)(this + 0x10),
                              someId1,
                              someId2,
                              scaledDt); // FUN_00522cb0
        }
    }
}