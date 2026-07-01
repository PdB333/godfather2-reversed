// FUNC_NAME: Player::updateState
void __fastcall Player::updateState(int thisPtr)
{
  char cVar1;
  int *piVar2;
  int iVar3;
  int *local_10;
  int local_c;
  undefined4 local_8;
  undefined1 local_4;
  
  // Check if there's a pending state change (state machine pointer at +0x54)
  if (*(int *)(thisPtr + 0x54) != 0) {
    local_8 = 0;
    local_4 = 0;
    local_c = *(int *)(thisPtr + 0x54);
    FUN_00408a00(&local_c,0);
  }
  
  // Check for special state identifiers (magic constants) at +0x1cc, +0x1d0, +0x1d4, +0x1d8
  // These appear to be state machine GUIDs or identifiers
  if (((((*(int *)(thisPtr + 0x1cc) == -0x45245246) && (*(int *)(thisPtr + 0x1d0) == -0x41104111))
       && (*(int *)(thisPtr + 0x1d4) == -0x153ea5ab)) && (*(int *)(thisPtr + 0x1d8) == -0x6eeff6ef))
     || (((*(int *)(thisPtr + 0x1cc) == 0 && (*(int *)(thisPtr + 0x1d0) == 0)) &&
         ((*(int *)(thisPtr + 0x1d4) == 0 && (*(int *)(thisPtr + 0x1d8) == 0)))))) {
    // Check state type at +0x1c4 (0 = idle, 0x48 = some specific state)
    if ((*(int *)(thisPtr + 0x1c4) == 0) || (*(int *)(thisPtr + 0x1c4) == 0x48)) {
      // Check another set of state identifiers at +0x64, +0x68, +0x6c, +0x70
      if (((*(int *)(thisPtr + 100) == -0x45245246) &&
          (((*(int *)(thisPtr + 0x68) == -0x41104111 && (*(int *)(thisPtr + 0x6c) == -0x153ea5ab))
           && (*(int *)(thisPtr + 0x70) == -0x6eeff6ef)))) ||
         ((((*(int *)(thisPtr + 100) == 0 && (*(int *)(thisPtr + 0x68) == 0)) &&
           ((*(int *)(thisPtr + 0x6c) == 0 && (*(int *)(thisPtr + 0x70) == 0)))) ||
          (iVar3 = FUN_00446100((int *)(thisPtr + 100),0), iVar3 == 0)))) goto LAB_008e38a0;
      piVar2 = (int *)FUN_008e1030(iVar3,0x96a9da2c);
      goto joined_r0x008e3896;
    }
  }
  else {
    // Different state path - query the state machine at +0x1cc
    piVar2 = (int *)FUN_00446100((int *)(thisPtr + 0x1cc),0);
    if (piVar2 == (int *)0x0) goto LAB_008e38a0;
    local_10 = (int *)0x0;
    cVar1 = (**(code **)(*piVar2 + 0x10))(0x96a9da2c,&local_10);
    piVar2 = local_10;
    if (cVar1 == '\\0') goto LAB_008e38a0;
joined_r0x008e3896:
    if (piVar2 == (int *)0x0) goto LAB_008e38a0;
  }
  // Trigger some action if state conditions are met
  FUN_00891a50(0);
LAB_008e38a0:
  // Check animation state at +0x11c (bit 0) and +0x120 (animation pointer)
  if ((*(byte *)(thisPtr + 0x11c) & 1) == 0) {
    if (*(int *)(thisPtr + 0x120) == 0) {
      piVar2 = (int *)0x0;
    }
    else {
      piVar2 = (int *)(*(int *)(thisPtr + 0x120) + -0x48);
    }
    local_10 = (int *)0x0;
    cVar1 = (**(code **)(*piVar2 + 0x10))(0x254cce9,&local_10);
    if ((cVar1 != '\\0') && (local_10 != (int *)0x0)) {
      iVar3 = (**(code **)(*local_10 + 0x160))();
      FUN_008e6b60(iVar3 + 0x20);
    }
  }
  // Check another animation state at +0xc0 (bit 0) and +0xc4 (animation pointer)
  if ((*(byte *)(thisPtr + 0xc0) & 1) == 0) {
    if (*(int *)(thisPtr + 0xc4) == 0) {
      piVar2 = (int *)0x0;
    }
    else {
      piVar2 = (int *)(*(int *)(thisPtr + 0xc4) + -0x48);
    }
    local_10 = (int *)0x0;
    cVar1 = (**(code **)(*piVar2 + 0x10))(0x254cce9,&local_10);
    if (((cVar1 != '\\0') && (local_10 != (int *)0x0)) &&
       (iVar3 = (**(code **)(*local_10 + 0x160))(), iVar3 != 0)) {
      FUN_00791a30();
    }
  }
  // Final cleanup - call update with -1 (invalidate) and reset global timer
  FUN_008e6320(thisPtr,0xffffffff);
  local_c = DAT_0112fdc0;
  local_8 = 0;
  local_4 = 0;
  FUN_00408a00(&local_c,0);
  return;
}