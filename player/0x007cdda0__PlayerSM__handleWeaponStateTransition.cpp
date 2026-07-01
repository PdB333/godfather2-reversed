// FUNC_NAME: PlayerSM::handleWeaponStateTransition
void __fastcall PlayerSM::handleWeaponStateTransition(int *thisPtr)

{
  code *vtableEntry;
  bool bVar2;
  char cVar3;
  int iVar4;
  undefined4 *puVar5;
  
  iVar4 = thisPtr[0x16]; // +0x58 - some object pointer
  cVar3 = FUN_007f7c50(); // likely isPlayerInVehicle or similar
  if (((cVar3 == '\0') && ((*(uint *)(iVar4 + 0x24a0) >> 5 & 1) == 0)) &&
     ((*(byte *)(iVar4 + 0x8e4) & 1) == 0)) {
    bVar2 = false;
  }
  else {
    bVar2 = true; // player is in vehicle or some blocking state
  }
  if ((((uint)thisPtr[0x74] >> 7 & 1) != 0) && (!bVar2)) {
    // Weapon is being drawn (bit 7 set) and player is not blocked
    cVar3 = FUN_007cbc10(1); // likely isWeaponEquipped or similar
    if (cVar3 == '\0') {
      thisPtr[0x74] = thisPtr[0x74] & 0xffffffbf; // clear bit 6
    }
    else {
      thisPtr[0x74] = thisPtr[0x74] | 0x40; // set bit 6
    }
    if (thisPtr[0x6d] == 0) { // +0x1B4 - some pointer
      iVar4 = 0;
    }
    else {
      iVar4 = thisPtr[0x6d] + -0x48; // offset calculation
    }
    if (*(char *)(iVar4 + 0x1b8c) != '\0') { // check some flag
      puVar5 = (undefined4 *)FUN_007ab160(); // get audio manager
      (**(code **)*puVar5)(0x80); // play weapon draw sound
      puVar5 = (undefined4 *)FUN_007ab160();
      (**(code **)*puVar5)(1); // play another sound
    }
    FUN_007cb110(*(uint *)(*(int *)(*(int *)(thisPtr[0x70] + 0x10) + 4) + 0x24 +
                          thisPtr[0x68] * 0x2c) >> 7 & 0xffffff01); // update weapon state
    vtableEntry = *(code **)(*thisPtr + 0x2c); // vtable entry for animation
    thisPtr[0x73] = 0x46f5c7b4; // set animation hash
    (*vtableEntry)(0x46f5c7b4,1,1,0,0x3f800000,0x3f800000); // play animation
    FUN_007cb020(); // update weapon visibility
    return;
  }
  if ((((uint)thisPtr[0x74] >> 7 & 1) == 0) && (bVar2)) {
    // Weapon is holstered (bit 7 clear) and player is blocked
    cVar3 = FUN_007fd640(); // check if can holster
    if (cVar3 != '\0') {
      cVar3 = FUN_007f7c50(); // recheck vehicle state
      if (cVar3 == '\0') {
        FUN_007fcd60(); // holster weapon
      }
    }
    cVar3 = FUN_007cbc10(1); // check weapon equipped
    if (cVar3 != '\0') {
      thisPtr[0x74] = thisPtr[0x74] | 0x40; // set bit 6
      return;
    }
    thisPtr[0x74] = thisPtr[0x74] & 0xffffffbf; // clear bit 6
  }
  return;
}