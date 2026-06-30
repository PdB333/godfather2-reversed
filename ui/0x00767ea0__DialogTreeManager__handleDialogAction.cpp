// FUNC_NAME: DialogTreeManager::handleDialogAction
undefined1 __thiscall DialogTreeManager::handleDialogAction(int this, undefined4 param_data1, float param_timerDelta, undefined4 param_data2, int actionId)
{
  int pDialogState;
  char boolFlag;
  undefined1 result;
  
  result = 1; // default return true
  switch(actionId - 0x23) {
  case 0: // ACTION_START_DIALOG (0x23)
    showDialog();
    hideDialog();
    return 1;
  case 1: // ACTION_ADVANCE_DIALOG (0x24)
    boolFlag = isDialogValid(); // FUN_0054f220
    if (boolFlag != '\0') {
      *(float *)(this + 0x84) = param_timerDelta + *(float *)(this + 0x84); // accumulate timer
      return 1;
    }
    break;
  case 2: // ACTION_CHOOSE_OPTION (0x25)
    pDialogState = *(int *)(*(int *)(this + 0x5c) + 0x21e4); // get state field
    hideDialog();
    if ((*(byte *)(pDialogState + 0x88) & 1) != 0) {
      completeDialog(); // FUN_0072cb10
    }
    showDialog();
    playDialogSound(); // FUN_007f63e0
    return 1;
  case 3: // ACTION_SELECT_CHOICE (0x26)
    pDialogState = *(int *)(this + 0x5c);
    setDialogChoice(); // FUN_0071b450
    hideDialog();
    showDialog();
    advanceDialogLine(); // FUN_0071ab70
    *(undefined4 *)(pDialogState + 0x2210) = DAT_01205228; // set global callback
    return 1;
  case 4: // ACTION_TRIGGER_TIMED (0x27)
    boolFlag = canEnterTimedState(); // FUN_00767710
    if (boolFlag != '\0') {
      pDialogState = *(int *)(this + 0x5c);
      startDialogTimer(); // FUN_00624bd0
      // Set up two callback functions for timer events
      setTimerCallback_1(CONCAT44(FUN_007347e0, pDialogState), (ulonglong)uStack_c << 0x20,
                         CONCAT44(&LAB_0073b090, local_8));
      setTimerCallback_2(CONCAT44(FUN_00716160, pDialogState + 0x2194), (ulonglong)uStack_c << 0x20,
                         CONCAT44(&LAB_0073b0a0, local_8));
      completeDialog(); // FUN_0072cb10
      return 1;
    }
    break;
  case 5: // ACTION_END (0x28)
    completeDialog(); // FUN_0072cb10
    return 1;
  case 6: // ACTION_NOP1 (0x29)
  case 8: // ACTION_NOP2 (0x2b)
    break;
  case 7: // ACTION_SHOW_MAP (0x2a)
    showMissionMap(); // FUN_004abdd0
    showMissionBriefing(); // FUN_004abe10
    return 1;
  default:
    result = handleDefaultDialogAction(); // FUN_0073e610
  }
  return result;
}