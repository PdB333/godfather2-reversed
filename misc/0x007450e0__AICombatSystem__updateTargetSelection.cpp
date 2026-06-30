// FUNC_NAME: AICombatSystem::updateTargetSelection
void __cdecl updateTargetSelection(AICombatComponent* pComponent, SimManager* pManager, TargetingConfig* pConfig) {
    int* piCurrentTargetPtr; // pointer to m_pCurrentTarget in component
    bool bIsActive; // flag check
    int iThreatEntity; // result from interest point search
    int iEntityBase; // base of potential target entity
    int iStateCheck; // result from state check function
    int iTemp1, iTemp2; // temporary entity IDs or pointers
    float fDx, fDy, fDz; // distance components
    float fDistSq; // squared distance
    uint32 uAction; // action type to set

    // --- Step 1: Check config flag to possibly fetch a threat/interest entity ---
    iThreatEntity = 0;
    if ((pConfig->m_flags & 0x4) != 0) {
        iThreatEntity = getInterestingTarget(); // Likely returns a potential target (e.g., pointer to entity +0x48)
    }

    // --- Step 2: Get the base entity from the manager's stored pointer (maybe a player character) ---
    if (pManager->m_pPlayerComponent == 0) { // Offset 0x24c4
        iEntityBase = 0;
    } else {
        iEntityBase = pManager->m_pPlayerComponent - 0x48; // Subtract offset to get base entity
    }

    // --- Step 3: Check game state and distance to decide if we should use the base entity as target ---
    iStateCheck = getCombatState(); // e.g., enterCombat or something
    if ((iEntityBase != 0) &&
        ((bIsActive = isPlayerInCombat(), bIsActive) ||
         ((iStateCheck != 0 && (bIsActive = isPlayerAlerted(), bIsActive))))) {
        // Player is either in combat or (in some state and alerted)
        iTemp1 = getPosition(); // Position of first entity (likely player)
        iTemp2 = getPosition(); // Position of second entity (likely iThreatEntity? But iThreatEntity may be zero)
        fDx = *(float*)(iTemp1 + 0x30) - *(float*)(iTemp2 + 0x30); // X difference (vector3 at +0x30)
        fDy = *(float*)(iTemp1 + 0x34) - *(float*)(iTemp2 + 0x34); // Y
        fDz = *(float*)(iTemp1 + 0x38) - *(float*)(iTemp2 + 0x38); // Z
        fDistSq = fDx*fDx + fDy*fDy + fDz*fDz;
        // If distance is less than threshold (pConfig->m_fDistThreshold1), switch to base entity
        if (fDistSq < pConfig->m_fDistThreshold1 * pConfig->m_fDistThreshold1) {
            iThreatEntity = iEntityBase;
        }
    }

    // --- Step 4: If we have a target (iThreatEntity) and the component exists, update component's target ---
    if ((iThreatEntity != 0) && (pComponent != 0)) {
        // Get positions of current target (if any?) and new target
        iTemp1 = getPosition(); // likely position of something
        iTemp2 = getPosition(); // likely position of new target (iThreatEntity?)
        fDx = *(float*)(iTemp2 + 0x30) - *(float*)(iTemp1 + 0x30);
        fDy = *(float*)(iTemp2 + 0x34) - *(float*)(iTemp1 + 0x34);
        fDz = *(float*)(iTemp2 + 0x38) - *(float*)(iTemp1 + 0x38);
        fDistSq = fDx*fDx + fDy*fDy + fDz*fDz;
        // Choose action based on distance to second threshold
        if (fDistSq >= pConfig->m_fDistThreshold2) {
            uAction = pConfig->m_uFarAction;      // e.g., shoot or approach
        } else {
            uAction = pConfig->m_uNearAction;     // e.g., melee or flee
        }

        // --- Update the component's current target pointer (offset +0x64) ---
        piCurrentTargetPtr = (int*)(pComponent + 0x64); // m_pCurrentTarget
        int* pNewTarget = (int*)(iThreatEntity + 0x48); // Target object starts at offset +0x48
        if (*piCurrentTargetPtr != pNewTarget) {
            if (*piCurrentTargetPtr != 0) {
                releaseTarget(piCurrentTargetPtr); // Release old target reference
            }
            *piCurrentTargetPtr = pNewTarget; // Set new target
            if (pNewTarget != 0) {
                pComponent->m_pBackLink = *(void**)(iThreatEntity + 0x4c); // Store back pointer? (offset +0x4c)
                *(void**)(iThreatEntity + 0x4c) = piCurrentTargetPtr; // Link target back to this component
            }
        }
        // Store action and a config value (speed, strength?) into component
        pComponent->m_uActionType = uAction;         // offset +0x60
        pComponent->m_fActionParam = *(float*)(pConfig + 0x74); // offset +0x5c
    }
    return;
}