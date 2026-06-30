// FUNC_NAME: FamilyManager::processFamilyCrewDisplay
void FamilyManager::processFamilyCrewDisplay(void)
{
    int count = g_familyCount;                                // DAT_0119474c
    if ((g_displayDisabledFlag != '\0') ||                    // DAT_0120546f
        ((g_activeFamilyCount < 1 && (g_familyCount < 1))))   // DAT_01194750, DAT_0119474c
    {
        g_familyCount = 0;
        g_activeFamilyCount = 0;
        return;
    }

    // Enable debug rendering context
    enableDebugFrame(1);                                      // FUN_00412f50
    disableDebugFilter(0);                                    // FUN_00412f10

    int familyIdx = 0;
    if (0 < count)
    {
        do
        {
            // Clamp debug depth values
            if (g_debugRenderDepth < 0x1b)                   // DAT_012058d0
                g_debugRenderDepth = 0x1b;
            if (0x1a < g_altRenderDepth)                     // DAT_00f15988
                g_altRenderDepth = 0x1b;

            // Get head of entity list for this family
            int entity = g_familyEntityList[familyIdx * 2];  // DAT_01194758[familyIdx*2]
            g_debugShapeId = 1;                              // _DAT_011f3a44

            // Traverse entity linked list (next pointer at +0x20)
            for (; entity != 0; entity = *(int *)(entity + 0x20))
            {
                // Skip invalid or deactivated entities (type 0/4)
                if ((*(int *)(entity + 0x90) != 0) && (*(int *)(entity + 0x90) != 4))
                {
                    // Compute debug color from entity blend + global factor
                    float scale = *(float *)(entity + 0x3c) * g_globalColorFactor; // DAT_00e44584
                    g_debugDrawColor = 
                        ((uint)(char)(int)(*(float *)(entity + 0x30) * scale) & 0xff) |
                        (((uint)(char)(int)(*(float *)(entity + 0x34) * scale) & 0xff) << 8) |
                        (((uint)(char)(int)(*(float *)(entity + 0x38) * scale) & 0xff) << 16) |
                        (((uint)(char)(int)scale & 0xff) << 24); // _DAT_011f3cdc

                    // Clamp depth again
                    if (g_debugShapeDepth < 0xc1)            // DAT_012058d4
                        g_debugShapeDepth = 0xc1;
                    if (0xc0 < g_altShapeDepth)              // DAT_00f1598c
                        g_altShapeDepth = 0xc1;

                    // Determine icon type based on some entity flag
                    uint iconType = 2;
                    if (*(char *)(*(int *)(entity + 0x24) + 0x13) != '\0') // check flag at entity+0x24+0x13
                        iconType = 0xf;

                    // Draw icon at entity position
                    drawDebugShape(1, 0xe, iconType);        // FUN_00417cf0

                    // Set debug label type and draw text
                    if (g_debugRenderDepth < 0x17)
                        g_debugRenderDepth = 0x17;
                    if (0x17 < g_altRenderDepth)
                        g_altRenderDepth = 0x17;
                    g_debugLabelType = 3;                    // _DAT_011f3a34
                    drawDebugText(familyUpdateFunction, 0);  // FUN_0049f960 (call FUN_004e6e00)

                    // Reset label to default
                    if (g_debugRenderDepth < 0x17)
                        g_debugRenderDepth = 0x17;
                    if (0x17 < g_altRenderDepth)
                        g_altRenderDepth = 0x17;
                    g_debugLabelType = 4;                    // _DAT_011f3a34
                }
                count = g_familyCount;                       // re-read count (may have changed)
            }

            // End shape group for this family
            drawDebugShape(1, 5, 6);                         // FUN_00417cf0

            // Clamp depth again
            if (g_debugRenderDepth < 0x1b)
                g_debugRenderDepth = 0x1b;
            if (0x1a < g_altRenderDepth)
                g_altRenderDepth = 0x1b;

            familyIdx++;
            g_debugShapeId = 0;                              // _DAT_011f3a44
        } while (familyIdx < count);
    }

    // Clear temporary entity array (max 20 entries)
    uint idx = 0;
    do
    {
        if (g_tempEntityList[idx * 2] == 0)                 // DAT_01218e50
        {
            if (idx < 0x14)
                g_tempEntityFlags[idx * 2] &= 0xfffffffc;    // DAT_01218e54
            break;
        }
        idx++;
    } while (idx < 0x14);

    // Handle crew leader / main entity change notification
    int* crewLeaderList = g_crewLeaderList;                  // DAT_01205750
    int leaderChangeFlag = g_crewLeaderChangeFlag;           // DAT_011f38f4
    bool wasChange = g_crewLeaderActive != 0;                // DAT_011f38f0
    g_crewLeaderActive = 0;
    g_crewLeaderChangeFlag = 0;
    if (wasChange || leaderChangeFlag)
    {
        int vtable = *g_crewLeaderList;
        uint frameTime = getSystemTime();                    // FUN_00609260
        (*(void(__thiscall**)(int*, int, uint))(vtable + 0x94))(crewLeaderList, 0, frameTime);
        g_crewNotificationFlag = 1;                          // DAT_01223538
    }

    // Update camera/viewport for minimap
    uint viewA = g_minimapViewA;                             // DAT_011f3914
    uint viewB = g_minimapViewB;                             // DAT_011f3910
    g_minimapViewB = g_minimapWorldView;                     // DAT_01218e98
    g_minimapViewA = 0;
    setViewport(4, viewB, viewA);                            // FUN_00609340
    setProjection(4, 0, 0, 1.0f, 1.0f);                    // FUN_0060db60

    // Get camera position if player exists
    uint cameraPos = g_defaultCameraPos;                     // DAT_012058a8
    if (g_playerObject != 0)                                 // DAT_012054dc
        cameraPos = *(uint*)(g_playerObject + 0x170);        // Player camera offset

    byte activeFamiliesMask = 0;
    byte computedMask = 0;
    switch(g_activeFamilyCount)                              // DAT_01194750
    {
    case 4:
        activeFamiliesMask = 8;
    case 3:
        activeFamiliesMask |= 4;
    case 2:
        activeFamiliesMask |= 2;
    case 1:
        computedMask = activeFamiliesMask | 1;
    default:
        // Remove families with invalid condition (entity+0x3c <= threshold)
        for (int i = 0; i < g_activeFamilyCount; i++)
        {
            if (*(float*)(g_familyData[i*2] + 0x3c) <= g_invalidFamilyThreshold) // DAT_00e2e780
                computedMask &= ~(1 << (i & 0x1f));
        }
        if (computedMask != 0)
            renderFamilyCrew(cameraPos);                     // FUN_004e2970
        break;
    }

    // Setup debug state for crew drawing
    if (g_debugShapeDepth < 0xa8) g_debugShapeDepth = 0xa8;
    if (0xa7 < g_altShapeDepth) g_altShapeDepth = 0xa8;
    g_debugShapeParam = 0;                                   // _DAT_011f3c78

    g_debugShapeDepth = 0xbe;
    g_altShapeDepth = 0xbe;
    g_debugShapeParam2 = 0;                                  // _DAT_011f3cd0

    g_debugShapeDepth = 0xc3;
    g_altShapeDepth = 0xc3;
    g_debugShapeParam3 = 0;                                  // _DAT_011f3ce4

    g_debugShapeDepth = 0xaf;
    g_altShapeDepth = 0xaf;
    g_debugShapeParam4 = 0;                                  // _DAT_011f3c94

    g_debugLineCount = 0;                                    // DAT_012058d8
    g_debugPointCount = 0;                                   // DAT_012058dc

    if (g_debugRenderDepth < 0x34) g_debugRenderDepth = 0x34;
    if (0x34 < g_altRenderDepth) g_altRenderDepth = 0x34;
    g_debugFilter = 1;                                       // _DAT_011f3aa8

    setDebugDrawState(3, 1, 1);                              // FUN_0041e4d0

    // Process each family's crew members
    int famIdx = 0;
    if (0 < g_activeFamilyCount)
    {
        do
        {
            int entity = g_familyEntityData[famIdx * 2];     // DAT_01194760
            for (; entity != 0; entity = *(int*)(entity + 0x20))
            {
                if ((*(int*)(entity + 0x90) != 0) && (*(int*)(entity + 0x90) != 4))
                {
                    // Get crew array from entity's team (offset -4 if entity type !=0)
                    int teamPtr;
                    if (*(int*)(entity + 0x90) == 0)
                        teamPtr = 0;
                    else
                        teamPtr = *(int*)(entity + 0x90) - 4;

                    int* crewMembers = *(int**)(teamPtr + 0x8c); // array of crew member pointers
                    int crewCount = *(int*)(teamPtr + 0x90);
                    int* crewEnd = crewMembers + crewCount;

                    // Accumulate bitmask from all crew members' flags
                    byte crewFlagMask = 0;
                    for (int* member = crewMembers; member < crewEnd; member++)
                    {
                        if ((*(byte*)(*member + 0xb2) & 1) != 0)
                        {
                            crewFlagMask |= *(byte*)(*(int*)(*member + 0xa0) + 0x2c);
                        }
                    }

                    // If any crew member has flags matching active families, draw debug markers
                    if ((crewFlagMask & computedMask) != 0)
                    {
                        g_debugRenderDepth = 0x38;
                        g_altRenderDepth = 0x38;
                        g_debugShapeType = 8;                // _DAT_011f3ab8

                        g_debugRenderDepth = 0x39;
                        g_altRenderDepth = 0x39;
                        g_debugShapeBits = (uint)(crewFlagMask & computedMask); // _DAT_011f3abc

                        g_debugRenderDepth = 0x3a;
                        g_altRenderDepth = 0x3a;
                        g_debugShapeExtra = g_debugShapeBits; // _DAT_011f3ac0

                        // Draw connections for each flagged crew member
                        for (int* member = crewMembers; member < crewEnd; member++)
                        {
                            int m = *member;
                            if ((*(byte*)(m + 0xb2) & 1) != 0)
                            {
                                drawLineOrIcon(*(uint*)(m + 0xa0),
                                               m + 0x10,         // position offset
                                               2,
                                               0xffffffff,
                                               5,
                                               0);               // FUN_00433700
                            }
                        }
                    }

                    // Recalculate crewFlagMask to update crew member's flag
                    crewFlagMask = 0;
                    for (int* member = crewMembers; member < crewEnd; member++)
                    {
                        if ((*(byte*)(*member + 0xb2) & 1) != 0)
                            crewFlagMask |= *(byte*)(*(int*)(*member + 0xa0) + 0x2c);
                    }

                    // Clear the bits that correspond to previously active families
                    for (int* member = crewMembers; member < crewEnd; member++)
                    {
                        if ((*(byte*)(*member + 0xb2) & 1) != 0)
                        {
                            *(byte*)(*(int*)(*member + 0xa0) + 0x2c) = 
                                (byte)(~activeFamiliesMask & crewFlagMask);
                        }
                    }
                }
            }
            famIdx++;
        } while (famIdx < g_activeFamilyCount);
    }

    // Reset debug state after crew drawing
    g_debugRenderDepth = 0x38;
    g_altRenderDepth = 0x38;
    g_debugShapeType = 8;
    g_debugRenderDepth = 0x39;
    g_altRenderDepth = 0x39;
    g_debugShapeBits = 0;
    g_debugRenderDepth = 0x3a;
    g_altRenderDepth = 0x3a;
    g_debugShapeExtra = 0xffffffff;
    g_debugRenderDepth = 0x34;
    g_altRenderDepth = 0x34;
    g_debugFilter = 0;
    setDebugDrawState(1, 1, 1);                              // FUN_0041e4d0

    g_debugRenderDepth = 0x19;
    g_altRenderDepth = 0x19;
    g_debugLabelType = 7;                                    // _DAT_011f3a3c

    g_debugRenderDepth = 0x18;
    g_altRenderDepth = 0x18;
    g_debugLabelSubType = 0;                                 // _DAT_011f3a38

    g_debugRenderDepth = 0xf;
    g_altRenderDepth = 0xf;
    g_debugIconType = 0;                                     // _DAT_011f3a14

    g_debugShapeDepth = 0xa8;
    g_altShapeDepth = 0xa8;
    g_debugShapeParam = 0xf;                                 // _DAT_011f3c78

    g_debugShapeDepth = 0xbe;
    g_altShapeDepth = 0xbe;
    g_debugShapeParam2 = 0xf;                                // _DAT_011f3cd0

    g_debugShapeDepth = 0xc3;
    g_altShapeDepth = 0xc3;
    g_debugShapeParam3 = 0;                                  // _DAT_011f3ce4

    g_debugShapeDepth = 0xaf;
    g_altShapeDepth = 0xaf;
    g_debugShapeParam4 = 0;                                  // _DAT_011f3c94

    g_debugLineCount = 0;
    g_debugPointCount = 0;

    g_debugRenderDepth = 0xe;
    g_altRenderDepth = 0xe;
    g_debugFilter2 = 1;                                      // _DAT_011f3a10

    g_debugRenderDepth = 7;
    g_altRenderDepth = 7;
    g_debugFilter3 = 1;                                      // _DAT_011f39f4

    // Build minimap marker data for each family
    if (0 < g_activeFamilyCount)
    {
        MinimapMarker markerArray[35];                        // stack array (size assumed)
        int markerIdx = 0;
        do
        {
            int entity = g_familyEntityData[markerIdx * 2];
            byte typeFlag = *(byte*)(g_familyEntityDataAlt[markerIdx * 2] + 0x13); // DAT_0119475c
            uint markerData[8];                               // local block for marker parameters
            markerData[0] = *(uint*)(entity + 0x30);          // position x
            markerData[1] = *(uint*)(entity + 0x34);          // position y
            markerData[2] = *(uint*)(entity + 0x38);          // position z
            markerData[3] = *(uint*)(entity + 0x3c);          // w
            markerData[4] = *(uint*)(entity + 0x84);          // some flag
            markerData[5] = (uint)typeFlag;                    // icon type from sibling

            uint otherFlags = *(uint*)(g_familyEntityDataAlt[markerIdx * 2] + 0x14);
            if ((otherFlags & 0x400) == 0)
                markerData[6] = (otherFlags >> 7) & 1;
            else
                markerData[6] = 2;

            // Send to minimap/audio system
            sendMinimapMarkerData();                          // FUN_00528100
            addMinimapMarker(&markerData[0]);                 // FUN_005286d0

            markerIdx++;
        } while (markerIdx < g_activeFamilyCount);
    }

    // Finalize family crew display update
    finalizeCrewDisplay();                                   // FUN_004e3a70
    g_activeFamilyCount = 0;                                 // DAT_01194750
    g_familyCount = 0;                                       // DAT_0119474c
}