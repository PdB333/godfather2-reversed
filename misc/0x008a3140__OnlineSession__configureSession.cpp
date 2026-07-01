//FUNC_NAME: OnlineSession::configureSession
// Address: 0x008a3140
// Role: Configures multiplayer session parameters based on flags, version, and network state.
// This function sets up mode request, match type, NAT strictness, version check, and Don mode flow.

int OnlineSession::configureSession(uint flags, undefined4 unused, char* versionString)
{
    char cVar1;
    bool bVar2;
    char* pcVar3;
    int* piVar4;
    int* piVar5;
    int* piVar6;
    uint uVar7;
    code* pcVar8;
    char unaff_retaddr;
    undefined* puVar9;
    undefined4 uStack_4;

    // Skip over a string constant (likely "PlayNowOptionsVersion___1_Sessio...")
    pcVar3 = PTR_s_PlayNowOptionsVersion___1_Sessio_00e543f0;
    do {
        cVar1 = *pcVar3;
        pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');

    // Get the session manager singleton
    piVar4 = (int*)getSessionManager(); // FUN_00b596e0
    if (piVar4 == (int*)0x0) {
        return 0;
    }

    // Get the ModeRequest object from the session manager (vtable+0x38 = getObjectByName)
    piVar5 = (int*)(**(code**)(*piVar4 + 0x38))("ModeRequest");
    if (piVar5 != (int*)0x0) {
        switch(flags) {
        case 0:
            // Clear all mode flags
            (**(code**)(*piVar5 + 0xc))(&DAT_00e36d94); // s_ModeNone
            (**(code**)(*piVar5 + 0xc))(&DAT_00d796d4); // s_ModeFreeRoam
            (**(code**)(*piVar5 + 0xc))(&DAT_00d796d0); // s_ModeStory
            // Fall through to case 4
        case 4:
            puVar9 = &DAT_00d796cc; // s_ModeDon
            break;
        case 1:
            puVar9 = &DAT_00e36d94; // s_ModeNone
            break;
        case 2:
            puVar9 = &DAT_00d796d4; // s_ModeFreeRoam
            break;
        case 3:
            puVar9 = &DAT_00d796d0; // s_ModeStory
            break;
        default:
            // Clear flags based on bits
            (**(code**)(*piVar5 + 0xc))(&DAT_00e36d94);
            if ((flags & 0x10) != 0) {
                (**(code**)(*piVar5 + 0xc))(&DAT_00d796d4);
            }
            if ((flags & 0x20) != 0) {
                (**(code**)(*piVar5 + 0xc))(&DAT_00d796d0);
            }
            if ((flags & 0x40) != 0) {
                puVar9 = &DAT_00d796cc; // s_ModeDon
            } else {
                goto LAB_008a3221;
            }
            break;
        }
        // Set the mode on the ModeRequest object (vtable+0xc = setMode)
        (**(code**)(*piVar5 + 0xc))(puVar9);
    }

LAB_008a3221:
    // Get MatchType object
    piVar5 = (int*)(**(code**)(*piVar4 + 0x68))("MatchType");
    if (piVar5 != (int*)0x0) {
        // Set match type (vtable+0x10 = setValue)
        (**(code**)(*piVar5 + 0x10))(uStack_4); // Note: uStack_4 is uninitialized, likely a bug or decompiler artifact
    }

    // Handle HostIsStrictNAT
    piVar5 = (int*)(**(code**)(*piVar4 + 0x68))("HostIsStrictNAT");
    if (unaff_retaddr == '\0') {
        if (piVar5 == (int*)0x0) goto LAB_008a32a3;
        pcVar8 = *(code**)(*piVar4 + 0x6c); // vtable+0x6c = setBool
        pcVar3 = "HostIsStrictNAT";
    } else {
        // Check network manager for player count
        bVar2 = true;
        piVar6 = (int*)getNetworkManager(); // FUN_00ad8d40
        if ((piVar6 != (int*)0x0) &&
            (piVar6 = (int*)(**(code**)(*piVar6 + 0x30))(), piVar6 != (int*)0x0)) {
            uVar7 = (**(code**)(*piVar6 + 0x50))(); // getPlayerCount or similar
            bVar2 = 2 < uVar7;
        }
        if (piVar5 == (int*)0x0) goto LAB_008a32a3;
        pcVar8 = *(code**)(*piVar5 + 0x10); // vtable+0x10 = setValue
        pcVar3 = (char*)-(uint)bVar2; // Convert bool to int
    }
    (*pcVar8)(pcVar3);

LAB_008a32a3:
    // Handle version check if version string provided
    if (versionString != 0) {
        piVar5 = (int*)(**(code**)(*piVar4 + 0x4c))
                          ("VersionCheck", 10000, &stack0xffffffdc, 2, &stack0xffffffe4, 4, "Version",
                           0, 1);
        // Set version string on the VersionCheck object (vtable+0xc = setString)
        (**(code**)(*piVar5 + 0xc))(versionString);
    }

    // Handle Don mode game and flow request
    piVar5 = (int*)(**(code**)(*piVar4 + 0x68))("DonModeGame");
    if (piVar5 != (int*)0x0) {
        if (unaff_retaddr == '\0') {
            // Set DonModeGame to true via session manager
            (**(code**)(*piVar4 + 0x6c))("DonModeGame");
            pcVar8 = *(code**)(*piVar4 + 0x6c);
            pcVar3 = "DonFlowReq";
        } else {
            // Set DonModeGame value directly
            (**(code**)(*piVar5 + 0x10))(unaff_retaddr);
            piVar5 = (int*)(**(code**)(*piVar4 + 0x68))("DonFlowReq");
            pcVar8 = *(code**)(*piVar5 + 0x10);
            pcVar3 = (char*)0x1; // true
        }
        (*pcVar8)(pcVar3);
    }

    // Finalize: get network manager and set session manager
    piVar5 = (int*)getNetworkManager(); // FUN_00ad8d40
    if ((piVar5 != (int*)0x0) &&
        (piVar5 = (int*)(**(code**)(*piVar5 + 0x30))(), piVar5 != (int*)0x0)) {
        // Call method on network manager with session manager (vtable+0x54 = setSessionManager)
        (**(code**)(*piVar5 + 0x54))(piVar4);
        return 1;
    }
    return 0;
}