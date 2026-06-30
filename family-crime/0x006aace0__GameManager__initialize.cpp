// FUNC_NAME: GameManager::initialize
void __thiscall GameManager::initialize(GameManager *this)
{
  // Set vtable pointer at offset 0x00
  *(void **)this = &g_GameManagerVtable;
  // Set function pointers at known offsets
  *(void **)((char *)this + 0x3c) = &func_00d5d9cc; // +0x3C: callback?
  *(void **)((char *)this + 0x48) = &func_00d5d9c8; // +0x48: callback?
  // Check if sub-object at +0xF2 needs initialization
  if (*(char *)((char *)this + 0xf2) != 0) {
    *(char *)((char *)this + 0xf2) = 0; // clear flag
    FUN_006aab90((char *)this + 0x19); // Initialize sub-object at +0x19
  }
  // Destroy and reconstruct sub-object at +0x15
  FUN_004086d0(&DAT_0120e93c); // Global cleanup?
  FUN_004086d0((char *)this + 0x15); // Destroy sub-object
  FUN_00408310((char *)this + 0x15); // Reconstruct sub-object
  // Destroy and reconstruct sub-object at +0x17
  FUN_004086d0((char *)this + 0x17);
  FUN_00408310((char *)this + 0x17);
  // Initialization of game subsystems
  FUN_006aa780(); // e.g., Manager::startup
  FUN_0046c640(); // e.g., UpdateSystem::initialize
}