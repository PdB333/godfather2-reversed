// FUNC_NAME: PlayerSM::updateState
void __fastcall PlayerSM::updateState(int thisPtr)
{
  int iVar1;
  int iVar2;
  char cVar3;
  undefined4 uVar4;
  int unaff_ESI;
  int *piVar5;
  undefined4 auStack_94 [15];
  undefined1 auStack_58 [84];
  
  iVar1 = *(int *)(thisPtr + 0xc4); // +0xC4: currentStateData
  if ((iVar1 == 0) || (piVar5 = (int *)(iVar1 + -0x48), piVar5 == (int *)0x0)) {
    // No valid state or state vtable pointer
    if (((*(uint *)(*(int *)(thisPtr + 0x10) + 0x14) & 0x1000) != 0) && // +0x10: player, +0x14: flags, check bit 12
       (*(int *)(thisPtr + 0xb4) != 0)) { // +0xB4: some pointer
      if ((*(uint *)(thisPtr + 0xc) & 0x20000) == 0) { // +0xC: stateFlags, check bit 17
        *(uint *)(thisPtr + 0xc) = *(uint *)(thisPtr + 0xc) | 0x20000;
        FUN_0051b120(); // likely enterState or transition
      }
      *(uint *)(thisPtr + 0xc) = *(uint *)(thisPtr + 0xc) & 0xfffbffff; // clear bit 18
    }
    *(undefined4 *)(thisPtr + 0xb4) = 0;
    FUN_0051d230(0); // likely exitState or cleanup
  }
  else {
    // Valid state exists
    *(int **)(thisPtr + 0xb4) = piVar5; // +0xB4: currentStateVtable
    uVar4 = (**(code **)(*piVar5 + 0x58))(); // vtable+0x58: getStateDuration or similar
    *(undefined4 *)(thisPtr + 0x84) = uVar4; // +0x84: stateDuration
    auStack_94[0] = 0;
    cVar3 = (**(code **)(*piVar5 + 0x10))(0xae986323,auStack_94); // vtable+0x10: checkStateCondition with hash
    if ((((cVar3 != '\0') && (unaff_ESI != 0)) && (iVar2 = *(int *)(unaff_ESI + 0x218), iVar2 != 0)) // +0x218: some object
       && ((*(uint *)(iVar2 + 0x10) & 0x4480000) == 0)) { // check flags
      FUN_0044b4e0(auStack_58,iVar1 + 0x88); // copy state data
      FUN_00577b30(iVar2); // process state transition
      FUN_00417560(); // cleanup or finalize
      return;
    }
    if ((*(uint *)(*(int *)(thisPtr + 0x10) + 0x14) & 0x1000) != 0) {
      if ((*(uint *)(thisPtr + 0xc) & 0x20000) == 0) {
        *(uint *)(thisPtr + 0xc) = *(uint *)(thisPtr + 0xc) | 0x20000;
        FUN_0051b120();
      }
      *(uint *)(thisPtr + 0xc) = *(uint *)(thisPtr + 0xc) & 0xfffbffff;
      return;
    }
  }
  return;
}