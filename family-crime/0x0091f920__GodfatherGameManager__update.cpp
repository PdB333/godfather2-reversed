// FUNC_NAME: GodfatherGameManager::update
int* __fastcall GodfatherGameManager::update(int* thisPtr)
{
    // Call various subsystem update functions
    updateAISystem();           // 0x0093d190
    updateAnimationSystem();    // 0x009457a0
    updateBuildingSystem();     // 0x00928e70
    updateCameraSystem();       // 0x00985e60
    updateChaseManager();       // 0x0097a010
    updateCombatSystem();       // 0x00929cc0
    updateControllerManager();  // 0x00980340
    updateCrimeManager();       // 0x00959cc0
    updateDialogTreeManager();  // 0x00911960
    updateDonControlManager();  // 0x00920eb0
    updateEntityManager();      // 0x009844b0
    updateEventScheduler();     // 0x00926680
    updateFamilyManager();      // 0x009380b0
    updateGameplayDebugger();   // 0x0095ab10
    updateHitMission();         // 0x00951290
    updateInputDeviceManager(); // 0x0092a610
    updateInventoryManager();   // 0x00992e00
    updateJobReward();          // 0x00991bf0
    updateLuaSystem();          // 0x0092cf20
    updateMobFaceManager();     // 0x0094e700
    updateMonopoly();           // 0x00962540
    updateMultiplayerScenario();// 0x00930250
    updateNPCManager();         // 0x00957d40
    updateNavigation();         // 0x00912fb0
    updateNetSession();         // 0x00915e90
    updatePlayerManager();      // 0x00950170
    updatePresentation();       // 0x00926540
    updateRagdollComponent();   // 0x00938820
    updateSimManager(0);        // 0x00983570 with arg 0
    updateStreamManager();      // 0x0090fb40
    updateTargetingManager();   // 0x009548d0
    updateTeamScenario();       // 0x00974740
    updateThrowableItem();      // 0x00922d90
    updateTopDonChallenge();    // 0x0090dd30
    updateTrafficManager();     // 0x0093f9e0
    updateVehicleBrain();       // 0x0094efd0
    updateVehicleDamage();      // 0x0094b460
    updateViolenceTracking();   // 0x00938b30
    updateVFX();                // 0x00954740
    updateWhiteboxCar();        // 0x0097bec0
    updateUIHudMinimap();       // 0x00993df0
    updateAudioDataManager();   // 0x0093ddb0
    updateBNKStreamManager();   // 0x0094f660

    // Call virtual update functions on sub-objects (vtable offset +100 = 0x64)
    // These are likely pointers to sub-systems stored at various offsets in thisPtr
    (*(void (__thiscall**)(int*))(*(int*)thisPtr + 100))(thisPtr); // +0x00 vtable
    (*(void (__thiscall**)(int*))(thisPtr[0x60] + 100))(thisPtr[0x60]); // +0x180
    (*(void (__thiscall**)(int*))(thisPtr[0xa3] + 100))(thisPtr[0xa3]); // +0x28c
    (*(void (__thiscall**)(int*))(thisPtr[0x4dd] + 100))(thisPtr[0x4dd]); // +0x1374
    (*(void (__thiscall**)(int*))(thisPtr[0x521] + 100))(thisPtr[0x521]); // +0x1484
    (*(void (__thiscall**)(int*))(thisPtr[0xc3] + 100))(thisPtr[0xc3]); // +0x30c
    (*(void (__thiscall**)(int*))(thisPtr[0xe0] + 100))(thisPtr[0xe0]); // +0x380
    (*(void (__thiscall**)(int*))(thisPtr[0x154] + 100))(thisPtr[0x154]); // +0x550
    (*(void (__thiscall**)(int*))(thisPtr[0x16d] + 100))(thisPtr[0x16d]); // +0x5b4
    (*(void (__thiscall**)(int*))(thisPtr[0x1bb] + 100))(thisPtr[0x1bb]); // +0x6ec
    (*(void (__thiscall**)(int*))(thisPtr[0x26d] + 100))(thisPtr[0x26d]); // +0x9b4
    (*(void (__thiscall**)(int*))(thisPtr[0x32c] + 100))(thisPtr[0x32c]); // +0xcb0
    (*(void (__thiscall**)(int*))(thisPtr[0x358] + 100))(thisPtr[0x358]); // +0xd60
    (*(void (__thiscall**)(int*))(thisPtr[0x39b] + 100))(thisPtr[0x39b]); // +0xe6c
    (*(void (__thiscall**)(int*))(thisPtr[0x3b0] + 100))(thisPtr[0x3b0]); // +0xec0
    (*(void (__thiscall**)(int*))(thisPtr[0x3cc] + 100))(thisPtr[0x3cc]); // +0xf30
    (*(void (__thiscall**)(int*))(thisPtr[0x3fe] + 100))(thisPtr[0x3fe]); // +0xff8

    // Additional subsystem updates
    updateCrewLeaderComponent(); // 0x0092a190
    updatePlayerCrewLeader();    // 0x00992b40
    updatePlayerReputation();    // 0x009909b0

    // More virtual calls
    (*(void (__thiscall**)(int*))(thisPtr[0x47b] + 100))(thisPtr[0x47b]); // +0x11ec
    (*(void (__thiscall**)(int*))(thisPtr[0x57e] + 100))(thisPtr[0x57e]); // +0x15f8
    (*(void (__thiscall**)(int*))(thisPtr[0x59f] + 100))(thisPtr[0x59f]); // +0x167c
    (*(void (__thiscall**)(int*))(thisPtr[0x5bf] + 100))(thisPtr[0x5bf]); // +0x16fc

    // Common utility call (likely process pending events)
    processPendingEvents(); // 0x005c1740

    (*(void (__thiscall**)(int*))(thisPtr[0x5db] + 100))(thisPtr[0x5db]); // +0x176c
    (*(void (__thiscall**)(int*))(thisPtr[0x5f2] + 100))(thisPtr[0x5f2]); // +0x17c8
    (*(void (__thiscall**)(int*))(thisPtr[0x60a] + 100))(thisPtr[0x60a]); // +0x1828
    (*(void (__thiscall**)(int*))(thisPtr[0x624] + 100))(thisPtr[0x624]); // +0x1890

    processPendingEvents(); // 0x005c1740 again

    (*(void (__thiscall**)(int*))(thisPtr[0x660] + 100))(thisPtr[0x660]); // +0x1980
    (*(void (__thiscall**)(int*))(thisPtr[0x675] + 100))(thisPtr[0x675]); // +0x19d4

    // Update some kind of list/container at offsets 0x6cc, 0x6d0, 0x71c
    updateListManager(); // 0x0094aba0

    int* list1 = thisPtr + 0x6cc; // +0x1b30
    processPendingUpdates(list1);  // 0x005c3960
    processPendingDeletions(list1); // 0x005c3b10

    int* list2 = thisPtr + 0x6d0; // +0x1b40
    processPendingUpdates(list2);
    processPendingDeletions(list2);

    int* list3 = thisPtr + 0x71c; // +0x1c70
    processPendingUpdates(list3);
    processPendingDeletions(list3);

    return thisPtr;
}