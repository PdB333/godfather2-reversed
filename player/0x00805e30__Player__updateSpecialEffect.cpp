// FUNC_NAME: Player::updateSpecialEffect

// Reconstructed C++ for function at 0x00805e30
// Role: Updates a special effect (sound or visual) for the player based on
//       current state and triggers a delayed effect.

void __fastcall Player::updateSpecialEffect(Player *thisPtr)
{
  int *pEffectManager;             // piVar1 - pointer to effect manager object
  bool bIsPlayerActive;            // cVar2
  int deltaTime;                   // iVar3
  int effectDelta;                 // iVar4 (not used directly in the code)

  // Begin frame update (possibly a lock or frame marker)
  beginFrameUpdate();

  // Get pointer to effectiveness manager from global singleton
  // DAT_0112b9b4 is likely the base address of a manager singleton
  pEffectManager = *(int **)(*(int *)0x0112b9b4 + 0x40);

  // Check: valid manager and its state is 2 (e.g., "active" or "missionActive")
  if ((pEffectManager != nullptr) && (pEffectManager[0x36] == 2)) {

    // Only proceed if a specific handle is valid (not -1)
    // +0x1ef8 stores a handle to an effect or target entity
    if (*(int *)((char *)thisPtr + 0x1ef8) != -1) {

      // Check player status
      bIsPlayerActive = isPlayerInGame();
      if (bIsPlayerActive) {
        // Additional check: audio system ready?
        bIsPlayerActive = isAudioSystemReady();
        if (bIsPlayerActive) {
          // Final check: mission or special condition active
          bIsPlayerActive = isMissionActive();
          if (bIsPlayerActive) {
            // Call a virtual method on the effect manager at +0xD0
            // (Likely "playSoundForHandle" or "spawnEffect")
            ((void (*)(int))(*pEffectManager + 0xD0))(*(int *)((char *)thisPtr + 0x1ef8));
          }
        }
      }
    }

    // Get the current frame delta time (used for timing)
    deltaTime = getFrameDeltaTime();

    // Check another global flag (DAT_01223484+8) and component hash
    // 0x5ade71cd is probably a hash for "FXComponent" or "SoundComponent"
    if ((*(int *)(*(int *)0x01223484 + 8) != 0) &&
        (hasComponent(pEffectManager, 0x5ade71cd) != 0)) {
      // Start a timed effect (handle + computed time offset)
      // +0x30 might be a base time offset for this type of effect
      startTimedEffect(*(int *)((char *)thisPtr + 0x1ef8), deltaTime + 0x30);
    }
  }
  return;
}