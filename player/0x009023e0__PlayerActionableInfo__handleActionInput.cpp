// FUNC_NAME: PlayerActionableInfo::handleActionInput
void __thiscall PlayerActionableInfo::handleActionInput(int thisPtr, int *actionParams)
{
  float fVar1;
  int iVar2;
  char cVar3;
  int iVar4;
  undefined4 uVar5;
  uint uVar6;
  undefined4 uVar7;
  undefined4 local_c;
  int local_8;
  undefined1 local_4;
  
  FUN_0046c6a0(actionParams); // likely some input validation or preprocessing
  iVar2 = DAT_01205224; // global time or frame counter
  if ((*actionParams == *(int *)(thisPtr + 0x1c)) && // action type matches current state?
     ((*(short *)(thisPtr + 0x18) != 0 || ((*(uint *)(thisPtr + 0x14) & 0xffff0000) != 0)))) { // some flags check
    iVar4 = *(int *)(thisPtr + 0x30); // last action timestamp
    if ((iVar4 != 0) && (DAT_01205224 != iVar4)) {
      fVar1 = (float)(DAT_01205224 - iVar4);
      if (DAT_01205224 - iVar4 < 0) {
        fVar1 = fVar1 + DAT_00e44578; // wrap-around for unsigned time
      }
      if (fVar1 * DAT_00d5efb8 < *(float *)(thisPtr + 0x2c)) { // cooldown check
        return;
      }
    }
    if ((((actionParams[1] != 0) && (iVar4 = *(int *)(actionParams[1] + 4), iVar4 != 0)) && // action target exists
        (iVar4 = iVar4 + -0x48, iVar4 != 0)) && (iVar4 = FUN_006c9470(iVar4,0x383225a1), iVar4 != 0) // hash lookup for action type
       ) {
      if ((*(uint *)(thisPtr + 0x14) & 0xffff0000) == 0) { // check if action is not a special type
        uVar6 = (uint)*(ushort *)(thisPtr + 0x18); // some index
        uVar7 = 1;
        uVar5 = (**(code **)(*(int *)(iVar4 + 0x1f30) + 8))(uVar6,1); // get action data
        cVar3 = FUN_004103b0(uVar5,uVar6,uVar7); // validate action
      }
      else {
        cVar3 = FUN_00902330(); // special action handling
      }
      if (cVar3 != '\0') {
        local_c = *(undefined4 *)(thisPtr + 0x24); // action context
        local_8 = actionParams[1]; // action target
        local_4 = 0;
        FUN_00408a00(&local_c,0); // execute action
        *(int *)(thisPtr + 0x30) = iVar2; // update last action timestamp
      }
    }
  }
  return;
}