// FUNC_NAME: ShowManager::setUpShowState

void __thiscall ShowManager::setUpShowState(ShowManager* this)
{
  int state = *(int*)((uint8_t*)this + 0xdc);
  if (state != 2) {
    *(int*)((uint8_t*)this + 0xc4) = 0;
    *(int*)((uint8_t*)this + 0xd4) = 0;
    int showType = 10; // default show type
    switch (state) {
    case 1:
    case 6:
      showType = 9;
      break;
    }
    *(int*)((uint8_t*)this + 0xd8) = showType;

    if (state == 4) {
      Debug::log("HideReadyState", 0, &DAT_00d8cdec, 0);
    }

    if (state == 1) {
      // some initialisation for state 1
      ShowManager::prepShowForState1();
    }

    // Register handlers for various events/states
    // Event handlers are stored in an array at this+0x10
    ShowManager::registerHandler((uint8_t*)this + 0x10, &ShowManager::onShowStart, 1);
    ShowManager::registerHandler((uint8_t*)this + 0x10, &ShowManager::onShowUpdate, 1);
    ShowManager::registerHandler((uint8_t*)this + 0x10, &ShowManager::onShowPause, 1);
    ShowManager::registerHandler((uint8_t*)this + 0x10, &ShowManager::onShowResume, 1);
    ShowManager::registerHandler((uint8_t*)this + 0x10, &ShowManager::onShowEnd, 1);

    // Set state to 2 (active/setup complete)
    *(int*)((uint8_t*)this + 0xdc) = 2;

    // Additional setup after handlers are registered
    ShowManager::postSetupShow();
  }

  // Always call these debug/log functions
  Debug::log("Destroy", 0, &DAT_00d8cdec, 0);
  Debug::log("ShowSetUp", 0, &DAT_00d8cdec, 0);

  // Retrieve the show state machine base pointer at this+0x508
  // +0x6c offset is the virtual function pointer table entry
  ShowStateMachineBase* base = *(ShowStateMachineBase**)((uint8_t*)this + 0x508);
  void (__thiscall *update)(int) = *(void (__thiscall**)(int))((uint8_t*)base + 0x6c);

  // Set flag indicating show is active
  *(uint8_t*)((uint8_t*)this + 0x554) = 1;

  // Call the update method with parameter 0 (e.g., deltaTime = 0)
  update(0);
}