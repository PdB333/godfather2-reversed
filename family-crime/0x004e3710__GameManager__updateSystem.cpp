// FUNC_NAME: GameManager::updateSystem
// Address: 0x004e3710
// Role: Main game logic update dispatcher. Switches on internal state to run subsystem updates.
// Uses global flags (g_* arrays) to check which features are enabled before calling specific update functions.

void GameManager::updateSystem()
{
    // Member variable stored in EAX – likely an enum or state integer
    int updateState = m_updateState; // e.g., 0 = reset, 1 = normal tick

    bool bVar3, bVar4, bVar5, bVar6, bVar7;
    char cVar8, cVar9;
    uint uVar1, uVar10, uVar11, uVar12, uVar13;
    int iVar14;

    uVar12 = 0;

    if (updateState < 0)
        return;

    if (updateState == 1)
    {
        // --- Update step for normal frame ---

        // Initialise base controls system
        FUN_00531d40();
        if (g_controlsEnabled1 == '\0')
            FUN_0052fe10(); // Controls init 1
        if (g_controlsEnabled2 == '\0')
            FUN_005167d0(); // Controls init 2

        cVar8 = g_timeScale; // global time scale factor
        cVar9 = '\0';
        uVar15 = 0;
        uVar10 = 0;
        uVar11 = 0;
        uVar13 = 0;

        if (g_feature1Enabled == '\0')
        {
            cVar9 = FUN_00515a20(); // Check some per-frame condition
            if (cVar9 != '\0')
            {
                if ((g_heatThreshold1 < g_globalHeat) ||
                    ((g_heatThreshold2 < g_globalHeat && g_heatThreshold3 < g_globalHeat &&
                      g_heatThreshold4 < g_globalHeat)))
                {
                    uVar15 = 1;
                }
                else
                {
                    uVar15 = 0;
                }
            }
        }

        if (g_feature2Enabled == '\0')
            FUN_0052ea40(); // Update feature 2

        if (g_feature3Enabled == '\0')
            uVar10 = FUN_00527e20(); // Update feature 3

        if (g_feature4Enabled == '\0')
            uVar11 = FUN_00531280(); // Update feature 4

        if (g_feature5Enabled == '\0')
            uVar12 = FUN_00517970(); // Update feature 5

        if (g_feature6Enabled == '\0')
            uVar13 = FUN_0052a120(); // Update feature 6

        iVar14 = FUN_0052de20(cVar9, uVar15, uVar10, uVar11, uVar12, uVar13);
        // Access a table of 27-byte entries
        uVar1 = g_systemFlags[iVar14]; // g_systemFlags is array of DWORDs, index by iVar14

        // Evaluate per-system enable/disable based on flags and global overrides

        if ((g_feature5Enabled != '\0') || ((uVar1 >> 5 & 1) != 0))
            bVar5 = true;
        else
            bVar5 = false;

        if ((g_feature1Enabled != '\0') || ((uVar1 >> 2 & 1) != 0))
            bVar3 = true;
        else
            bVar3 = false;

        if ((g_feature3Enabled != '\0') || ((uVar1 >> 4 & 1) != 0))
            bVar6 = true;
        else
            bVar6 = false;

        if ((g_feature4Enabled != '\0') || ((uVar1 & 1) != 0))
            bVar7 = true;
        else
            bVar7 = false;

        if ((g_feature2Enabled == '\0') || ((uVar1 & 0xfffff8ff) != 0))
            bVar4 = false;
        else
            bVar4 = true;

        if ((uVar1 == 0) || (cVar8 == '\0'))
            bVar2 = false;
        else
            bVar2 = true;

        // Execute conditional updates
        if ((g_feature6Enabled == '\0') && ((uVar1 >> 1 & 1) == 0))
            FUN_0052a260(); // Disable feature 6 if not forced

        if ((!bVar2) && (g_timeScale != '\0'))
            FUN_0052b390(1.0f); // Reset time scale interpolation

        if ((uVar1 >> 5 & 1) != 0)
            FUN_00517b10(); // Update system 5

        if (g_feature1Enabled == '\0')
            FUN_00515a80(this, uVar1 >> 5 & 0xffffff01); // Process feature 1 with flags

        if (!bVar3)
            FUN_00515c20(); // Idle feature 1

        if (!bVar4)
            FUN_0052f250(this, uVar1, cVar8); // Update feature 2 with time scale

        if (!bVar5)
            FUN_00517de0(this); // Idle system 5

        if (!bVar6)
            FUN_00527e60(); // Idle system 3

        if (!bVar7)
            FUN_005312d0(); // Idle system 4

        if (g_feature7Enabled == '\0')
            FUN_0052b990(); // Update feature 7

        if (g_feature8Enabled == '\0')
        {
            FUN_005262b0(); // Finalise update
            return;
        }
    }
    else if ((updateState == 0) && (g_feature9Enabled == '\0'))
    {
        FUN_004e6e30(); // Reset/initialise state
        return;
    }
    return;
}