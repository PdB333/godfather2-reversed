// Xbox PDB: EARS_Apt_UIScoreboard_CallUpdate
// FUNC_NAME: Monopoly::updateBoardUI
void __thiscall Monopoly::updateBoardUI(int this, int param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 *puVar4;
  
  if (*(int *)(this + 100) != 0) { // +0x64: some flag/state
    if (*(int *)(DAT_0112b9b4 + 0x40) != 0) { // global pointer +0x40: some manager
      if ((((param_2 != -1) && (iVar1 = **(int **)(DAT_012233a0 + 4), iVar1 != 0)) &&
          (iVar1 != 0x1f30)) && (*(int *)(iVar1 + -0x38) == param_2)) {
        uVar2 = FUN_00983b20(param_2); // get some object by ID
        FUN_0094dbb0(uVar2); // update/refresh that object
      }
      uVar2 = FUN_008b4e20(1); // get some manager (1)
      uVar3 = FUN_008b4e20(0); // get some manager (0)
      FUN_0094e020(uVar3,uVar2); // update UI with both managers
    }
    FUN_00984630(); // update board state
    if ((*(char *)(this + 0x48) != '\0') && ((*(byte *)(this + 0x49) & 10) == 0)) { // +0x48: visible flag, +0x49: state flags
      puVar4 = *(undefined1 **)(this + 0x7c); // +0x7c: current board texture
      if (puVar4 == (undefined1 *)0x0) {
        puVar4 = &DAT_0120546e; // default texture string
      }
      *(undefined1 **)(this + 0x8c) = puVar4; // +0x8c: display texture
      puVar4 = *(undefined1 **)(this + 0x90); // +0x90: current don scoreboard texture
      if (puVar4 == (undefined1 *)0x0) {
        puVar4 = &DAT_0120546e; // default texture string
      }
      *(undefined1 **)(this + 0xa0) = puVar4; // +0xa0: display don scoreboard texture
      FUN_005a04a0("UpdateBoard",0,&DAT_00d77dc0,0); // trigger board update event
      if (*(char *)(this + 0x6c) != '\0') { // +0x6c: don scoreboard visible flag
        FUN_005a04a0("UpdateDonScoreboard",0,&DAT_00d77dc0,0); // trigger don scoreboard update event
      }
      *(undefined1 **)(this + 0xa0) = &DAT_00e2f044; // reset to empty texture
      *(undefined1 **)(this + 0x8c) = &DAT_00e2f044; // reset to empty texture
    }
  }
  return;
}