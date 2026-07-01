// Xbox PDB: EARS_Apt_UIHud_ShowTutorial
// FUNC_NAME: Player::handleTutorialTrigger
void __thiscall Player::handleTutorialTrigger(int this, undefined4 param_2, char param_3, int param_4)
{
  bool bVar1;
  char cVar2;
  undefined4 local_c;
  undefined4 local_8;
  undefined1 local_4;
  
  bVar1 = true;
  if (param_3 == '\0') {
    if (param_4 == 0) goto LAB_0093b5b4;
    *(int *)(this + 0xcc) = param_4 * 1000; // +0xCC: tutorialTimer (ms)
  }
  else {
    if ((*(uint *)(this + 0x5c) >> 0xf & 1) == 0) { // +0x5C: flags bit 15 (tutorialInProgress?)
      cVar2 = FUN_00911f40(0); // likely Player::isInGame or similar
      if ((cVar2 != '\0') && (*(int *)(this + 0x60) == 0)) { // +0x60: some state check
        FUN_0040eac0(1); // likely UI::showTutorialOverlay
        FUN_006913c0(10); // likely Audio::playTutorialSound
        *(uint *)(this + 0x5c) = *(uint *)(this + 0x5c) | 0x8000; // set bit 15
        *(undefined4 *)(this + 0xcc) = 3000; // tutorialTimer = 3 seconds
        goto LAB_0093b5a4;
      }
    }
    bVar1 = false;
    *(uint *)(this + 0x5c) = *(uint *)(this + 0x5c) | 0x10000; // set bit 16 (tutorialFailed?)
  }
LAB_0093b5a4:
  FUN_005c0260(this + 0x10, &LAB_0093b450, 1); // +0x10: some state machine, set callback
LAB_0093b5b4:
  *(undefined4 *)(this + 200) = param_2; // +0xC8: tutorialData
  if (bVar1) {
    FUN_005a04a0("ShowTutorial", 0, &DAT_00d8a64c, 0); // likely EventManager::triggerEvent
    *(uint *)(this + 0x5c) = *(uint *)(this + 0x5c) | 0x4000; // set bit 14 (tutorialShown)
    local_c = DAT_011301b8;
    local_8 = 0;
    local_4 = 0;
    FUN_00408a00(&local_c, 0); // likely some UI display function
  }
  return;
}