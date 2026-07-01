// FUNC_NAME: Player::updateCameraMode
void __fastcall Player::updateCameraMode(Player* this)
{
    // Global state pointer at 0x01129944 (likely CameraManager singleton)
    CameraManager* cameraMgr = *DAT_01129944;
    uint aimTarget = 0; // potentially a target entity ID
    uint flags0x8e0 = *(uint*)(this + 0x8e0);
    uint flags0x8e4 = *(uint*)(this + 0x8e4);
    uint flags0x8e8 = *(uint*)(this + 0x8e8);
    uint flags0x249c = *(uint*)(this + 0x249c);
    int vehicleOrCover = *(int*)(this + 0x24b4); // +0x24b4 might be Vehicle* or CoverHintNode*; 0x48 = something like "in cover" ID?
    int secondaryRef = *(int*)(this + 0x31a8); // +0x31a8 maybe another entity ref
    int tertiaryRef = *(int*)(this + 0x30c0); // +0x30c0 another ref

    bool isAiming = (flags0x8e4 >> 7) & 1;
    bool isInVehicle = (flags0x8e0 >> 10) & 1;
    bool isInCover = (flags0x8e0 >> 9) & 1;
    bool isDoingQuickAction = (flags0x8e8 >> 2) & 1;
    bool isInStare = (flags0x249c >> 0x17) & 1; // bit 23

    // Determine aim target
    if (!isAiming)
    {
        if (!isInVehicle)
            aimTarget = 0; // no target
        else
            aimTarget = getCurrentVehicleTarget(); // FUN_00800a90
    }
    else
    {
        // When aiming, check if vehicle/cover pointer is null or sentinel (0, 0x48)
        if (vehicleOrCover == 0 || vehicleOrCover == 0x48)
        {
            aimTarget = 0;
        }
        else
        {
            // The pointer at +0x24b4 points to some object; we derive a vtable pointer
            int* vtablePtr = (int*)(vehicleOrCover - 0x48); // subtract offset to get base
            uint local_4 = 0;
            char result = ((int (__thiscall*)(int*, uint*))(*vtablePtr)[4])(vtablePtr, &local_4); // vtable[4] (index 4) is likely getTargetId
            if (result == 0)
                aimTarget = 0;
            else
                aimTarget = local_4;
        }
    }

    int isInCombat = isPlayerInCombat(); // FUN_00800b10
    char cutsceneActive = isCutscenePlaying(); // FUN_00842870
    if (cutsceneActive == 0)
    {
        char dead = isPlayerDead(); // FUN_007f7c60
        if (dead == 0 &&
            !((flags0x8e4 >> 0x10) & 1) && // bit 16? maybe player is falling?
            (int)flags0x8e4 >= 0 && // what? possibly sign check
            !((flags0x8e4 >> 0x1e) & 1)) // bit 30? maybe stunned
        {
            char menuOpen = isMenuOpen(); // FUN_007f7c50
            if (menuOpen == 0)
            {
                char isInTutorial = isTutorialActive(0x18); // FUN_00690210
                if (isInTutorial == 0)
                {
                    char isInDialogue = isDialogueActive(0x18); // FUN_00690150
                    if (isInDialogue != 0)
                    {
                        // Check another dialogue flag (0x19) - maybe for sub-mode
                        char isInSubDialogue = isDialogueActive(0x19); // FUN_00690150
                        if (isInSubDialogue == 0)
                            goto LAB_DISABLE_CAMERA;
                    }
                    if (globalPlayerControlledFlag == 0) // DAT_0112a863
                    {
                        char multiplayerBlock = isMultiplayerBlock(); // FUN_007fd720
                        if (multiplayerBlock == 0)
                        {
                            char isInRestrictedArea = isRestrictedArea(0x4d); // FUN_00690210
                            if (isInRestrictedArea == 0)
                            {
                                bool useAimCamera = false;
                                bool useCoverCamera = false;

                                // Determine camera mode based on flags
                                // Aim camera conditions
                                if (isInCover && tertiaryRef != 0 && tertiaryRef != 0x48)
                                {
                                    // If in cover and have a valid cover pointer (not null/0x48)
                                    useAimCamera = true;
                                }

                                // Cover camera conditions
                                if ((isDoingQuickAction) ||
                                    (isInVehicle && (tertiaryRef == 0 || tertiaryRef == 0x48) && isInCombat == 0) ||
                                    (isInStare && (secondaryRef != 0 && secondaryRef != 0x48)))
                                {
                                    useCoverCamera = true;
                                }

                                if (useAimCamera)
                                {
                                    // Update aim camera with target
                                    updateAimingCamera(aimTarget); // FUN_0081e970
                                    if (aimTarget != 0)
                                    {
                                        float distance = calculateDistanceToTarget(); // FUN_00702e10
                                        cameraMgr->cameraDistance = distance; // *(float*)(cameraMgr + 0x18)
                                    }
                                    return;
                                }
                                if (useCoverCamera)
                                {
                                    updateCoverCamera(aimTarget); // FUN_0081ebb0
                                    float defaultZoom = defaultCameraZoom; // DAT_00d5780c
                                    // Override zoom if in stare mode
                                    if (isInStare && aimTarget != 0)
                                    {
                                        float stareZoom = calculateStareDistance(); // FUN_007022c0
                                        defaultZoom = stareZoom;
                                    }
                                    cameraMgr->cameraDistance = defaultZoom;
                                    return;
                                }
                                updateDefaultCamera(); // FUN_0081e850
                                return;
                            }
                        }
                    }
                }
            }
        }
    }
LAB_DISABLE_CAMERA:
    disableCameraUpdate(); // FUN_0081dce0
}