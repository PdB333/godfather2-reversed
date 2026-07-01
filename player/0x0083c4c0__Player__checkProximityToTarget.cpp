// FUNC_NAME: Player::checkProximityToTarget
undefined4 __thiscall Player::checkProximityToTarget(int this, int *targetEntity, float *targetPos, float maxDistSq, float minDistSq)
{
  int *piVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  int unaff_EBX;
  float fVar5;
  float fVar6;
  float fVar7;
  
  piVar1 = targetEntity;
  iVar3 = FUN_00471610(); // likely getPlayerPosition or getPlayerTransform
  fVar5 = *(float *)(iVar3 + 0x30) - *targetPos; // playerPos.x - targetPos.x
  fVar6 = *(float *)(iVar3 + 0x34) - targetPos[1]; // playerPos.y - targetPos.y
  fVar7 = *(float *)(iVar3 + 0x38) - targetPos[2]; // playerPos.z - targetPos.z
  targetPos = (float *)(CONCAT31(targetPos._1_3_,(char)(*(uint *)(this + 0xa8) >> 0x12)) & 0xffffff01
                     );
  targetEntity = (int *)(fVar7 * fVar7 + fVar6 * fVar6 + fVar5 * fVar5); // distanceSq
  cVar2 = FUN_006c0050(iVar3 + 0x30,1,targetPos); // likely checkLineOfSight or checkVisibility
  if (cVar2 == '\0') {
    if (minDistSq < (float)targetEntity) {
      return 1; // too close, return true
    }
  }
  else if (maxDistSq < (float)targetEntity) {
    return 1; // too far, return true
  }
  targetEntity = (int *)0x0;
  cVar2 = (**(code **)(*piVar1 + 0x10))(0x369ac561,&targetEntity); // virtual call on target entity
  if (((cVar2 == '\0') || (unaff_EBX == 0)) ||
     (uVar4 = 1, (*(uint *)(unaff_EBX + 0x1f58) >> 0x19 & 1) == 0)) {
    uVar4 = 0;
  }
  return uVar4;
}