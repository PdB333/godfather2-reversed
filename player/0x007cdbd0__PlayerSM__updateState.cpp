// FUNC_NAME: PlayerSM::updateState
void __fastcall PlayerSM::updateState(int *this)
{
  code *pcVar1;
  bool bVar2;
  char cVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  undefined4 local_4;
  
  // Check if current state is valid (non-zero and not 0x48 = 72)
  if ((this[0x6d] != 0) && (this[0x6d] != 0x48)) {
    iVar4 = this[0x16]; // +0x58 - player object pointer
    cVar3 = FUN_007f7c50(); // likely isPlayerDead() or similar
    if ((cVar3 == '\0') &&
       (((*(uint *)(iVar4 + 0x24a0) >> 5 & 1) == 0 && ((*(byte *)(iVar4 + 0x8e4) & 1) == 0)))) {
      bVar2 = false;
    }
    else {
      bVar2 = true;
    }
    // Check if bit 7 of flags at +0x1D0 is set, and if bVar2 is true
    if ((((uint)this[0x74] >> 7 & 1) == 0) || (bVar2)) {
      // If bit 7 is not set and bVar2 is true
      if ((((uint)this[0x74] >> 7 & 1) == 0) && (bVar2)) {
        cVar3 = FUN_007fd640(); // likely isInVehicle()
        if ((cVar3 != '\0') && (cVar3 = FUN_007f7c50(), cVar3 == '\0')) {
          FUN_007fcd60(); // likely exitVehicle()
        }
        cVar3 = FUN_007cbc10(1); // likely canEnterCover()
        if (cVar3 != '\0') {
          this[0x74] = this[0x74] | 0x40; // set bit 6 of flags
          return;
        }
        this[0x74] = this[0x74] & 0xffffffbf; // clear bit 6 of flags
      }
    }
    else {
      // Bit 7 is set and bVar2 is false - entering cover state
      if (this[0x6d] == 0) {
        iVar4 = 0;
      }
      else {
        iVar4 = this[0x6d] + -0x48; // subtract state offset
      }
      iVar4 = *(int *)(iVar4 + 0x1f3c); // get some data from state
      this[0x6f] = iVar4; // store at +0x1BC
      if (iVar4 != 0) {
        iVar4 = this[0x68] * 0x2c + *(int *)(*(int *)(this[0x70] + 0x10) + 4); // calculate animation index
        uVar6 = 0x40084;
        local_4 = 0;
        if ((iVar4 != 0) &&
           (iVar4 = FUN_007cae60(*(undefined4 *)(iVar4 + 0x14),*(undefined2 *)((int)this + 0x1d6)
                                ), iVar4 != 0)) {
          local_4 = *(undefined4 *)(iVar4 + 8);
          uVar6 = *(undefined4 *)(iVar4 + 4);
        }
        FUN_007cbfa0(uVar6,local_4); // likely playAnimation()
        FUN_007cc310(1); // likely setAnimationSpeed()
        if (this[0x6d] == 0) {
          iVar4 = 0;
        }
        else {
          iVar4 = this[0x6d] + -0x48;
        }
        if (*(char *)(iVar4 + 0x1b8c) != '\0') {
          puVar5 = (undefined4 *)FUN_007ab160(); // likely getAudioManager()
          (**(code **)*puVar5)(0x80); // play sound 0x80
          puVar5 = (undefined4 *)FUN_007ab160();
          (**(code **)*puVar5)(1); // play sound 1
        }
        FUN_007cb110(*(uint *)(*(int *)(*(int *)(this[0x70] + 0x10) + 4) + 0x24 +
                              this[0x68] * 0x2c) >> 7 & 0xffffff01); // update animation state
        pcVar1 = *(code **)(*this + 0x2c); // vtable + 0x2C = some update method
        this[0x73] = 0x46f5c7b4; // set some timer/state value
        (*pcVar1)(0x46f5c7b4,1,1,0,0x3f800000,0x3f800000); // call update with parameters
        return;
      }
    }
  }
  return;
}