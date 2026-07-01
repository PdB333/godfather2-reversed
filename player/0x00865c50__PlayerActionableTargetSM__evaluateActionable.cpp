// FUNC_NAME: PlayerActionableTargetSM::evaluateActionable
undefined1 __thiscall PlayerActionableTargetSM::evaluateActionable(int this, int targetEntity, undefined8 *hitPosition, int actionType, undefined8 *targetForward)
{
  char cVar1;
  uint uVar2;
  int iVar3;
  float10 fVar4;
  float10 extraout_ST0;
  undefined1 result;
  
  result = 0;
  if ((((targetEntity != 0) && (hitPosition != (undefined8 *)0x0)) && (actionType != 0)) &&
     (targetForward != (undefined8 *)0x0)) {
    cVar1 = FUN_00865300(targetEntity, hitPosition, actionType, targetForward);
    uVar2 = FUN_0085f630(actionType);
    if (((uVar2 & 2) == 0) || (cVar1 == '\0')) {
      result = 0;
    }
    else {
      // Set flag 0x2000000 on the action flags
      *(uint *)(this + 0xf28) = *(uint *)(this + 0xf28) | 0x2000000;
      // Copy hit position to this+0xfe0
      *(undefined8 *)(this + 0xfe0) = *hitPosition;
      *(undefined4 *)(this + 0xfe8) = *(undefined4 *)(hitPosition + 1);
      // Copy target forward to this+0xffc
      *(undefined8 *)(this + 0xffc) = *targetForward;
      *(undefined4 *)(this + 0x1004) = *(undefined4 *)(targetForward + 1);
      iVar3 = FUN_00471610(); // likely getAnimController or similar
      fVar4 = (float10)FUN_0045c4b0(iVar3 + 0x30, (undefined8 *)(this + 0xffc)); // dot product or angle
      *(float *)(this + 0xff8) = (float)fVar4;
      result = 1;
    }
    if ((uVar2 & 1) != 0) {
      // Set flag 0x4000000 on the action flags
      *(uint *)(this + 0xf28) = *(uint *)(this + 0xf28) | 0x4000000;
      // Clear flag 0x2000000
      *(uint *)(this + 0xf28) = *(uint *)(this + 0xf28) & 0xfdffffff;
      // Copy hit position to this+0xfe0
      *(undefined8 *)(this + 0xfe0) = *hitPosition;
      *(undefined4 *)(this + 0xfe8) = *(undefined4 *)(hitPosition + 1);
      // Copy target forward to this+0xffc
      *(undefined8 *)(this + 0xffc) = *targetForward;
      *(undefined4 *)(this + 0x1004) = *(undefined4 *)(targetForward + 1);
      FUN_0045c4b0((undefined8 *)(this + 0xfe0), (undefined8 *)(this + 0xffc)); // compute distance or angle
      *(float *)(this + 0xff8) = (float)extraout_ST0;
      return 1;
    }
  }
  return result;
}