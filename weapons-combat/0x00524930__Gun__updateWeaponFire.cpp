// FUNC_NAME: Gun::updateWeaponFire
void __thiscall Gun::updateWeaponFire(Gun* this, bool isFiring, unsigned int param_3, unsigned int param_4, float deltaTime)
{
    char canFireOrHasAmmo;
    int i;
    int slotIndex;
    Vector3 worldPos; // local_20, local_1c, local_18, actually float[4] but used as Vector3+pad
    float screenX, screenY; // local_18, local_14 after reassign

    // Check if firing and not in cooldown (bit1 of flags at +0x460)
    if (isFiring && ((this->flags & 2) == 0)) {
        canFireOrHasAmmo = FUN_0051eca0(); // maybe canFire() or hasAmmo()
        if (canFireOrHasAmmo == 0) {
            // No ammo or cannot fire, increment fire attempt counter
            this->fireAttemptCounter = this->fireAttemptCounter + 1; // +0x462
            if (this->fireAttemptCounter < 6) {
                return; // Wait for more attempts before forcing cooldown
            }
            // Exceeded attempts, apply damage to weapon? Or add force?
            this->damage = *(float*)(*(int*)(this->owner + 0x10) + 0x6c) + this->damage; // +0x14
            return;
        }
        // Can fire, spawn projectile
        FUN_00523340(this); // spawnProjectile
        this->flags = this->flags | 2; // set cooldown bit
    }

    // Save current world position from fields +0x28..+0x34
    worldPos.x = this->position.x;
    worldPos.y = this->position.y; // actually local_1c is undefined4 but likely float
    worldPos.z = this->position.z;
    // worldPos.w? Actually local_14 is another float, but we'll treat as Vector3
    // There is a fourth float at +0x34? Probably pad or w component

    // If current controller is active (global array of controllers)
    if (*(int*)(&controllerArray + (unsigned int)currentControllerIndex * 0x38) != 0) {
        FUN_0060add0(screenTransform, *(int*)(&controllerArray + (unsigned int)currentControllerIndex * 0x38), &worldPos);
    }

    // Now compute screen position from owner's data
    worldPos.x = *(float*)(*(int*)(this->owner + 0x10) + 0x4c); // some offset
    worldPos.y = *(float*)(*(int*)(this->owner + 0x10) + 0x50); // another offset
    screenX = (DAT_00e44564) - (this->aimDirection.x * worldPos.x); // +0x20
    screenY = (DAT_00e44564) - (this->aimDirection.y * worldPos.x); // +0x24
    // Note: worldPos.x reused as scale factor? Actually local_20 is overwritten by first component

    // If another controller component exists
    if (*(int*)(&controllerArray2 + (unsigned int)currentControllerIndex * 0x38) != 0) {
        FUN_0060add0(screenTransform, *(int*)(&controllerArray2 + (unsigned int)currentControllerIndex * 0x38), &worldPos);
    }

    // Scale deltaTime by speed factor
    deltaTime = this->speed * deltaTime; // +0x18

    // If damage threshold exceeded and there are active projectiles
    if ((DAT_00e2af44 <= deltaTime) && (this->activeCount > 0)) { // +0x450
        // Process each projectile slot
        for (i = 0; i < this->activeCount; i++) {
            slotIndex = i;
            // Each slot is 0xa0 bytes starting at +0x90
            FUN_00522cb0(this->projectileSlots + slotIndex * 0xa0, this->owner, param_3, param_4, deltaTime);
        }
    }
    return;
}