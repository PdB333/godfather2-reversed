// FUNC_NAME: PlayerSM::updateState
void __fastcall PlayerSM::updateState(int this)
{
  char cVar1;
  uint uVar2;
  int *piVar3;
  float10 fVar4;
  
  cVar1 = FUN_00778fd0(); // likely isPlayerInVehicle or similar
  if ((*(uint *)(this + 0x90) >> 4 & 1) == 0) {
    *(uint *)(this + 0x90) = *(uint *)(this + 0x90) | 0x22; // set flags 0x20 and 0x02 (maybe "in air" and "jumping")
    return;
  }
  if ((*(int *)(this + 0x88) != 0) && (*(int *)(this + 0x88) != 0x48)) {
    if (*(int *)(this + 0x88) == 0) {
      piVar3 = (int *)0x0;
    }
    else {
      piVar3 = (int *)(*(int *)(this + 0x88) + -0x48); // get base object from offset -0x48
    }
    fVar4 = (float10)(**(code **)(*piVar3 + 0x1a8))(); // virtual call at vtable+0x1a8 (likely getSpeed or getVelocity)
    if ((float10)_DAT_00d6835c < fVar4) { // compare with some threshold (maybe max speed)
      *(uint *)(this + 0x90) = *(uint *)(this + 0x90) | 4; // set flag 0x04 (maybe "moving fast")
      if (cVar1 == '\\0') {
        return;
      }
      DAT_012054b4 = DAT_012054b4 + 1; // increment some global counter
      return;
    }
  }
  *(uint *)(this + 0x90) = *(uint *)(this + 0x90) | 2; // set flag 0x02 (maybe "jumping")
  uVar2 = DAT_010c2678 & DAT_012054b4; // bitwise AND with global counter
  DAT_012054b4 = DAT_012054b4 + 1;
  if (DAT_00d68368 < *(float *)(&DAT_010c2680 + uVar2 * 4) ||
      DAT_00d68368 == *(float *)(&DAT_010c2680 + uVar2 * 4)) { // compare with some array value
    if (*(int *)(this + 0x88) == 0) {
      piVar3 = (int *)0x0;
    }
    else {
      piVar3 = (int *)(*(int *)(this + 0x88) + -0x48);
    }
    (**(code **)(*piVar3 + 0x298))(); // virtual call at vtable+0x298 (likely performJump or similar)
    return;
  }
  *(uint *)(this + 0x90) = *(uint *)(this + 0x90) | 0x20; // set flag 0x20 (maybe "in air")
  return;
}