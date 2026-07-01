// FUNC_NAME: TargetingManager::isValidCombatTarget
// Address: 0x007cbcd0
// Role: Determines if an attacker can engage a target, checking numerous conditions including components, family alignment, state flags, distance, and line of sight.

uint __fastcall TargetingManager::isValidCombatTarget(Sentient* attacker, Sentient* target)
{
    // attacker at param_1 (ECX), target at param_2 (EDX)
    int* pAttacker = (int*)attacker;
    int* pTarget = (int*)target;

    // Early fail if attacker has flag 0x929 bit 8 set, or target is null
    if ((pAttacker[0x929] >> 8 & 1) != 0 || pTarget == nullptr)
        goto fail;

    // Check global pause/menu state
    if (isGamePaused())
        goto fail;

    // Try to get a specific component from target using hash 0x369ac561 (likely "CombatComponent" or "CrewComponent")
    Sentient* component = nullptr; // Output parameter for component lookup
    bool componentFound = (**(bool (__thiscall**)(Sentient*, uint, Sentient**))(*pTarget + 0x10))(pTarget, 0x369ac561, &component);
    // Note: unaff_EBX is a register leftover; we treat it as a success condition from previous call. If component lookup failed or unaff_EBX is zero, fail.
    // unaff_EBX likely holds a global flag from the calling context (e.g., "isComponentValid").
    // Since we cannot resolve, we assume the condition as: if(!componentFound || !globalComponentValid) goto fail;
    // We'll ignore unaff_EBX for reconstruction.
    if (!componentFound) // simplified: treat as if unaff_EBX always non-zero
        goto fail;

    // Check if target and attacker belong to the same family (or crew) using two separate checks
    if (!isSameFamily(pTarget, g_familyId_A) || !isSameFamily(pTarget, g_familyId_B))
        goto fail;

    // Check some global game state (maybe free roam enabled, not in special mode)
    if (!isFastTravelAllowed())
        goto fail;

    // Ensure attacker and target are not already in certain combat states (offset 0x79c non-zero)
    if (pAttacker[0x79c] != 0 || pTarget[0x79c] != 0)
        goto fail;

    // Check various game state flags: 4,5,0x31,0xc – likely "isInVehicle", "isInConversation", etc.
    if (isGameStateActive(4) || isGameStateActive(5) || isGameStateActive(0x31) || isGameStateActive(0xc))
        goto fail;

    // Another global pause check
    if (isGamePaused())
        goto fail;

    // Compare some global time/ distance factor; fail if less than threshold
    float timeFactor = getGlobalTimeFactor(); // dummy name
    if (timeFactor < g_maxCombatDistance)
        goto fail;

    // Check if mission 9 is active (main story mission?)
    if (isMissionActive(9))
        goto fail;

    // Now check target's state byte at offset 0x6e3
    if (pTarget[0x6e3] != 0)
    {
        // Get target's position components (likely from a hash or inline code)
        int posX = getPositionComponent();
        int posY = getPositionComponent();
        int posZ = getPositionComponent();
        float radius = (**(float (__thiscall**)(Sentient*))(*pTarget + 0x214))(pTarget); // virtual getCombatRadius?
        // Check distance between target and an offset (maybe attack range)
        bool inRange = isWithinRange(posX + 0x30, posY + 0x30, posZ + 0x20, radius);
        if (!inRange)
        {
            // If not in range, clear the flag
            inRange = false;
        }
        else
        {
            // Now get attacker's position
            int attPosX = getPositionComponent();
            int attPosY = getPositionComponent();
            int attPosZ = getPositionComponent();
            float attRadius = (**(float (__thiscall**)(Sentient*))(*pAttacker + 0x214))(pAttacker);
            // Check if attacker is within range of target offset
            bool attInRange = isWithinRange(attPosX + 0x30, attPosY + 0x30, attPosZ + 0x20, attRadius);
            if (!attInRange)
            {
                // If attacker not in range, clear flag
                inRange = false;
            }
            else
            {
                inRange = true;
            }
        }

        // Re-evaluate based on target state byte
        if (pTarget[0x6e3] == 0x04) // special state?
            goto after_distance;

        if (!inRange)
            goto fail;

        // Check target's bitfield at offset 0x208 bit 1 (bit 2 shifted by 2)
        if ((pTarget[0x208] >> 2) & 1)
            goto after_distance;

        // Check if target has some component/state via function
        if (hasSpecialComponent(pTarget))
        {
            // If target has it, query something from attacker
            bool attackerSpecial = queryAttackerSpecial(pAttacker);
            inRange = attackerSpecial;
            goto after_distance;
        }
        else
        {
            inRange = true; // set flag to true
            // Note: uVar3 set to 0? later used
        }
    }

after_distance:
    // If attacker pointer (actually bool) is non-zero (from componentFound?)
    // Note: param_1 is actually attacker pointer, but they use (char)param_1 which is low byte.
    // This might be a leftover; we treat as a flag from earlier.
    if (componentFound)
    {
        // Check line of sight
        if (!isLineOfSightClear())
        {
            // If LOS blocked, try to initiate action (maybe charge or move)
            bool actionStarted = startEngageAction(pTarget, g_familyId_A, g_familyId_B, 0x30000);
            componentFound = !actionStarted; // invert
        }
        else
        {
            // LOS clear, keep flag true
            componentFound = true;
        }
    }

    if (componentFound)
    {
        // Check attacker's flag at offset 0x239 bit 17
        if (!((pAttacker[0x239] >> 0x11) & 1)) // bit is not set
        {
            // Return composite: high 24 bits from attacker's bit 25, low 8 bits = 1
            return ((pAttacker[0x239] >> 0x19) << 8) | 1;
        }
    }

fail:
    return 0; // or some error code
}