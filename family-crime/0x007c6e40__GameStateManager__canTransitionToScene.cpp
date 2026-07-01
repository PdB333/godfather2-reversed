// FUNC_NAME: GameStateManager::canTransitionToScene
bool __thiscall GameStateManager::canTransitionToScene(int newSceneId)
{
  char cVar1;
  int *piVar2;
  undefined4 uVar3;

  // +0xC4: current active scene ID
  if (*(int *)(this + 0xC4) == newSceneId) {
    return false;
  }

  // Get the global mission/game manager singleton
  piVar2 = (int *)MissionManager::getInstance(); // FUN_007ab1f0
  if (piVar2 != (int *)0x0) {
    // Check if game is currently loading (e.g. streaming level)
    cVar1 = GameStateManager::isLoading(); // FUN_00701010
    if (cVar1 == '\0') {
      // Not loading: allocate a scene change request (size 0x38)
      uVar3 = operator_new(0x38); // FUN_00798f50
      cVar1 = SceneChangeRequest::initializeForUnload(uVar3); // FUN_0079e970
    }
    else {
      // Loading: allocate and init for load
      uVar3 = operator_new(0x38); // FUN_00798f50
      cVar1 = SceneChangeRequest::initializeForLoad(uVar3); // FUN_0079e920
    }

    // Proceed if initialization succeeded, and the mission manager's
    // transition eligibility callback (stored at +0x180) returns true,
    // and the game is in a ready state (e.g. not in cutscene)
    if (((cVar1 != '\0') &&
        (cVar1 = (**(code **)(*piVar2 + 0x180))(), cVar1 != '\0')) &&
       (cVar1 = GameStateManager::isGameReady(), cVar1 != '\0')) {
      // Allow transition only if specific scenes (0x42 = 66, 9) are active
      // (e.g. free roam or main menu)
      cVar1 = GameStateManager::isSceneActive(0x42); // FUN_007aefe0
      if ((cVar1 == '\0') && (cVar1 = GameStateManager::isSceneActive(9), cVar1 == '\0')) {
        return false;
      }
      return true;
    }
  }
  return false;
}