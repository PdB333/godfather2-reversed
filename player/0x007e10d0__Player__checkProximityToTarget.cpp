// FUNC_NAME: Player::checkProximityToTarget
bool __thiscall Player::checkProximityToTarget(int this, int target)
{
  char cVar1;
  int iVar2;
  float10 fVar3;
  float local_3c;
  float local_38;
  float local_34;
  undefined8 local_30;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  if (((target != 0) && ((*(byte *)(target + 0x40) & 1) != 0)) && (*(char *)(target + 0x1e4) == '\0')) {
    iVar2 = FUN_00471610(); // getPlayerPosition or similar
    local_30 = *(undefined8 *)(iVar2 + 0x30); // player position (x, y)
    local_28 = *(float *)(iVar2 + 0x38); // player position z
    FUN_009a8320(&local_18,&local_30); // transform or copy position
    local_24 = local_18 - (float)local_30; // delta x
    local_20 = local_14 - local_30._4_4_; // delta y
    local_1c = local_10 - local_28; // delta z
    iVar2 = FUN_00471610(); // get player again
    fVar3 = (float10)FUN_004a10f0(iVar2 + 0x20,&local_24,&DAT_00d6f960); // dot product or distance calculation
    if (fVar3 < (float10)0) {
      iVar2 = FUN_00471610();
      fVar3 = (float10)FUN_004a10f0(iVar2 + 0x20,&local_24,&DAT_00d6f960);
      fVar3 = -fVar3;
    }
    else {
      iVar2 = FUN_00471610();
      fVar3 = (float10)FUN_004a10f0(iVar2 + 0x20,&local_24,&DAT_00d6f960);
    }
    if ((float)fVar3 < *(float *)(target + 0x1e0) * DAT_00e445c8) {
      FUN_009a8830(*(undefined4 *)(this + 0x58),&local_3c,&local_c,_DAT_00e533dc); // get target position
      if (SQRT((local_28 - local_34) * (local_28 - local_34) +
               (local_30._4_4_ - local_38) * (local_30._4_4_ - local_38) +
               ((float)local_30 - local_3c) * ((float)local_30 - local_3c)) <
          *(float *)(target + 0x1dc)) {
        cVar1 = *(char *)(*(int *)(this + 0x58) + 0x1b8c); // some flag on target
        target = CONCAT31((int3)((uint)(float)fVar3 >> 8),cVar1);
        if (cVar1 != '\0') {
          fVar3 = (float10)FUN_007fd880(target,0); // get some offset
          fVar3 = -fVar3;
          local_3c = (float)((float10)local_c * fVar3 + (float10)local_3c);
          local_38 = (float)((float10)local_8 * fVar3 + (float10)local_38);
          local_34 = (float)(fVar3 * (float10)local_4 + (float10)local_34);
        }
        cVar1 = FUN_0080e650(&local_3c,&local_30,1,0); // line of sight check
        return cVar1 == '\0';
      }
    }
  }
  return false;
}