// FUNC_NAME: PlayerAlertManager::updateAlertSound
void __thiscall PlayerAlertManager::updateAlertSound(PlayerAlertManager* this, Entity* entity, bool bForcePlay)
{
    char cVar1;
    byte bVar2;
    int iManager;
    int iSoundManager;
    int iTemp1;
    int iTemp2;
    undefined4 uVar4;
    byte bVar5;
    int iEntity;
    int iEntityBase;
    undefined4 uVar8;
    undefined4 local_34;
    undefined ***local_30;
    undefined1 local_2c;
    undefined **local_24;
    int local_20;
    int local_1c[2];
    undefined8 local_14;
    undefined4 local_c;
    undefined1 local_8;
    undefined4 local_4;

    iEntity = entity; // Save original entity pointer
    // Resolve game manager from global singleton
    if (entity == 0) {
        entity = 0;
    }
    else {
        entity = GameManager::getInstance(DAT_01131040); // DAT_01131040 likely g_pGameManager
    }
    // Check if entity status component exists at offset 0x30
    if (*(int*)(entity + 0x30) == 0) {
        iTemp1 = 0;
    }
    else {
        iTemp1 = *(int*)(entity + 0x30) - 0x48; // Adjust to get base object? (vtable offset)
    }
    iSoundManager = 0;
    cVar1 = IsGameActive(); // FUN_009b11f0 - likely checks if game is not paused/menu
    if ((cVar1 != 0) && (iTemp1 != 0)) {
        iSoundManager = AudioManager::getInstance(DAT_0112af98); // DAT_0112af98 likely g_pAudioManager
    }
    // Check flag at entity+0x48 bit 1 and if sound manager exists and has a valid sound channel at +0xa4
    if ((((*(uint*)(entity + 0x48) >> 1 & 1) != 0) && (iSoundManager != 0)) && (*(int*)(iSoundManager + 0xa4) != 0)) {
        // Prepare a callback structure (TimerEvent or similar)
        local_c = 0;
        local_14 = 0;
        local_24 = &PTR_FUN_00d5dbbc; // Function pointer for callback
        local_1c[0] = 0;
        local_1c[1] = 0;
        local_8 = 0;
        local_4 = DAT_01205228; // Some data
        local_20 = *(int*)(iSoundManager + 0xa4); // Sound channel handle

        // Get some data from entity (maybe position or ID)
        Entity::getSomeData(iEntity); // FUN_0044b210 - unknown
        // Get current game time
        iTemp1 = GameTimer::getCurrent(); // FUN_00471610
        local_8 = 1;
        local_14 = *(undefined8*)(iTemp1 + 0x30);
        local_c = *(undefined4*)(iTemp1 + 0x38);
        // Set up event scheduling parameters
        local_30 = &local_24;
        local_34 = DAT_0112ad8c; // Some event ID
        local_2c = 0;
        if (this == 0) {
            this = 0;
        }
        else {
            this = this + 0x3c; // Use timer at offset 0x3c
        }
        // Schedule an event/timer
        EventManager::scheduleEvent(&local_34, this, 0); // FUN_00408bf0
        // Cleanup if schedule event allocated something
        if (local_1c[0] != 0) {
            MemoryDealloc(local_1c); // FUN_004daf90
        }
    }
    // If force play flag is set, evaluate whether to play the alert sound
    if (bForcePlay != 0) {
        iTemp1 = **(int**)(DAT_012233a0 + 4); // Global player data
        if ((iTemp1 == 0) || (iTemp1 == 0x1f30)) {
            bVar5 = 0;
            bVar2 = 0;
        }
        else {
            bVar5 = (byte)((uint)*(undefined4*)(iTemp1 + 0x574) >> 8) & 1; // Check some flag
            bVar2 = *(byte*)(iTemp1 + -0x164a) & 1; // Another flag
        }
        if (bVar2 == 0 && bVar5 == 0) {
            cVar1 = IsGameActive(); // FUN_009b11f0
            if (cVar1 == 0) {
                // Game not active (paused/in menu)
                if ((*(byte*)(entity + 0x44) & 0x40) == 0) {
                    return;
                }
                // Check if entity has a specific flag at offset 0x8e0 bit 18
                if ((*(uint*)(iEntity + 0x8e0) >> 0x12 & 1) == 0) {
                    cVar1 = InputManager::isButtonDown(0x13); // FUN_00690150
                    if (cVar1 == 0) {
                        return;
                    }
                    iEntity = -0xf5c28b5; // Some negative value for pitch?
                }
                else {
                    iEntity = 0x35bdf06d; // Some positive value
                }
            }
            else {
                // Game is active
                if (iSoundManager == 0) {
                    return;
                }
                iEntity = *(int*)(iSoundManager + 0x4c); // Get some audio handle
                if (iEntity == 0) {
                    return;
                }
            }
            // Play the alert sound with parameters
            uVar8 = 0;
            uVar4 = AudioManager::beginSoundEvent(0, 0); // FUN_006fbc40
            AudioManager::playSoundEvent(iEntity, 0x75, uVar4, uVar8); // FUN_007f96a0 (opcode 0x75 = alert sound?)
            AudioManager::endSoundEvent(); // FUN_006fbc70
        }
    }
    return;
}