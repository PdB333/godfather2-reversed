// FUNC_NAME: Gun::updateRecoil

// Function at 0x0070e140 updates the gun's spread/recoil for a given slot.
// param_2 = isFiring flag (non-zero means currently firing)
// param_3 = slot index (e.g., weapon slot)
void __thiscall Gun::updateRecoil(int thisPtr, int isFiring, int slotIndex) {
    float *currentSpread;               // pointer to current spread for this slot (at this+0x2DC + slot*4)
    float fVar2;                        // random float result
    float fVar3;                        // time delta
    // Sound handle struct passed to stop/play sound
    struct {
        int handle;                     // +0x00 sound handle
        int unknown;                    // +0x04
        char flag;                      // +0x08 flag
    } soundHandle;
    
    if (isFiring != 0) {
        currentSpread = (float *)(thisPtr + 0x2DC + slotIndex * 4); // +0x2DC: currentSpread[slot]
        // Global game time (DAT_01205228) is compared to a stored time (this+0x254 = lastFireTime)
        if (DAT_01205228 <= *(float *)(thisPtr + 0x254)) {
            // Time has not elapsed enough (should not happen? maybe inverted logic)
            // fVar3 = lastFireTime - gameTime (negative? but since gameTime <= lastFireTime, fVar3 <= 0)
            fVar3 = *(float *)(thisPtr + 0x254) - DAT_01205228;
            if (*(char *)(slotIndex + 0x221 + thisPtr) == '\0') {
                // Negative spread direction
                *currentSpread = *(float *)(thisPtr + 0x298 + slotIndex * 4) - 
                    (_DAT_00d5780c - fVar3 / *(float *)(thisPtr + 0x248)) * 
                    *(float *)(thisPtr + 0x258 + slotIndex * 4); // 0x258 = spreadScale[slot]
            } else {
                // Positive spread direction
                *currentSpread = (_DAT_00d5780c - fVar3 / *(float *)(thisPtr + 0x244)) * 
                    *(float *)(thisPtr + 0x258 + slotIndex * 4) + 
                    *(float *)(thisPtr + 0x298 + slotIndex * 4);
            }
        } else {
            // Time has elapsed beyond threshold -> reset spread (new shot)
            if (*(char *)(slotIndex + 0x221 + thisPtr) == '\0') {
                *(char *)(slotIndex + 0x231 + thisPtr) = 0; // +0x231: some reset flag
                fVar2 = (float)FUN_004aabd0(); // random value [0,1]?
                *currentSpread = fVar2 * *(float *)(thisPtr + 0x250); // +0x250: spreadMaxNegative
                // Store sound handle for this slot
                soundHandle.handle = *(int *)(thisPtr + 0x3A0); // +0x3A0: negativeSoundHandle
                soundHandle.unknown = 0;
                soundHandle.flag = 0;
                FUN_00408a00(&soundHandle, 0); // stop the negative sound
            } else {
                *(char *)(slotIndex + 0x221 + thisPtr) = 0; // clear direction flag
                fVar2 = (float)FUN_004aabd0();
                *currentSpread = fVar2 * *(float *)(thisPtr + 0x24C); // +0x24C: spreadMaxPositive
                soundHandle.handle = *(int *)(thisPtr + 0x3A8); // +0x3A8: positiveSoundHandle
                soundHandle.unknown = 0;
                soundHandle.flag = 0;
                FUN_00408a00(&soundHandle, 0); // stop the positive sound
            }
        }
        // After updating spread, call a function that likely applies/plays the spread effect
        FUN_004aa8c0(*currentSpread);
    }
}