// FUNC_NAME: NPC::enterAttackState
void __thiscall NPC::enterAttackState(NPC* this) {
    bool bRandomSuccess;
    float fFireRate;
    uint uSoundHandle;

    // Check if we are in attack state (2) and not already firing
    if ((this->m_nState == 2) && ((this->m_nStateFlags & 0x4000) == 0)) {
        // Stop any previous sound? (FUN_00875da0 likely stops a sound)
        FUN_00875da0();
        uSoundHandle = DAT_00d5d7b8;  // Global sound handle
        this->m_nStateFlags |= 0x4000; // Mark as firing
        // Start a sound? (FUN_005fea00 with same handle twice)
        FUN_005fea00(uSoundHandle, uSoundHandle);

        // Determine fire rate
        if ((this->m_nBehaviorFlags & 0x800) == 0) {
            // Virtual call to get fire rate from vtable+0x2c8
            fFireRate = (this->vtable->getFireRate)();
        } else {
            // Use global constant for fire rate
            fFireRate = DAT_00d756fc;
        }
        // Set the fire rate (FUN_00860360 likely sets fire rate)
        FUN_00860360(fFireRate);

        // Random chance to fail (bVar1) if no ammo? (m_nAmmo == 0)
        bRandomSuccess = true;
        if (this->m_nAmmo == 0) {
            // rand() gives int, scale by two globals and compare to another global
            float fRandScale = (float)_rand() * DAT_00e44590 * DAT_00d5e288;
            if (DAT_00d5d934 < fRandScale) {
                bRandomSuccess = false;
            }
        }

        // If not already playing fire sound? (m_nBehaviorFlags bit 6)
        if ((this->m_nBehaviorFlags & 0x40) == 0) {
            // Trigger sound effect via sub-object (m_pSoundObject + 0x28)
            (*(code **)(this->m_pSoundObject + 0x28))(0x10); // 0x10 might be a sound ID
            this->m_nBehaviorFlags |= 0x40; // Mark sound played
        }

        // Set a timer or countdown to global
        this->m_nFireTimer = DAT_00d5c458;

        if (bRandomSuccess) {
            // Actually fire a bullet? (FUN_0087d560 likely spawns projectile)
            FUN_0087d560(1);
        }

        // If behavior flag bit 21 is set, also spawn extra effect?
        if ((this->m_nBehaviorFlags & 0x200000) != 0) {
            FUN_0087bd50(1);
        }

        // Cleanup and reset state
        FUN_005fe6f0(); // Probably reset bullet count or muzzle flash
        this->m_nStateFlags &= 0xf1cfffff; // Clear some flags (bits 20-23, 28-31?)
        this->m_nCooldownA = 0; // +0x3da
        this->m_nCooldownB = 0; // +0x3d7
        this->m_nUnknownTimer = 0; // +0x3e4
        this->m_nAnotherTimer = 0; // +0x402
        this->m_nStateFlags &= 0xefffffff; // Clear bit 28

        // Transition to next state? (FUN_008659a0 likely state update)
        FUN_008659a0();
    }
}

// NOTE: Offsets are as follows:
// this+0xF2C (0x3cb*4) -> m_nState (likely enum)
// this+0xF28 (0x3ca*4) -> m_nStateFlags (bitfield)
// this+0xC88 (0x322*4) -> m_nBehaviorFlags (bitfield)
// this+0xB90 (0x2e4*4) -> m_nAmmo (int)
// this+0x58  (0x16*4)  -> m_pSoundObject (pointer)
// this+0xA28 (0x28a*4) -> m_nFireTimer (int)
// this+0xF68 (0x3da*4) -> m_nCooldownA
// this+0xF5C (0x3d7*4) -> m_nCooldownB
// this+0xF90 (0x3e4*4) -> m_nUnknownTimer
// this+0x1008 (0x402*4)-> m_nAnotherTimer
// Globals: DAT_00d5d7b8, DAT_00d756fc, DAT_00d5c458, DAT_00d5d934, DAT_00e44590, DAT_00d5e288