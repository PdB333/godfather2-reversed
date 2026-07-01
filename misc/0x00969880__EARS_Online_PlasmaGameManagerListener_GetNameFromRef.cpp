// Xbox PDB: EARS_Online_PlasmaGameManagerListener_GetNameFromRef
// FUNC_NAME: NetSession::buildGameSetupInfo
void __thiscall NetSession::buildGameSetupInfo(GameSetupInfo* outInfo)
{
    float fVar1;
    int iVar2, iVar3, iVar4, iVar9;
    char cVar5;
    int* piVar6;
    undefined4 uVar7;
    const char* pcVar8;
    char pcStack_10[0x30]; // buffer for player name (inferred)

    // Assume DAT_01223484 is the global NetSession singleton
    iVar4 = DAT_01223484; // NetSession* g_pNetSession
    // Get player manager (offset +0xC) and its iterator
    piVar6 = (int*)(**(code**)(**(int**)(iVar4 + 0xC) + 8))(); // PlayerManager::begin()
    uVar7 = (**(code**)(*piVar6 + 0xC))(); // iterator::getCurrent() -> Player*

    pcVar8 = "No Game Joined";
    if (*(int**)(iVar4 + 0xC) != nullptr) // if player manager exists
    {
        pcVar8 = "Could not find Player name";
        piVar6 = (int*)(**(code**)(**(int**)(iVar4 + 0xC) + 0x18))(uVar7); // PlayerManager::getLocalPlayer(uVar7)
        if (piVar6 != nullptr)
        {
            pcVar8 = (const char*)(**(code**)(*piVar6 + 4))(); // Player::getName()
        }
    }

    // Log the player name (debug print)
    FUN_004d3bc0(pcVar8); // presumably some logging function

    iVar3 = DAT_0112b9b4; // ProfileManager* g_pProfileManager
    this->m_bFlag1 = 1; // param_1+0x144
    iVar2 = *(int*)(iVar3 + 0x34); // ProfileManager::mActiveProfileIndex (or similar)
    iVar9 = 0;
    if (iVar2 == -1) // no active profile
    {
        this->m_bFlag1 = 0;
        cVar5 = FUN_0089c630(); // some environment check (e.g., demo mode?)
        if (cVar5 == '\0')
        {
            this->m_bFlag2 = 1; // param_1+500
            *(char*)(DAT_01129914 + 0xD3) = 1; // global flag set
            FUN_0095eb90(1); // enable something
        }
        this->m_bFlag3 = 1; // param_1+0x221
    }
    else
    {
        iVar9 = *(int*)(*(int*)(iVar3 + 0x28) + iVar2 * 4); // ProfileManager::getProfile(iVar2)
    }

    // Fallback string pointer
    const char* srcStr = pcStack_10;
    if (srcStr == nullptr)
    {
        srcStr = (const char*)DAT_0120546e; // default string (likely "Player")
    }

    // Copy player name into output struct (offset 8, size 0x30)
    _strncpy((char*)(outInfo + 8), srcStr, 0x30);
    *(char*)((int)outInfo + 0x4F) = '\0'; // null-terminate after string (probably at 0x38 + padding)

    if (iVar9 == 0) // no profile slot selected
    {
        if (this->m_bFlag2 == '\0')
        {
            outInfo->gameMode = 4; // *outInfo = 4
            outInfo->maxPlayers = 3; // outInfo[1] = 3
        }
        else
        {
            outInfo->gameMode = 2;
            outInfo->maxPlayers = 7;
        }
    }
    else // profile slot exists
    {
        outInfo->gameMode = *(undefined4*)(iVar9 + 0x2C); // Profile::mGameMode
        outInfo->maxPlayers = *(undefined4*)(iVar9 + 0x34); // Profile::mMaxPlayers
    }

    // Set difficulty level (outInfo[5])
    if (this->m_bFlag2 == '\0')
    {
        outInfo->difficulty = 4 - (uint)(*(int*)(iVar4 + 8) != 0); // NetSession::mLocalPlayerExists? (offset +8)
    }
    else if (*(int*)(iVar4 + 8) == 0)
    {
        cVar5 = FUN_0089c630(); // check again
        outInfo->difficulty = ((uint)(cVar5 != '\0') & 0xFFFFFFFE) + 4; // 4 if cVar5=0, 2 if cVar5!=0
    }
    else
    {
        outInfo->difficulty = 1;
    }

    // Set other fields
    uVar7 = DAT_00d5779c; // some global (maybe session ID)
    fVar1 = *(float*)(DAT_01129908 + 0x14); // global time or timer
    outInfo->missionIndex = 6; // outInfo[3] = 6
    outInfo->sessionId = uVar7; // outInfo[7] = uVar7
    outInfo->timeLimit = (int)(fVar1 + 0.5f); // rounding (outInfo[2])
    outInfo->someGlobal1 = *(undefined4*)(DAT_011307e8 + 0x60); // outInfo[6]
    *(char*)(outInfo + 0x16) = 1; // byte flag
    outInfo->roundNumber = 2; // outInfo[4] = 2

    // Get session ID again from PlayerManager (maybe different)
    piVar6 = (int*)(**(code**)(**(int**)(iVar4 + 0xC) + 8))(); // PlayerManager::begin()
    uVar7 = (**(code**)(*piVar6 + 0xC))(); // iterator::getCurrent() -> Player*
    outInfo->someSessionId2 = uVar7; // outInfo[0x17] = uVar7

    // Cleanup if temporary buffer was allocated
    if (pcStack_10 != nullptr)
    {
        // Simulated cleanup (DLL free or something)
        // (*pcStack_4)(pcStack_10);
    }
}