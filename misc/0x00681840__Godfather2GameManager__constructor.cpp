// FUNC_NAME: Godfather2GameManager::constructor
// Address: 0x00681840
// Role: Main game initialization and component registration for The Godfather 2

int __fastcall Godfather2GameManager::constructor(void* thisPtr)
{
    undefined4 uVar1;
    int iVar2;
    int* piVar3;
    undefined4* puVar4;
    undefined4 unaff_EBX;
    undefined1* puVar5;
    code* pcVar6;
    undefined4 local_64;
    undefined4 uStack_60;
    undefined4 uStack_5c;
    undefined4 uStack_58;
    undefined1 local_50[4];
    undefined4 local_4c;
    undefined4 local_48;
    undefined4 local_44;
    undefined4 local_38;
    char* pcStack_30;
    undefined* local_2c;
    undefined4 uStack_28;
    undefined4 uStack_24;
    char* pcStack_20;
    undefined4 uStack_1c;
    int* piStack_18;
    undefined1* puStack_14;
    code* pcStack_10;
    undefined1* puStack_c;
    undefined1* puStack_8;

    // Initialize memory manager
    gMemoryManager->init();

    // Zero out this+0x1c and this+0x20 (likely flags or pointers)
    *(undefined4*)((int)thisPtr + 0x1c) = 0;
    *(undefined4*)((int)thisPtr + 0x20) = 0;

    // Various engine subsystem initializations
    EngineConfig::init();
    ConsoleManager::init();
    ResourceManager::init();
    FileSystem::init();
    NetworkManager::init();
    InputSystem::init();
    TimerManager::init();
    PhysicsSystem::init();
    GameplayManager::init();
    AnimationManager::init();
    AudioManager::init();
    VFXManager::init();
    UIManager::init();
    ParticleManager::init();
    HavokManager::init();
    StreamingManager::init();
    PresentationManager::init();
    ScriptManager::init();
    ObjectFactory::init();

    // Set up render settings
    RenderSettings::setResolution(0x1ff); // 511? or 0x1ff as parameter
    uVar1 = getSystemTime(); // or some initial time
    local_64 = uVar1;

    // Allocate camera manager
    iVar2 = gHeapAlloc(0x10c); // size 0x10c
    if (iVar2 != 0) {
        CameraManager::init();
    }

    // Allocate input controller slots
    gInputManager->init(0x58c); // 16 controller slots? 0x58c/0x44 = 31.9? likely
    iVar2 = gHeapAlloc(0x58c);
    if (iVar2 != 0) {
        iVar2 = getInputManagerInstance();
        if (iVar2 == 0) {
            InputDeviceManager::init(0);
        } else {
            InputDeviceManager::init(iVar2 + 4);
        }
    }

    // Configure screen dimensions
    ScreenConfig::init(gScreenWidth, gScreenWidth + 1);

    // Allocate player manager
    gPlayerManager->init();
    gBehaviorManager->init();

    // Set up window dimensions
    local_44 = gWindowWidth;   // global
    local_4c = 0x28;           // 40
    local_48 = 0x14;           // 20
    local_38 = gWindowHeight;  // global

    // Allocate and initialize video buffer
    iVar2 = gHeapAlloc(0x18d0);
    if (iVar2 != 0) {
        VideoManager::init(uVar1, local_50, 0x80);
    }

    // Allocate renderer
    iVar2 = gHeapAlloc(0x10);
    if (iVar2 != 0) {
        Renderer::init(uVar1);
    }

    // Allocate texture manager
    gTextureManager->init();
    iVar2 = gHeapAlloc(0x20);
    if (iVar2 != 0) {
        TextureManager::init(uVar1, 0x20);
    }

    // Allocate font cache
    iVar2 = gHeapAlloc(0x20);
    if (iVar2 != 0) {
        FontCache::init(0x200, 0x200, uVar1, 0);
    }

    // Set up physics world
    PhysicsWorld::init(uVar1);
    iVar2 = gHeapAlloc(0x78);
    if (iVar2 != 0) {
        HavokWorld::init(uVar1, 0x80, 0x80);
    }

    // Configure AI parameters
    AIConfig::init(1, 0);

    // Set up nav mesh manager
    NavMeshManager::init();
    NavMemoryManager::initMemoryPools(uVar1, 0x1400); // 5120
    NavMemoryManager::initMemoryPools(uVar1, 0x3000); // 12288
    NavMemoryManager::initMemoryPools(uVar1, 0x60000); // 393216
    NavMemoryManager::initMemoryPools(uVar1, 0x18000); // 98304

    // Allocate pathfinding data
    iVar2 = gHeapAlloc(0x1044);
    if (iVar2 != 0) {
        PathfindingManager::init(uVar1, 0x1000, 0xc0000);
    }

    // Create the main game world
    uVar1 = GameWorld::create();
    uVar1 = GameWorld::getInstance(uVar1);
    *(undefined4*)(DAT_012234c4 + 0x10) = uVar1; // store world pointer
    *(undefined**)(DAT_012234c4 + 0x14) = &gGlobalData1; // various data pointers
    *(undefined**)(DAT_012234c4 + 0x18) = &gGlobalData2;
    *(undefined**)(DAT_012234c4 + 0x1c) = &gGlobalData3;
    *(undefined**)(DAT_012234c4 + 0x24) = &gGlobalData4;
    *(undefined**)(DAT_012234c4 + 0x20) = &gGlobalData5;

    // Initialize resource system
    ResourceDatabase::init(&gResourceTable);
    ResourceDatabase::registerSubdir(&gSkelFullDir, 5, "res_skel_full");
    ResourceDatabase::loadResourceList();
    iVar2 = gHeapAlloc(0xc);
    if (iVar2 != 0) {
        ResourceCache::init();
    }

    // Set up loot table manager
    LootTableManager::init();

    // Get current thread and setup exception handler
    piVar3 = (int*)Threading::getCurrentThread();
    iVar2 = *piVar3;
    uVar1 = getInputManager();
    (**(code**)(iVar2 + 0x20))(uVar1); // set thread exception handler?

    if (pcStack_10 != (code*)0x0) {
        (**(code**)(*(int*)pcStack_10 + 0xc))(); // call vtable function
    }
    pcStack_10 = (code*)piVar3;
    (**(code**)(*piVar3 + 8))(); // call vtable function

    puStack_c = (undefined1*)Threading::getCurrentThreadId();
    uVar1 = gHeapAlloc(0x200000);
    iVar2 = gHeapAlloc(0x18);
    if (iVar2 != 0) {
        PerThreadData::init(uVar1, &pcStack_30);
    }
    if (piStack_18 != (int*)0x0) {
        (**(code**)(*piStack_18 + 0xc))();
    }
    piStack_18 = (int*)0x0;
    iVar2 = gHeapAlloc(0x10);
    if (iVar2 != 0) {
        ThreadManager::init(&pcStack_30);
    }

    // Configure video memory sizes
    VideoMemoryManager::init(4);
    VideoMemoryManager::configurePools(0x40, 0x80, 0x1000000);

    if (piStack_18 != (int*)0x0) {
        (**(code**)(*piStack_18 + 0xc))();
    }

    // Initialize graphics pipeline
    iVar2 = gHeapAlloc(0x50);
    if (iVar2 != 0) {
        GraphicsPipeline::init(unaff_EBX, 0x20, 0x20, 0x40);
    }

    // Allocate various managers
    iVar2 = gHeapAlloc(0x9c0);
    if (iVar2 != 0) {
        WeaponManager::init();
    }
    iVar2 = gHeapAlloc(0x24);
    if (iVar2 != 0) {
        VehicleManager::init();
    }
    iVar2 = gHeapAlloc(0x2d8);
    if (iVar2 != 0) {
        CombatManager::init(15000, 0, unaff_EBX, 1000, 4000, 400);
    }
    iVar2 = gHeapAlloc(0x218);
    if (iVar2 != 0) {
        MissionManager::init();
    }
    iVar2 = gHeapAlloc(0xb0);
    if (iVar2 != 0) {
        DialogTreeManager::init();
    }
    iVar2 = gHeapAlloc(0x3c);
    if (iVar2 != 0) {
        DataStoreManager::init();
    }
    iVar2 = gHeapAlloc(0x18);
    if (iVar2 != 0) {
        MusicPlayer::init("MUSIC");
    }
    iVar2 = gHeapAlloc(0x2024);
    if (iVar2 != 0) {
        AudioManager::init(); // 0x2024 size
    }
    iVar2 = gHeapAlloc(0x2c);
    if (iVar2 != 0) {
        AudioChannelManager::init(0x20, unaff_EBX);
    }
    iVar2 = gHeapAlloc(0x2f0);
    if (iVar2 != 0) {
        AnimationStateMachine::init();
    }
    iVar2 = gHeapAlloc(0x10);
    if (iVar2 != 0) {
        ParticleEffectManager::init(unaff_EBX);
    }
    iVar2 = gHeapAlloc(0xf0);
    if (iVar2 != 0) {
        VFXManager::init(unaff_EBX);
    }

    // Set up crash reporting / session IDs
    gCrashReporter->init(0x93efa6cd, 0x22cfbde9, 0xe241c048);
    gCrashReporter->init2(0xbae5ffbf, 0xf7b7113e);
    gCrashReporter->init3(0x6d81fbab, 0x76497f7b, 0x4776a0db, 0x174706f6, 0x70984452);

    iVar2 = gHeapAlloc(0x10);
    if (iVar2 != 0) {
        DebugOverlay::init();
    }

    uStack_1c = gRenderWindowManager->init();
    pcStack_30 = "/PC/GODFATHER-2007";
    local_2c = &gGameSettingsData;
    uStack_28 = 1;
    uStack_24 = 0x46a0;
    pcStack_20 = "godfather2-pc";
    piStack_18 = (int*)0x1;
    puStack_14 = &LAB_008a1b10;
    pcStack_10 = (code*)FUN_008a1610;
    puStack_c = &LAB_0067fa00;
    puStack_8 = &LAB_0067faf0;

    // Allocate and initialize game application context
    iVar2 = gHeapAlloc(0x238);
    if (iVar2 != 0) {
        uVar1 = getInputManager();
        GameAppContext::init(&pcStack_30, uVar1);
    }

    // Allocate online services manager
    iVar2 = gHeapAlloc(0x3d8);
    if (iVar2 != 0) {
        OnlineServices::init();
    }

    // Allocate save game manager
    iVar2 = gHeapAlloc(0x28);
    if (iVar2 != 0) {
        SaveGameManager::init();
    }

    // Allocate streaming / resource cache
    iVar2 = gHeapAlloc(0x804c);
    if (iVar2 != 0) {
        ResourceStreamer::init();
    }

    // Allocate network session
    iVar2 = gHeapAlloc(0xc);
    if (iVar2 != 0) {
        NetSession::init();
    }

    // Allocate gameplay debugger
    iVar2 = gHeapAlloc(0x4dc);
    if (iVar2 != 0) {
        GameplayDebugger::init();
    }

    // Allocate UI manager
    iVar2 = gHeapAlloc(0x880);
    if (iVar2 != 0) {
        UIManager::init();
    }
    UIManager::registerComponents();

    // Allocate input handler
    iVar2 = gHeapAlloc(0xc);
    if (iVar2 != 0) {
        InputHandler::init();
    }

    gConsoleManager->init();

    // Allocate building manager
    iVar2 = gHeapAlloc(0xd4);
    if (iVar2 != 0) {
        BuildingManager::init();
    }

    // Allocate crew AI manager
    iVar2 = gHeapAlloc(0x3c);
    if (iVar2 != 0) {
        CrewAIManager::init();
    }

    // Allocate crime manager
    iVar2 = gHeapAlloc(0x34);
    if (iVar2 != 0) {
        CrimeManager::init();
    }

    // Allocate family manager
    iVar2 = gHeapAlloc(0x2678);
    if (iVar2 != 0) {
        FamilyManager::init(unaff_EBX);
    }

    // Set up memory allocator for rendering
    piVar3 = (int*)gMemoryAllocator::init(&LAB_00500000);
    iVar2 = gHeapAlloc(0x44);
    if (iVar2 != 0) {
        RenderMemoryAllocator::init(piVar3, 0x20000);
    }
    (**(code**)(*piVar3 + 0xc))(); // call vtable function

    // Create controller manager instance
    puVar4 = (undefined4*)gHeapAlloc(8);
    if (puVar4 != (undefined4*)0x0) {
        puVar4[1] = &vtable1;
        gControllerManager = puVar4;
        *puVar4 = &vtable2;
        puVar4[1] = &vtable3;
    }
    ControllerManager::init(gControllerManager);

    // Create input device manager
    puVar4 = (undefined4*)gHeapAlloc(8);
    if (puVar4 != (undefined4*)0x0) {
        puVar4[1] = &vtable4;
        gInputDeviceManager = puVar4;
        *puVar4 = &vtable5;
        puVar4[1] = &vtable6;
    }
    InputDeviceManager::init(gInputDeviceManager);

    // Allocate network system
    iVar2 = gHeapAlloc(0x24);
    if (iVar2 != 0) {
        NetworkSystem::init();
    }
    NetworkManager::initGlobal(gNetworkManager);

    // Allocate multiplayer scenario manager
    iVar2 = gHeapAlloc(0x50);
    if (iVar2 != 0) {
        MultiplayerScenarioManager::init();
    }

    // Allocate weather manager
    iVar2 = gHeapAlloc(0x30);
    if (iVar2 != 0) {
        WeatherManager::init();
    }

    // Allocate destructible object manager
    iVar2 = gHeapAlloc(0x5c);
    if (iVar2 != 0) {
        DestructibleManager::init();
    }

    // Allocate chatter playback
    iVar2 = gHeapAlloc(0x3c);
    if (iVar2 != 0) {
        ChatterPlaybackManager::init();
    }

    // Initialize game statistics
    gStatManager->init();
    gScriptFunctionRegistry->init(0x6a73ba16, &LAB_00452b60); // register script functions
    gScriptFunctionRegistry->init(0x7c32d73b, (code*)FUN_0085c150);
    gScriptFunctionRegistry->init(0xa0d329d6, &LAB_008f08e0);
    gScriptFunctionRegistry->init(0xcffc631f, &LAB_0083b1a0);
    gScriptFunctionRegistry->init(0xfe84b724, &LAB_0083aa10);
    gScriptFunctionRegistry->init(0x1afdd13b, &LAB_0083ae20);
    gScriptFunctionRegistry->init(0xb703f7bf, (code*)FUN_008f86a0);
    gScriptFunctionRegistry->init(0xf9608b20, &LAB_009091c0);
    gScriptFunctionRegistry->init(0x10e5319e, &LAB_008f0960);
    gScriptFunctionRegistry->init(0xa5975eb2, &LAB_008f0960);
    gScriptFunctionRegistry->init(0x580e3e39, (code*)FUN_0044e6d0);
    gScriptFunctionRegistry->init(0x774eb208, (code*)FUN_0044e6d0);
    gScriptFunctionRegistry->init(0xdb8457d3, &LAB_009b8300);
    gScriptFunctionRegistry->init(0x4ecfbe13, &LAB_00856490);
    gScriptFunctionRegistry->init(0xf26fb813, &LAB_00856490);
    gScriptFunctionRegistry->init(0x332d5a20, &LAB_00856490);
    gScriptFunctionRegistry->init(0xdb90da76, &LAB_0067f4c0);
    gScriptFunctionRegistry->init(0xcae15a68, &LAB_007f24a0);
    gScriptFunctionRegistry->init(0x83c382cf, &LAB_006a54a0);
    gScriptFunctionRegistry->init(0xbaaf7236, &LAB_006a80c0);

    // Initialize various UI and debug systems
    gUIDialogManager->init();
    gDebugMenu->init();
    gHelpSystem->init();
    gHUDManager->init();
    gMapManager->init();
    gMinimapManager->init();
    gTutorialManager->init();
    gMobfaceManager->init();
    gStatsScreen->init();
    gFamilyTreeUI->init();
    gWeaponWheel->init();

    // Allocate and initialize player progression data
    iVar2 = gHeapAlloc(0x20);
    if (iVar2 != 0) {
        PlayerProgression::init();
    }

    local_64 = 0;
    gAIDirector->init(&local_64);
    gComponentTaskScheduler->init(1);

    // Create and initialize the world simulation (maybe physics)
    puVar4 = (undefined4*)gEngineAllocator->alloc();
    uStack_60 = 2;
    uStack_5c = 0x10;
    uStack_58 = 0;
    iVar2 = (**(code**)*puVar4)(0x70, &uStack_60);
    if (iVar2 != 0) {
        gWorldSim->init(0);
    }

    // Create collision system
    puVar4 = (undefined4*)gEngineAllocator->alloc();
    local_64 = 0x10;
    uStack_60 = 0;
    iVar2 = (**(code**)*puVar4)(0x50, &stack0xffffff98);
    if (iVar2 != 0) {
        CollisionSystem::init();
    }

    // Allocate AI navigation
    iVar2 = gHeapAlloc(0x18);
    if (iVar2 != 0) {
        Navigation::init(unaff_EBX);
    }

    // Allocate AI perception
    iVar2 = gHeapAlloc(0x80);
    if (iVar2 != 0) {
        AIPerception::init(unaff_EBX, unaff_EBX);
    }

    // Initialize Lua manager
    LuaManager::init();

    // Register many component factories with hash IDs
    gComponentFactory->registerFactory(0xc87d40d1, &LAB_0067d450);
    gComponentFactory->registerFactory(0x480a2ab5, &LAB_0067dc20);
    gComponentFactory->registerFactory(0x19e7a3f0, &LAB_0044c0d0);
    puVar5 = &LAB_0067dc50;
    uVar1 = gFactory::getFactoryHash(&LAB_0067dc50);
    gComponentFactory->registerFactory(uVar1, puVar5);
    puVar5 = &LAB_0067dc80;
    uVar1 = gFactory::getFactoryHash(&LAB_0067dc80);
    gComponentFactory->registerFactory(uVar1, puVar5);
    puVar5 = &LAB_0067dcb0;
    uVar1 = gFactory::getFactoryHash(&LAB_0067dcb0);
    gComponentFactory->registerFactory(uVar1, puVar5);
    puVar5 = &LAB_0067dce0;
    uVar1 = gFactory::getFactoryHash(&LAB_0067dce0);
    gComponentFactory->registerFactory(uVar1, puVar5);
    puVar5 = &LAB_0067dd10;
    uVar1 = gFactory::getFactoryHash(&LAB_0067dd10);
    gComponentFactory->registerFactory(uVar1, puVar5);
    puVar5 = &LAB_0067dd40;
    uVar1 = gFactory::getFactoryHash(&LAB_0067dd40);
    gComponentFactory->registerFactory(uVar1, puVar5);
    puVar5 = &LAB_0067d5e0;
    uVar1 = gFactory::getFactoryHash(&LAB_0067d5e0);
    gComponentFactory->registerFactory(uVar1, puVar5);
    puVar5 = &LAB_0067dd70;
    uVar1 = gFactory::getFactoryHash(&LAB_0067dd70);
    gComponentFactory->registerFactory(uVar1, puVar5);
    puVar5 = &LAB_0067d770;
    uVar1 = gFactory::getFactoryHash(&LAB_0067d770);
    gComponentFactory->registerFactory(uVar1, puVar5);
    puVar5 = &LAB_0067d850;
    uVar1 = gFactory::getFactoryHash(&LAB_0067d850);
    gComponentFactory->registerFactory(uVar1, puVar5);
    puVar5 = &LAB_0067d7c0;
    uVar1 = gFactory::getFactoryHash(&LAB_0067d7c0);
    gComponentFactory->registerFactory(uVar1, puVar5);
    puVar5 = &LAB_0067d4c0;
    uVar1 = gFactory::getFactoryHash(&LAB_0067d4c0);
    gComponentFactory->registerFactory(uVar1, puVar5);
    puVar5 = &LAB_0067d480;
    uVar1 = gFactory::getFactoryHash(&LAB_0067d480);
    gComponentFactory->registerFactory(uVar1, puVar5);

    // Register interface factories
    pcVar6 = (code*)FUN_00999e90;
    uVar1 = gInterfaceFactory::getHash(FUN_00999e90);
    gInterfaceRegistry->registerInterface(uVar1, pcVar6);
    pcVar6 = (code*)FUN_00416c70;
    uVar1 = gInterfaceFactory::getHash(FUN_00416c70);
    gInterfaceRegistry->registerInterface(uVar1, pcVar6);
    pcVar6 = (code*)FUN_0099c630;
    uVar1 = gInterfaceFactory::getHash(FUN_0099c630);
    gInterfaceRegistry->registerInterface(uVar1, pcVar6);
    pcVar6 = (code*)FUN_00858670;
    uVar1 = gInterfaceFactory::getHash(FUN_00858670);
    gInterfaceRegistry->registerInterface(uVar1, pcVar6);
    puVar5 = &LAB_0044bb00;
    uVar1 = gInterfaceFactory::getHash(&LAB_0044bb00);
    gInterfaceRegistry->registerInterface(uVar1, puVar5);
    gInterfaceRegistry->registerInterface(0xef7686fb, &LAB_0067d6c0);
    puVar5 = &LAB_006817f0;
    uVar1 = gInterfaceFactory::getHash(&LAB_006817f0);
    gInterfaceRegistry->registerInterface(uVar1, puVar5);
    pcVar6 = (code*)FUN_0067d6f0;
    uVar1 = gInterfaceFactory::getHash(FUN_0067d6f0);
    gInterfaceRegistry->registerInterface(uVar1, pcVar6);
    pcVar6 = (code*)FUN_00999b10;
    uVar1 = gInterfaceFactory::getHash(FUN_00999b10);
    gInterfaceRegistry->registerInterface(uVar1, pcVar6);
    puVar5 = &LAB_0067d8c0;
    uVar1 = gInterfaceFactory::getHash(&LAB_0067d8c0);
    gInterfaceRegistry->registerInterface(uVar1, puVar5);
    puVar5 = &LAB_0067d740;
    uVar1 = gInterfaceFactory::getHash(&LAB_0067d740);
    gInterfaceRegistry->registerInterface(uVar1, puVar5);
    pcVar6 = (code*)FUN_008cd270;
    uVar1 = gInterfaceFactory::getHash(FUN_008cd270);
    gInterfaceRegistry->registerInterface(uVar1, pcVar6);
    gInterfaceRegistry->registerInterface(0xa4ab3300, &LAB_0067d620);
    pcVar6 = (code*)FUN_0067d910;
    uVar1 = gInterfaceFactory::getHash(FUN_0067d910);
    gInterfaceRegistry->registerInterface(uVar1, pcVar6);
    pcVar6 = (code*)FUN_0067d990;
    uVar1 = gInterfaceFactory::getHash(FUN_0067d990);
    gInterfaceRegistry->registerInterface(uVar1, pcVar6);
    gInterfaceRegistry->registerInterface(0x90d2b839, &LAB_0067d9f0);
    puVar5 = &LAB_0067da20;
    uVar1 = gInterfaceFactory::getHash(&LAB_0067da20);
    gInterfaceRegistry->registerInterface(uVar1, puVar5);
    pcVar6 = (code*)FUN_008cf2b0;
    uVar1 = gInterfaceFactory::getHash(FUN_008cf2b0);
    gInterfaceRegistry->registerInterface(uVar1, pcVar6);
    gInterfaceRegistry->registerInterface(0xaa087880, &LAB_0067da60);
    gInterfaceRegistry->registerInterface(0xf97091c2, &LAB_0067daa0);

    // Register update manager with main loop
    gUpdateManager->registerUpdateable((code*)FUN_00449f20);

    // Register more component factories
    puVar5 = &LAB_0067d650;
    uVar1 = gFactory::getFactoryHash(&LAB_0067d650);
    gComponentFactory->registerFactory(uVar1, puVar5);

    // Register additional interface factories
    pcVar6 = (code*)FUN_0044b790;
    uVar1 = gInterfaceFactory::getHash(FUN_0044b790);
    gInterfaceRegistry->registerInterface2(uVar1, pcVar6);
    pcVar6 = (code*)FUN_008cca30;
    uVar1 = gInterfaceFactory::getHash(FUN_008cca30);
    gInterfaceRegistry->registerInterface2(uVar1, pcVar6);
    pcVar6 = (code*)FUN_008cd410;
    uVar1 = gInterfaceFactory::getHash(FUN_008cd410);
    gInterfaceRegistry->registerInterface2(uVar1, pcVar6);
    pcVar6 = (code*)FUN_008cd660;
    uVar1 = gInterfaceFactory::getHash(FUN_008cd660);
    gInterfaceRegistry->registerInterface2(uVar1, pcVar6);
    pcVar6 = (code*)FUN_008cdbe0;
    uVar1 = gInterfaceFactory::getHash(FUN_008cdbe0);
    gInterfaceRegistry->registerInterface2(uVar1, pcVar6);
    pcVar6 = (code*)FUN_008ce0a0;
    uVar1 = gInterfaceFactory::getHash(FUN_008ce0a0);
    gInterfaceRegistry->registerInterface2(uVar1, pcVar6);
    puVar5 = &LAB_008cea90;
    uVar1 = gInterfaceFactory::getHash(&LAB_008cea90);
    gInterfaceRegistry->registerInterface2(uVar1, puVar5);

    // Set up some global parameters
    gParameterManager->setParameter(0xa500bcbc, 100);
    gParameterManager->setParameter2(0x30256d83, 1);

    // Allocate AI world state
    iVar2 = gHeapAlloc(0x30);
    if (iVar2 != 0) {
        AIWorldState::init(1000, 500, 1000, 400);
    }

    // Allocate NPC manager
    iVar2 = gHeapAlloc(0x440);
    if (iVar2 != 0) {
        NPCManager::init(unaff_EBX);
    }

    // Allocate player family tree
    iVar2 = gHeapAlloc(0x48);
    if (iVar2 != 0) {
        PlayerFamilyTree::init();
    }

    // Initialize remaining systems
    gEntityManager->init();
    gMaterialManager->init();
    gPropManager->init();
    gConsoleVariable::set(0); // some global flag
    gThreadPool->init(0x100);
    gCrashDumpHandler->init();

    // Allocate multi-threaded job system
    iVar2 = gHeapAlloc(4);
    if (iVar2 != 0) {
        JobSystem::init();
    }

    // Allocate career data manager
    iVar2 = gHeapAlloc(0x1c);
    if (iVar2 != 0) {
        CareerDataManager::init();
    }

    // Allocate cheat system
    iVar2 = gHeapAlloc(4);
    if (iVar2 != 0) {
        CheatSystem::init();
    }

    // Set up game state vtable
    *(undefined1**)(DAT_01223378 + 0x50) = &gGameStateVtable;

    // Allocate game state machine
    iVar2 = gHeapAlloc(0x10);
    if (iVar2 != 0) {
        GameStateMachine::init();
    }

    // Create main game state object
    iVar2 = gHeapAlloc(1);
    if (iVar2 == 0) {
        iVar2 = 0;
    } else {
        // Initialize game state with vtable
        gGameState->constructor();
        gGameState->init(0, 0x340);
        piVar3 = (int*)(DAT_01206880 + 0x14);
        **(undefined4**)(DAT_01206880 + 0x14) = &vtableForGameState;
        *piVar3 = *piVar3 + 4;
    }
    *(int*)((int)thisPtr + 0x24) = iVar2; // store game state pointer

    // Allocate player inventory manager
    iVar2 = gHeapAlloc(4);
    if (iVar2 != 0) {
        InventoryManager::init();
    }

    // Allocate player reputation tracker
    iVar2 = gHeapAlloc(4);
    if (iVar2 != 0) {
        ReputationTracker::init();
    }

    // Set up vtable for game logic
    *(code**)(DAT_012234a0 + 0x40) = (code*)FUN_0068fc60;

    // Initialize game mode
    gGameModeManager->init(0);
    gGameModeManager->postInit();

    return (int)thisPtr;
}