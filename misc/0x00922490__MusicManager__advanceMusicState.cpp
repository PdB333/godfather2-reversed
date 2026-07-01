// FUNC_NAME: MusicManager::advanceMusicState
void __fastcall MusicManager::advanceMusicState(int this)
{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int local_18;
  int local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined1 local_4;
  
  local_18 = 0;
  local_14 = 0;
  local_10 = 0;
  FUN_009217e0(&local_18); // getMusicStateList
  iVar4 = local_18;
  if (*(int *)(this + 0x74) < local_14) { // currentStateIndex < stateCount
    FUN_00891960(); // logDebugMessage
    local_c = DAT_011302e8; // some debug string
    local_8 = 0;
    local_4 = 0;
    FUN_00408a00(&local_c,0); // debugPrint
    piVar1 = (int *)(iVar4 + 4 + *(int *)(this + 0x74) * 8); // stateEntry + 4 + currentStateIndex*8
    *piVar1 = *piVar1 + -1; // decrement state timer
    iVar2 = *(int *)(iVar4 + 4 + *(int *)(this + 0x74) * 8); // get updated timer
    *(int *)(this + 0x9c) = iVar2; // store currentStateTimer
    if (iVar2 == 0) {
      local_14 = 0;
      FUN_009c8f10(iVar4); // releaseStateList
      local_18 = 0;
      local_10 = 0;
      FUN_009217e0(&local_18); // getMusicStateList again
      iVar4 = local_14;
      *(int *)(this + 0x7c) = local_14; // store stateCount
      FUN_009223c0(); // advanceToNextState
      *(undefined1 *)(this + 0xa0) = 0; // clear some flag
      *(uint *)(this + 0x74) =
           *(uint *)(this + 0x74) & (iVar4 <= (int)*(uint *)(this + 0x74)) - 1; // clamp currentStateIndex
      iVar4 = local_18;
    }
    iVar2 = *(int *)(this + 0x58); // currentLayer
    if (*(int *)(this + 0x78 + iVar2 * 4) < 1) { // layerStateCount
      if (*(int *)(this + 0xa4) != 0) { // pendingTransition
        FUN_004daf90((undefined4 *)(this + 0xa4)); // cancelTransition
        *(undefined4 *)(this + 0xa4) = 0;
      }
    }
    else {
      iVar3 = *(int *)(this + 0x78 + iVar2 * 4); // layerStateCount
      *(int *)(this + 0x74) = (*(int *)(this + 0x74) + iVar3) % iVar3; // wrap currentStateIndex
      if (iVar2 == 0) {
        FUN_00921730(); // processLayer0
      }
      else if (iVar2 == 1) {
        FUN_009218e0(); // processLayer1
      }
      else if (iVar2 == 2) {
        FUN_00921680(); // processLayer2
      }
    }
    FUN_00976270(); // updateMusicEngine
  }
  if (iVar4 != 0) {
    FUN_009c8f10(iVar4); // releaseStateList
  }
  return;
}