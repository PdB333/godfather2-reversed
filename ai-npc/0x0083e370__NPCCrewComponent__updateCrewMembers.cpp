// FUNC_NAME: NPCCrewComponent::updateCrewMembers
int __thiscall NPCCrewComponent::updateCrewMembers(int this, float param_2)
{
  int iVar1;
  int iVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  float10 fVar6;
  float fVar7;
  float local_18;
  float local_14;
  undefined1 local_10 [4];
  undefined1 local_c [12];
  
  iVar4 = FUN_0083de60(); // getCrewMemberCount
  iVar2 = (int)param_2;
  if (iVar4 < (int)param_2) {
    fVar6 = (float10)FUN_0083d270(local_10,&local_14,&param_2,&local_18,local_c,0); // some distance/angle calculation
    param_2 = *(float *)(this + 0x6c) - (float)fVar6; // this->somePositionOffset
    param_2 = param_2 * param_2;
    if (param_2 < local_18) {
      param_2 = local_18;
    }
    local_14 = local_14 + _DAT_00d743fc; // global time delta
    iVar1 = *(int *)(this + 0x98); // crew member count
    do {
      do {
        iVar1 = iVar1 + -1;
        if (iVar1 < 0) goto LAB_0083e459;
        iVar5 = *(int *)(*(int *)(this + 0x94) + iVar1 * 8); // crew member array (+0x94)
        if (iVar5 == 0) {
          iVar5 = 0;
        }
        else {
          iVar5 = iVar5 + -0x48; // offset to NPC object
        }
      } while ((*(int *)(iVar5 + 0x158) != 0) || // check if member is busy
              (cVar3 = FUN_0083c4c0(iVar5,local_c,param_2,local_14), cVar3 == '\0')); // check if member can be assigned
      FUN_0083dea0(iVar1,0); // assign member to task
      iVar4 = iVar4 + 1;
    } while (iVar4 < iVar2);
  }
LAB_0083e459:
  if ((0 < iVar4) && ((*(byte *)(this + 0xa8) & 1) != 0)) { // check flag
    fVar7 = *(float *)(this + 0x70); // some speed/cooldown value
    if (((*(uint *)(this + 0xa8) & 0x18000) != 0) &&
       ((fVar7 < *(float *)(this + 0x74) && ((*(uint *)(this + 0xa8) >> 0x10 & 1) != 0)))) {
      fVar7 = (*(float *)(this + 0x74) + fVar7) - fVar7; // clamp or adjust
    }
    *(float *)(this + 0xa0) = fVar7; // update cooldown timer
  }
  return iVar4;
}