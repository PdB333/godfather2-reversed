// FUNC_NAME: EARSGameEngine::shutdown
void __thiscall EARSGameEngine::shutdown(EARSGameEngine* this)
{
  int* piVar1;
  undefined4* puVar2;
  
  // Shutdown core subsystems
  FUN_008b82d0(); // MemoryManager::shutdown
  FUN_006cc350(); // StreamManager::shutdown
  FUN_009cfa50(); // Unknown subsystem
  
  // Shutdown singleton objects
  if (DAT_01129950 != (undefined4 *)0x0) {
    (**(code **)*DAT_01129950)(1); // SingletonX::shutdown(1)
  }
  if (DAT_011299cc != (undefined4 *)0x0) {
    (**(code **)*DAT_011299cc)(1);
  }
  if (DAT_011299c8 != (undefined4 *)0x0) {
    (**(code **)*DAT_011299c8)(1);
  }
  if (DAT_011299c4 != (undefined4 *)0x0) {
    (**(code **)*DAT_011299c4)(1);
  }
  if (DAT_011299c0 != (undefined4 *)0x0) {
    (**(code **)*DAT_011299c0)(1);
  }
  if (DAT_01129898 != (undefined4 *)0x0) {
    (**(code **)*DAT_01129898)(1);
  }
  if (DAT_0112989c != (undefined4 *)0x0) {
    (**(code **)*DAT_0112989c)(1);
  }
  
  // Shutdown rendering/UI subsystems
  FUN_006938a0(); // Renderer::shutdown
  thunk_FUN_006911b0(); // FontManager::shutdown
  FUN_009202e0(0); // InputManager::shutdown(0)
  FUN_00868a30(); // AudioManager::shutdown
  
  // More singleton shutdowns
  if (DAT_011299b8 != (undefined4 *)0x0) {
    (**(code **)*DAT_011299b8)(1);
  }
  if (DAT_01129918 != (undefined4 *)0x0) {
    (**(code **)*DAT_01129918)(1);
  }
  if (DAT_012233ec != (undefined4 *)0x0) {
    (**(code **)*DAT_012233ec)(1);
  }
  if (DAT_011298fc != (undefined4 *)0x0) {
    (**(code **)*DAT_011298fc)(1);
  }
  if (DAT_011298b0 != (undefined4 *)0x0) {
    (**(code **)*DAT_011298b0)(1);
  }
  if (DAT_01223418 != (undefined4 *)0x0) {
    (**(code **)*DAT_01223418)(1);
  }
  if (DAT_01129954 != (undefined4 *)0x0) {
    (**(code **)*DAT_01129954)(1);
  }
  if (DAT_01129958 != (undefined4 *)0x0) {
    (**(code **)*DAT_01129958)(1);
  }
  
  // Shutdown network/physics
  FUN_006a61d0(); // NetworkManager::shutdown
  FUN_006a80b0(); // PhysicsManager::shutdown
  
  if (DAT_011299ac != (undefined4 *)0x0) {
    (**(code **)*DAT_011299ac)(1);
  }
  if (DAT_011299a0 != (undefined4 *)0x0) {
    (**(code **)*DAT_011299a0)(1);
  }
  if (DAT_0112999c != (undefined4 *)0x0) {
    (**(code **)*DAT_0112999c)(1);
  }
  if (DAT_011299a4 != (undefined4 *)0x0) {
    (**(code **)*DAT_011299a4)(1);
  }
  if (DAT_011299a8 != (undefined4 *)0x0) {
    (**(code **)*DAT_011299a8)(1);
  }
  
  // Shutdown game state managers
  FUN_00447fe0(); // MissionManager::shutdown
  FUN_00442320(); // CrimeManager::shutdown
  FUN_00444d90(); // FamilyManager::shutdown
  FUN_009cb680(); // DebugConsole::shutdown
  FUN_0082a2c0(); // EntityManager::shutdown
  
  // Shutdown player-specific data
  if ((*(int *)(this + 0x4d30) != 0) &&
     (puVar2 = (undefined4 *)(*(int *)(this + 0x4d30) + -0xc), puVar2 != (undefined4 *)0x0)) {
    (**(code **)*puVar2)(1); // PlayerComponent::shutdown(1)
  }
  
  FUN_00435b20(); // JobManager::shutdown
  if (DAT_012233f0 != (undefined4 *)0x0) {
    (**(code **)*DAT_012233f0)(1);
  }
  FUN_00439f30(); // DialogManager::shutdown
  FUN_00424950(); // UIHud::shutdown
  
  if (DAT_0112991c != (undefined4 *)0x0) {
    (**(code **)*DAT_0112991c)(1);
  }
  
  (**(code **)(*DAT_01129924 + 4))(); // Call virtual shutdown
  
  // Reset global singleton pointer table
  piVar1 = (int *)(DAT_01206880 + 0x14);
  **(undefined4 **)(DAT_01206880 + 0x14) = &PTR_LAB_00e5011c;
  *piVar1 = *piVar1 + 4;
  
  // Perform shutdown operations 4 times (probably for each phase)
  int iVar3 = 4;
  do {
    FUN_0068bcd0(0); // Phase shutdown A
    FUN_0068baf0(0); // Phase shutdown B
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  
  if (DAT_011298c4 != (undefined4 *)0x0) {
    (**(code **)*DAT_011298c4)(1);
  }
  if (DAT_01129964 != (undefined4 *)0x0) {
    (**(code **)*DAT_01129964)(1);
  }
  // ... [many more singleton shutdowns omitted for brevity]
  
  // Clean up remaining subsystems
  FUN_007edfb0(); // Cleanup resource
  FUN_007edfb0(); // Cleanup resource
  
  // Set static pointers to null
  DAT_011298c8 = 0;
  
  // More cleanup with vtable manipulation
  FUN_007edfb0(); // Cleanup resource
  
  // Final shutdown calls
  FUN_0043c050(); // DebugOverlay::shutdown
  FUN_00814090(); // ProfileSystem::shutdown
  FUN_00893d60(); // FileSystem::shutdown
  FUN_008ffb00(); // ConsoleSystem::shutdown
  FUN_00442030(); // EventManager::shutdown
  
  return;
}