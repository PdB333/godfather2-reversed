// FUNC_NAME: PlayerF2FSM::handleF2FState
void __thiscall PlayerF2FSM::handleF2FState(int *this, char *param_2)
{
  char cVar1;
  int iVar2;
  float10 fVar3;
  
  if (this[0xba] != 0) {
    if (*param_2 != '\0') {
      if ((*(uint *)(this[0xd8] + 0x110) >> 1 & 1) == 0) {
        FUN_0055d950(); // likely startF2FAnimation or similar
      }
      *(uint *)(this[0xd8] + 0x110) = *(uint *)(this[0xd8] + 0x110) | 2;
      if (((((uint)this[0x286] >> 3 & 1) != 0) || (cVar1 = FUN_0087ae60(), cVar1 != '\0')) ||
         (iVar2 = FUN_00544b70(), iVar2 == 0)) {
        FUN_00544ae0(this[0x3a1]); // setF2FState or transition
      }
      FUN_009f4240(1,1,0); // likely setF2FInput or lockControls
      return;
    }
    fVar3 = (float10)(**(code **)(*this + 0xc0))(); // getF2FTimer or similar
    if (fVar3 <= (float10)0) {
      FUN_0087a9b0(); // likely endF2FState
LAB_0087d4b2:
      FUN_004088c0(this + 0xf); // clearF2FInput or reset
      return;
    }
    *(uint *)(this[0xd8] + 0x110) = *(uint *)(this[0xd8] + 0x110) & 0xfffffffd;
    cVar1 = FUN_0087cb30(); // checkF2FCancelCondition
    if (cVar1 == '\0') {
      cVar1 = (**(code **)(*this + 0x2a4))(); // checkF2FInput
      if ((cVar1 != '\0') && (((uint)this[0x322] >> 2 & 1) == 0)) goto LAB_0087d4b2;
      if ((((uint)this[0x286] >> 3 & 1) != 0) && (iVar2 = FUN_00544b70(), iVar2 != 2)) {
        this[0x3a1] = iVar2;
        FUN_00544ae0(2); // setF2FState(2)
        return;
      }
    }
    else {
      iVar2 = FUN_00544b70();
      if (iVar2 != 0) {
        FUN_009f4240(1,1,0);
        this[0x3a1] = iVar2;
        FUN_00544ae0(0); // setF2FState(0)
      }
    }
  }
  return;
}