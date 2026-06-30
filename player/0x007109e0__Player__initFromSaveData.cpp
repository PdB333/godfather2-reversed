// FUNC_NAME: Player::initFromSaveData

void __thiscall Player::initFromSaveData(PlayerSaveData* pSaveData)
{
    uint32_t* puFlags;
    int* piListNext;
    
    // Call base class initialization
    baseInit();
    
    // Allocate setup data structure (size 0xB8)
    PlayerSetupData* pSetupData = reinterpret_cast<PlayerSetupData*>(allocateMemory(0xB8));
    if (pSetupData != nullptr) {
        pSetupData = new (pSetupData) PlayerSetupData(); // Call constructor via FUN_00710850
    }
    this->m_pSetupData = pSetupData; // +0x128
    
    // Copy position/rotation data from save (four consecutive quaternion/vector components)
    pSetupData->vRotation[0] = *(float*)(pSaveData + 0x1FC0); // +0x00
    pSetupData->vRotation[1] = *(float*)(pSaveData + 0x1FC8); // +0x04
    pSetupData->vRotation[2] = *(float*)(pSaveData + 0x1FD0); // +0x08
    pSetupData->vRotation[3] = *(float*)(pSaveData + 0x1FD8); // +0x0C
    pSetupData->vPosition[0] = *(float*)(pSaveData + 0x1FE0); // +0x10
    pSetupData->vPosition[1] = *(float*)(pSaveData + 0x1FF8); // +0x14
    pSetupData->vPosition[2] = *(float*)(pSaveData + 0x20D0); // +0x18
    pSetupData->vPosition[3] = *(float*)(pSaveData + 0x20D8); // +0x1C
    pSetupData->vAppearance[0] = *(float*)(pSaveData + 0x20E0); // +0x20
    pSetupData->vAppearance[1] = *(float*)(pSaveData + 0x20E8); // +0x24
    pSetupData->vAppearance[2] = *(float*)(pSaveData + 0x20F0); // +0x28
    pSetupData->vAppearance[3] = *(float*)(pSaveData + 0x20F8); // +0x2C
    
    // Copy family/gang color data from global singleton (e.g., FamilyManager)
    FamilyManager* pFamilyManager = (FamilyManager*)getSingleton(DAT_01131018); // FUN_0043b870
    pSetupData->familyColor[0] = *(uint32_t*)(pFamilyManager + 0x54); // +0x30
    pSetupData->familyColor[1] = *(uint32_t*)(pFamilyManager + 0x5C); // +0x34
    
    // Copy more appearance/skin tone data from save
    pSetupData->skinTone[0] = *(float*)(pSaveData + 0x1CC0); // +0x38
    pSetupData->skinTone[1] = *(float*)(pSaveData + 0x1CC8); // +0x3C
    pSetupData->skinTone[2] = *(float*)(pSaveData + 0x1CD0); // +0x40
    
    // Copy outfit/accessory data from another global singleton
    // (likely CrewComponent or FamilyMemberData)
    CrewComponent* pCrew = (CrewComponent*)getSingleton(DAT_0112A9FC);
    pSetupData->outfitData[0] = *(int*)(pCrew + 0x14); // +0x44
    pSetupData->outfitData[1] = *(int*)(pCrew + 0x18); // +0x48
    pSetupData->outfitData[2] = *(int*)(pCrew + 0x1C); // +0x4C
    pSetupData->outfitData[3] = *(int*)(pCrew + 0x20); // +0x50
    pSetupData->accessoryData[0] = *(int*)(pCrew + 0x48); // +0x54
    pSetupData->accessoryData[1] = *(int*)(pCrew + 0x4C); // +0x58
    pSetupData->accessoryData[2] = *(int*)(pCrew + 0x50); // +0x5C
    pSetupData->accessoryData[3] = *(int*)(pCrew + 0x54); // +0x60
    pSetupData->weaponData[0] = *(int*)(pCrew + 0x7C); // +0x64 (100 decimal)
    pSetupData->weaponData[1] = *(int*)(pCrew + 0x80); // +0x68
    pSetupData->weaponData[2] = *(int*)(pCrew + 0x84); // +0x6C
    pSetupData->weaponData[3] = *(int*)(pCrew + 0x88); // +0x70
    pSetupData->vehicleData[0] = *(int*)(pCrew + 0xB0); // +0x74
    pSetupData->vehicleData[1] = *(int*)(pCrew + 0xB4); // +0x78
    pSetupData->vehicleData[2] = *(int*)(pCrew + 0xB8); // +0x7C
    pSetupData->vehicleData[3] = *(int*)(pCrew + 0xBC); // +0x80
    
    // Set flags based on save data
    uint32_t flags = 0;
    puFlags = &pSetupData->flags; // +0x98
    *puFlags = 0;
    
    // Check bit at save+0x1F57 (mask 0x01) for "isMale"
    if ((*(uint8_t*)(pSaveData + 0x1F57) & 1) == 0) {
        *puFlags |= 4; // Female flag
    } else {
        *puFlags |= 1; // Male flag
    }
    
    // Check bit at save+0x1F54 (bit 25) for some other option (e.g., isNPC or isPlayer)
    if ((*(uint32_t*)(pSaveData + 0x1F54) >> 25 & 1) == 0) {
        *puFlags |= 8;
    } else {
        *puFlags |= 2;
    }
    
    // Set name string (with default if empty)
    const char* szName = *(const char**)(pSaveData + 0x203C);
    if (szName == nullptr) {
        szName = "DefaultName"; // DAT_0120546e
    }
    setName(szName); // FUN_004d3d90
    
    // Copy some ID or level from save
    pSetupData->someID = *(int*)(pSaveData + 0x1F98); // +0x94
    
    // Determine gang affiliation based on player state or save flags
    if (*(int*)(this + 0x11C) == 3) {
        // player is in a specific state? Maybe "DonControl"
        pSetupData->gangAffiliation = 3; // +0xAC
    } else if ((*(uint32_t*)(pSaveData + 0x1F5C) >> 9 & 1) == 0) {
        if ((*(uint32_t*)(pSaveData + 0x1F5C) >> 10 & 1) == 0) {
            pSetupData->gangAffiliation = 0; // Neutral
        } else {
            pSetupData->gangAffiliation = 2; // Corleone?
        }
    } else {
        pSetupData->gangAffiliation = 1; // Other family
    }
    
    // Insert this setup data into a linked list owned by the save or player
    // Structure: pSetupData has m_pListNext at +0xB0 and m_pListPrev at +0xB4
    // The save object has a list head at +0x4C and node field at +0x48
    piListNext = &pSetupData->m_pListNext; // +0xB0
    int* pListNodeInSave = (int*)(pSaveData + 0x48);
    if (*piListNext != pListNodeInSave) {
        if (*piListNext != 0) {
            removeFromList(pSetupData); // FUN_004daf90 (removes from current list)
        }
        *piListNext = (int)pListNodeInSave;
        pSetupData->m_pListPrev = *(int**)(pSaveData + 0x4C); // back pointer
        *(int**)(pSaveData + 0x4C) = piListNext; // update list head
    }
}