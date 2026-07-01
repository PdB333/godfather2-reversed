// FUNC_NAME: Entity::checkVisibilityInFrustum
bool __thiscall Entity::checkVisibilityInFrustum(int this, float *frustumPlanes)
{
  int iVar1;
  int iVar3;
  int *piVar4;
  int iStack_3c;
  int aiStack_38 [2];
  float local_30;
  float local_2c;
  float local_28;
  float local_20;
  float local_1c;
  float local_18;
  
  // +0xD4: bounding sphere radius
  local_18 = *(float *)(this + 0xd4);
  // Compute AABB from frustum planes expanded by bounding sphere radius
  local_30 = *frustumPlanes - local_18;
  local_20 = local_18 + *frustumPlanes;
  local_1c = frustumPlanes[1] + local_18;
  local_2c = frustumPlanes[1] - local_18;
  local_28 = frustumPlanes[2] - local_18;
  local_18 = frustumPlanes[2] + local_18;
  
  // +0xD8: pointer to a spatial query structure (octree node?)
  if (*(int *)(this + 0xd8) == 0) {
    TlsGetValue(DAT_01139810);
    iVar1 = FUN_00aa2680(0xd0, 0x31);
    *(undefined2 *)(iVar1 + 4) = 0xd0;
    uVar2 = FUN_00540c60(0xb, 0x1f, 0);
    iVar1 = FUN_009f59e0(&local_30, uVar2);
    *(int *)(this + 0xd8) = iVar1;
    if ((iVar1 != 0) && (*(int *)(iVar1 + 8) == 0)) {
      FUN_009e7450(iVar1);
    }
  }
  else {
    FUN_009f5240(&local_30);
  }
  
  // +0xD8: pointer to spatial query result (octree node list)
  iVar1 = *(int *)(*(int *)(this + 0xd8) + 0xc4);
  if (0 < iVar1) {
    piVar4 = *(int **)(*(int *)(this + 0xd8) + 0xc0);
    iStack_3c = iVar1;
    do {
      iVar3 = *piVar4;
      if ((iVar3 != 0) && (*(char *)(iVar3 + 0x10) + iVar3 != 0)) {
        FUN_004af8c0(aiStack_38, 0x2001);
        iVar3 = 0;
        if (aiStack_38[0] != 0) {
          iVar3 = aiStack_38[0];
        }
        if ((iVar3 != 0) && (*(char *)(iVar3 + 0x15e) < '\0')) {
          iVar1 = iVar1 + -1;
        }
      }
      piVar4 = piVar4 + 1;
      iStack_3c = iStack_3c + -1;
    } while (iStack_3c != 0);
  }
  return 0 < iVar1;
}