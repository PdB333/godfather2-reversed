// FUNC_NAME: GodfatherGameManager::shutdown
void __fastcall GodfatherGameManager::shutdown()
{
    int* tempPtr;
    int loopCount;
    uint gameStateFlags;

    // Flush pending engine messages 4 times
    loopCount = 4;
    do {
        Engine::processMessages(0);
        Engine::updateFrame(0);
        loopCount--;
    } while (loopCount != 0);

    // Clear controller input flag at +0x40 if singleton exists
    if (DAT_012234a0 != 0) {
        *(int*)(DAT_012234a0 + 0x40) = 0;
    }

    // Shutdown singletons via vtable (calling first virtual function with 1)
    if (DAT_011299d0 != nullptr) {
        (**(code**)(*DAT_011299d0))(1);
    }
    if (DAT_011299d4 != nullptr) {
        (**(code**)(*DAT_011299d4))(1);
    }

    // Destroy memory manager object at this+0x24
    tempPtr = *(int*)(this + 0x24);
    if (tempPtr != 0) {
        int* vtablePtr = (int*)(DAT_01206880 + 0x14);
        **(int**)(DAT_01206880 + 0x14) = &PTR_LAB_00e500f4;   // vtable override
        *vtablePtr = *vtablePtr + 4;
        MemoryManager::deallocate(tempPtr);
    }

    // More singleton shutdowns
    if (DAT_01223438 != nullptr) {
        (**(code**)(*DAT_01223438))(1);
    }
    if (DAT_0122343c != nullptr) {
        (**(code**)(*DAT_0122343c))(1);
    }
    if (DAT_01129908 != nullptr) {
        (**(code**)(*DAT_01129908))(1);
    }
    if (DAT_01223440 != nullptr) {
        (**(code**)(*DAT_01223440))(1);
    }

    // Shutdown streaming system
    StreamManager::shutdown();

    // Flush messages 2 times
    loopCount = 2;
    do {
        Engine::processMessages(0);
        Engine::updateFrame(0);
        loopCount--;
    } while (loopCount != 0);

    // Shutdown timer system
    TimerSystem::shutdown();

    // Save game state flags
    gameStateFlags = GameStateManager::getStateFlags();

    // If we have a scene manager at +0x1c, destroy it
    if (*(int*)(this + 0x1c) != 0) {
        SceneManager::shutdown();
        tempPtr = *(int*)(this + 0x1c);
        if (tempPtr != 0) {
            MemoryManager::releaseScene(tempPtr);
            MemoryManager::deallocate(tempPtr);
        }
        *(int*)(this + 0x1c) = 0;
    }

    // Destroy renderer at +0x20
    if (*(int*)(this + 0x20) != 0) {
        Renderer::shutdown();
        *(int*)(this + 0x20) = 0;
    }

    // More singleton shutdowns
    if (DAT_01129938 != nullptr) {
        (**(code**)(*DAT_01129938))(1);
    }
    if (DAT_01129984 != nullptr) {
        (**(code**)(*DAT_01129984))(1);
    }

    // Shutdown various subsystems
    ScriptSystem::shutdown();
    FontRenderer::shutdown();
    ParticleSystem::shutdown();
    UISystem::shutdown();
    AudioSystem::shutdown();
    CinematicSystem::shutdown();
    AnimationSystem::shutdown();
    PhysicsWorld::shutdown();
    HavokVisualDebugger::shutdown();
    NavMeshSystem::shutdown();
    PathfindingSystem::shutdown();

    // Clear critical section objects
    CriticalSection::release(&DAT_0112db64);
    CriticalSection::release(&DAT_0112db74);
    CriticalSection::release(&DAT_0112db6c);
    CriticalSection::release(&DAT_0112db7c);

    // Shutdown another singleton
    if (DAT_01223444 != nullptr) {
        (**(code**)(*DAT_01223444))(1);
    }

    // Unregister a bunch of component types from the component factory
    uint compType;
    compType = ComponentFactory::getTypeFromName("AICarBehavior");
    ComponentFactory::unregisterType(compType);
    compType = ComponentFactory::getTypeFromName("ActionOptions");
    ComponentFactory::unregisterType(compType);
    compType = ComponentFactory::getTypeFromName("Animated");
    ComponentFactory::unregisterType(compType);
    compType = ComponentFactory::getTypeFromName("Animation");
    ComponentFactory::unregisterType(compType);
    compType = ComponentFactory::getTypeFromName("AssetViewer");
    ComponentFactory::unregisterType(compType);
    compType = ComponentFactory::getTypeFromName("Attitude");
    ComponentFactory::unregisterType(compType);
    compType = ComponentFactory::getTypeFromName("AudioDataManager");
    ComponentFactory::unregisterType(compType);
    // Hardcoded CRC types
    ComponentFactory::unregisterType(0x19e7a3f0);
    ComponentFactory::unregisterType(0x480a2ab5);
    ComponentFactory::unregisterType(0xc87d40d1);
    compType = ComponentFactory::getTypeFromName("BNKStreamManager");
    ComponentFactory::unregisterType(compType);
    compType = ComponentFactory::getTypeFromName("BaseVehicle");
    ComponentFactory::unregisterType(compType);
    compType = ComponentFactory::getTypeFromName("Building");
    ComponentFactory::unregisterType(compType);
    compType = ComponentFactory::getTypeFromName("BuildingDebugMenu");
    ComponentFactory::unregisterType(compType);
    compType = ComponentFactory::getTypeFromName("BuildingManager");
    ComponentFactory::unregisterType(compType);
    compType = ComponentFactory::getTypeFromName("BuildingStore");
    ComponentFactory::unregisterType(compType);
    // ... more component type unregistrations with different registration flags
    compType = ComponentFactory::getTypeFromName("CSACrewComponent");
    ComponentFactory::unregisterTypePersistent(compType);
    compType = ComponentFactory::getTypeFromName("CameraManager");
    ComponentFactory::unregisterTypePersistent(compType);
    compType = ComponentFactory::getTypeFromName("ChaseCamera");
    ComponentFactory::unregisterTypePersistent(compType);
    ComponentFactory::unregisterTypePersistent(0xef7686fb);
    compType = ComponentFactory::getTypeFromName("ChaseManager");
    ComponentFactory::unregisterTypePersistent(compType);
    compType = ComponentFactory::getTypeFromName("ChatterPlaybackManager");
    ComponentFactory::unregisterTypePersistent(compType);
    compType = ComponentFactory::getTypeFromName("CollisionCamera");
    ComponentFactory::unregisterTypePersistent(compType);
    compType = ComponentFactory::getTypeFromName("CombatKnowledge");
    ComponentFactory::unregisterTypePersistent(compType);
    compType = ComponentFactory::getTypeFromName("CombatPerception");
    ComponentFactory::unregisterTypePersistent(compType);
    compType = ComponentFactory::getTypeFromName("CommonCombatDatabase");
    ComponentFactory::unregisterTypePersistent(compType);
    ComponentFactory::unregisterTypePersistent(0x90d2b839);
    compType = ComponentFactory::getTypeFromName("ControllerManager");
    ComponentFactory::unregisterTypePersistent(compType);
    ComponentFactory::unregisterTypePersistent(0xaa087880);
    ComponentFactory::unregisterTypePersistent(0xf97091c2);
    ComponentFactory::unregisterTypePersistent(0xa4ab3300);
    compType = ComponentFactory::getTypeFromName("CoverHintNode");
    ComponentFactory::unregisterType(compType);
    compType = ComponentFactory::getTypeFromName("CoverHintNodeManager");
    ComponentFactory::unregisterTypeNetworked(compType);
    compType = ComponentFactory::getTypeFromName("CoverState");
    ComponentFactory::unregisterTypeNetworked(compType);
    compType = ComponentFactory::getTypeFromName("CrewLeaderComponent");
    ComponentFactory::unregisterTypeNetworked(compType);
    compType = ComponentFactory::getTypeFromName("CrimeManager");
    ComponentFactory::unregisterTypeNetworked(compType);
    compType = ComponentFactory::getTypeFromName("CrimeScene");
    ComponentFactory::unregisterTypeNetworked(compType);
    compType = ComponentFactory::getTypeFromName("Debug");
    ComponentFactory::unregisterTypeNetworked(compType);

    // Reset component factory
    ComponentFactory::reset();

    // Shutdown singleton
    if (DAT_012233c4 != nullptr) {
        (**(code**)(*DAT_012233c4))(1);
    }

    // Shutdown memory pool
    MemoryPool::shutdown();

    // Flush messages 4 times
    loopCount = 4;
    do {
        Engine::processMessages(0);
        Engine::updateFrame(0);
        loopCount--;
    } while (loopCount != 0);

    // Shutdown more singletons
    if (DAT_012233b0 != nullptr) {
        (**(code**)(*DAT_012233b0))(1);
    }

    loopCount = 4;
    do {
        Engine::processMessages(0);
        Engine::updateFrame(0);
        loopCount--;
    } while (loopCount != 0);

    if (DAT_012233a4 != nullptr) {
        (**(code**)(*DAT_012233a4))(1);
    }

    loopCount = 4;
    do {
        Engine::processMessages(0);
        Engine::updateFrame(0);
        loopCount--;
    } while (loopCount != 0);

    if (DAT_01223448 != nullptr) {
        (**(code**)(*DAT_01223448))(1);
    }

    // Shutdown network system
    NetworkSystem::shutdown();

    // Shutdown more singletons
    if (DAT_01129880 != nullptr) {
        (**(code**)(*DAT_01129880))(1);
    }
    if (DAT_011299bc != nullptr) {
        (**(code**)(*DAT_011299bc))(1);
    }
    if (DAT_01129900 != nullptr) {
        (**(code**)(*DAT_01129900))(1);
    }

    // Clear global state flags
    DAT_012234f0[0xd] = 0;
    DAT_012234f0[0xb] = 0;
    DAT_012234f0[9] = 0;

    Engine::processMessages(0);
    Engine::updateFrame(0);

    // Shutdown additional subsystems via vtable calls
    if (DAT_01129924 != 0) {
        (*(code*)(**(int**)(DAT_01129924 + 4)))(1);
    }
    if (DAT_01129934 != nullptr) {
        (**(code**)(*DAT_01129934))(1);
    }
    if (DAT_0112993c != 0) {
        (*(code*)(**(int**)(DAT_0112993c + 4)))(1);
    }
    if (DAT_0112994c != nullptr) {
        (**(code**)(*DAT_0112994c + 8))(1);
    }
    if (DAT_012234f0 != nullptr) {
        (**(code**)(*DAT_012234f0))(1);
    }
    if (DAT_0112988c != nullptr) {
        (**(code**)(*DAT_0112988c))(1);
    }
    if (DAT_01129914 != nullptr) {
        (**(code**)(*DAT_01129914))(1);
    }

    Engine::processMessages(0);
    Engine::updateFrame(0);

    // Shutdown entity system
    EntitySystem::shutdown();
    // Shutdown debug drawing
    DebugDrawSystem::shutdown();

    if (DAT_01129818 != nullptr) {
        (**(code**)(*DAT_01129818))(1);
    }

    // Shutdown localization
    Localization::shutdown();

    if (DAT_01129894 != nullptr) {
        (**(code**)(*DAT_01129894))(1);
    }
    if (DAT_012233c0 != nullptr) {
        (**(code**)(*DAT_012233c0))(1);
    }
    if (DAT_01129888 != nullptr) {
        (**(code**)(*DAT_01129888))(1);
    }
    if (DAT_012234dc != nullptr) {
        (**(code**)(*DAT_012234dc))(1);
    }
    if (DAT_012234e4 != nullptr) {
        (**(code**)(*DAT_012234e4))(1);
    }
    if (DAT_01223484 != nullptr) {
        (**(code**)(*DAT_01223484 + 0x70))(1);
    }
    if (DAT_012234b8 != nullptr) {
        (**(code**)(*DAT_012234b8 + 0x68))(1);
    }
    if (DAT_012234d8 != nullptr) {
        (**(code**)(*DAT_012234d8))(1);
    }
    if (DAT_01129828 != nullptr) {
        (**(code**)(*DAT_01129828))(1);
    }
    if (DAT_01129814 != nullptr) {
        (**(code**)(*DAT_01129814))(1);
    }
    if (DAT_012234a4 != nullptr) {
        (**(code**)(*DAT_012234a4))(1);
    }
    if (DAT_01223450 != nullptr) {
        (**(code**)(*DAT_01223450))(1);
    }
    if (DAT_01223430 != nullptr) {
        (**(code**)(*DAT_01223430))(1);
    }
    if (DAT_011298a4 != nullptr) {
        (**(code**)(*DAT_011298a4))(1);
    }
    if (DAT_011298cc != nullptr) {
        (**(code**)(*DAT_011298cc))(1);
    }
    if (DAT_01223454 != nullptr) {
        (**(code**)(*DAT_01223454))(1);
    }
    if (DAT_01223408 != nullptr) {
        (**(code**)(*DAT_01223408))(1);
    }
    if (DAT_01129824 != nullptr) {
        (**(code**)(*DAT_01129824))(1);
    }
    if (DAT_01223410 != nullptr) {
        (**(code**)(*DAT_01223410))(1);
    }
    if (DAT_011298a0 != nullptr) {
        (**(code**)(*DAT_011298a0))(1);
    }
    if (DAT_011299b0 != nullptr) {
        (**(code**)(*DAT_011299b0))(1);
    }
    if (DAT_011299b4 != nullptr) {
        (**(code**)(*DAT_011299b4))(1);
    }
    if (DAT_012233fc != nullptr) {
        (**(code**)(*DAT_012233fc))(1);
    }
    if (DAT_012233f8 != nullptr) {
        (**(code**)(*DAT_012233f8))(1);
    }

    // Flush messages 3 times
    loopCount = 3;
    do {
        Engine::processMessages(0);
        Engine::updateFrame(0);
        loopCount--;
    } while (loopCount != 0);

    if (DAT_01223400 != nullptr) {
        (**(code**)(*DAT_01223400))(1);
    }

    // Shutdown input system
    InputSystem::shutdown();

    if (DAT_01223458 != nullptr) {
        (**(code**)(*DAT_01223458))(1);
    }

    // Shutdown multiplayer systems
    MultiplayerManager::shutdown();
    NetworkSession::shutdown();

    if (DAT_012234e8 != nullptr) {
        (**(code**)(*DAT_012234e8))(1);
    }
    if (DAT_0122345c != nullptr) {
        (**(code**)(*DAT_0122345c))(1);
    }

    // Restore game state flags
    GameStateManager::setStateFlags(gameStateFlags);

    if (DAT_012234ac != nullptr) {
        (**(code**)(*DAT_012234ac))(1);
    }

    // Shutdown mission system and more
    MissionSystem::shutdown();
    GameModeManager::shutdown();

    if (DAT_0122341c != nullptr) {
        (**(code**)(*DAT_0122341c))(1);
    }

    // Unregister various message types
    MessageSystem::unregisterType(0x67a6002e);
    MessageSystem::unregisterType(0x38b2b8d2);
    MessageSystem::unregisterType(0x7a10372b);
    MessageSystem::unregisterType(0x9dc401b7);
    MessageSystem::unregisterType(0x5393ac01);

    if (DAT_01223460 != nullptr) {
        (**(code**)(*DAT_01223460))(1);
    }
    if (DAT_01223464 != nullptr) {
        (**(code**)(*DAT_01223464))(1);
    }
    if (DAT_01223394 != nullptr) {
        (**(code**)(*DAT_01223394))(1);
    }

    // Shutdown physics world
    PhysicsWorld::shutdown();

    if (DAT_012233b4 != nullptr) {
        (**(code**)(*DAT_012233b4))(1);
    }

    // Shutdown rendering and GPU systems
    Renderer::shutdown();
    GpuStreamManager::shutdown();
    VertexBufferManager::shutdown();
    IndexBufferManager::shutdown();
    ShaderManager::shutdown();
    TextureManager::shutdown();
    MaterialManager::shutdown();
    LightManager::shutdown();
    CameraManager::shutdown();
    ViewportManager::shutdown();
    RenderTargetManager::shutdown();
    DepthStencilManager::shutdown();
    RasterizerStateManager::shutdown();
    BlendStateManager::shutdown();
    SamplerStateManager::shutdown();
    ConstantBufferManager::shutdown();
    BufferManager::shutdown();
    // Additional GPU resource managers
    ResourceManagerA::shutdown();
    ResourceManagerB::shutdown();
    ResourceManagerC::shutdown();
    // Shutdown effect system
    EffectManager::shutdown();
    // Shutdown window system
    WindowSystem::shutdown();
    // Final cleanup
    PostProcessManager::shutdown();
    return;
}