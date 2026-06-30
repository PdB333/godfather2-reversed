// FUNC_NAME: Player::handleHitTarget
// Address: 0x006ae9f0
// Handles when a player's weapon hits a target (NPC/vehicle). Checks conditions (not dead, has state, not certain vehicle types, damage threshold) and plays impact sound, checks health components for invulnerability flags, and triggers hit reaction events.

void __thiscall Player::handleHitTarget(Player* this, int targetEntity)
{
    float fDamageMult;
    float fVolume;
    int iTargetState;
    char cFreeRoamCheck;
    int iTemp;
    int* pVtable;
    unsigned int uParamA;
    unsigned int uParamB;

    // Check bit 17 of target's flags (likely alive/active flag): must be 0 to proceed (?)
    if (((~(byte)(*(uint*)(targetEntity + 0x18c) >> 0x11) & 1) != 0) &&
        (*(int*)(*(int*)(this + 0x180) + 0xd8) != 0) &&  // Some pointer from this+0x180 must be non-zero
        (iTemp = FUN_0043b870(DAT_0112afb8), iTemp != 0) &&  // Get game manager
        (iTargetState = *(int*)(iTemp + 0x1c), iTargetState != 0 && iTargetState != 0x3c) &&  // Not state 0 or 0x3c (dead?)
        (iTemp = **(int**)(DAT_012233a0 + 4), iTemp != 0) &&  // Global pointer to some object (player camera/vehicle?)
        (iTemp != 0x1f30 && iTemp != -0x794)) &&             // Not certain vehicle types (0x1f30 = 7984, -0x794 = -1940)
       ((*(float*)(iTemp + 0x804) < 0.0) ||                 // Condition: damage modifier or similar less than 0, OR
        (*(float*)(iTargetState + 0xc0) + *(float*)(iTemp + 0x804) < DAT_01205228)))  // Sum of two floats below threshold
    {
        // Set damage/modifier to threshold
        *(float*)(iTemp + 0x804) = DAT_01205228;

        fVolume = *(float*)(targetEntity + 400);          // Possibly target's volume or health delta
        fDamageMult = *(float*)(iTargetState + 0x58);    // Damage multiplier from state
        FUN_0078b270(4);                                   // Set audio group/slot
        FUN_0078b4b0(fVolume * fDamageMult, 0, 1);        // Play impact sound with calculated volume
        FUN_00402050(&DAT_0112a588, 0);                    // Reset or stop some effect (recoil?)

        // Check for hit component (invulnerability flags)
        iTemp = FUN_006ad790(targetEntity, 0x36cac259);   // Get component by hash (e.g., health component)
        if (iTemp == 0)
        {
            iTemp = FUN_006ad7c0(targetEntity, 0x6a8acf44); // Alternative component lookup
            if (iTemp != 0)
            {
                cFreeRoamCheck = FUN_00690150(0x5d);       // Check some condition (weapon type flag?)
                if (cFreeRoamCheck != '\0')
                    return;
            }
        }
        else if ((*(byte*)(iTemp + 0x290) & 1) != 0)      // Invulnerability flag set?
            return;

        cFreeRoamCheck = FUN_00732380();                   // Check if player is in free roam mode
        if (cFreeRoamCheck != '\0')
        {
            iTemp = **(int**)(DAT_012233a0 + 4);           // Global pointer (same as above)
            if (iTemp != 0)
            {
                iTemp += -0x1f30;                          // Adjust pointer by subtracting vehicle type ID?
                if (iTemp != 0)
                {
                    pVtable = (int*)FUN_006ad7f0(iTemp);   // Get vtable or interface
                    (**(code**)(*pVtable + 0x28))(0x848db96, 0, 0xffffffff, 0); // Call virtual function (send event? 0x848db96 hash)

                    uParamA = 0;
                    uParamB = FUN_006fbc40(0, 0);          // Begin message
                    FUN_007f96a0(0x888ad614, 0x74, uParamB, uParamA); // Send message with hash 0x888ad614 (hit reaction?)
                    FUN_006fbc70();                         // End message

                    cFreeRoamCheck = FUN_0078a7d0();       // Check for additional condition (e.g., target type)
                    if (cFreeRoamCheck != '\0')
                    {
                        uParamA = 0;
                        uParamB = FUN_006fbc40(0, 0);
                        FUN_007f96a0(0x8908c696, 0x74, uParamB, uParamA); // Send another message (maybe death impact)
                        FUN_006fbc70();
                    }
                }
            }
        }
    }
    return;
}