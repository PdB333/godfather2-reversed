// FUN_008a0010: DonControlGadget::updateAbilityCooldowns

void __thiscall DonControlGadget::updateAbilityCooldowns(DonControlGadget *this, int *pUpdateData)
{
    char cVar1;
    int iVar2;
    float fDeltaTime;
    float fTimer;
    
    // Base class update (likely updates the event context)
    baseUpdate(pUpdateData);
    
    fDeltaTime = DAT_012067e8; // frame delta time
    int eventType = *pUpdateData;
    
    // Handle primary cooldown (e.g. ability slot A)
    if ((DAT_012069c4 == eventType) && (*(bool *)(DAT_01129914 + 0xd3))) {
        // Cooldown timer at +0x154
        if (DAT_00e44598 < this->mPrimaryCooldownTimer) {
            this->mPrimaryCooldownTimer -= fDeltaTime;
            if (this->mPrimaryCooldownTimer <= 0.0f) {
                this->mPrimaryCooldownTimer = 0.0f;
                // Get player instance from global singleton
                iVar2 = **(int **)(DAT_012233a0 + 4);
                if ((iVar2 != 0) && (iVar2 - 0x1f30 != 0)) {
                    cVar1 = isAbilityCapable(); // FUN_00481620()
                    if (cVar1 == '\0') {
                        // Not capable – check alternative action
                        if (isSpecialActionEnabled()) { // FUN_00481640()
                            stopCurrentAbility(iVar2 - 0x1ed8); // FUN_004a8ec0
                            scheduleDeferredAction(0x8a001f, 0x8a00bd); // FUN_0089e2a0
                        }
                    } else {
                        // Capable – start ability
                        activatePrimaryAbility(); // FUN_0089c1d0
                        activateDerivedAction(iVar2 - 0x1f30); // FUN_0089f160
                    }
                }
            }
        }
        // Secondary cooldown at +0x158
        if (DAT_00e44598 < this->mSecondaryCooldownTimer) {
            this->mSecondaryCooldownTimer -= fDeltaTime;
            if (this->mSecondaryCooldownTimer <= 0.0f) {
                this->mSecondaryCooldownTimer = 0.0f;
                return;
            }
        }
    } else if (((this->mEventID1 == eventType) || (this->mEventID2 == eventType)) && 
               (DAT_0112a834 != 0)) {
        // Handle event-based update for different ability types
        if (isSpecialActionEnabled() && 
            (*(bool *)(DAT_01129914 + 0xd3) == '\0') && 
            (pUpdateData[1] != 0)) {
            // Get target object from update data
            int *pTargetBase = *(int **)(pUpdateData[1] + 4);
            if (pTargetBase == 0) {
                pTargetBase = 0;
            } else {
                pTargetBase = (int *)((char *)pTargetBase - 0x48);
            }
            cVar1 = isAbilityCapable();
            if (cVar1 != '\0') {
                if (isSpecialActionEnabled()) {
                    int abilityParam = -1;
                    if (this->mEventID1 == eventType) {
                        abilityParam = *(int *)(pTargetBase + 0x1ef4 / 4); // offset 0x1ef4
                    }
                    activateSpecificAbility(abilityParam); // FUN_0089c4d0
                }
            }
        }
    }
    return;
}