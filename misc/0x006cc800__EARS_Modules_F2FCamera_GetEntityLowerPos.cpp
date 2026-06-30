// Xbox PDB: EARS::Modules::F2FCamera::GetEntityLowerPos
// FUNC_NAME: CameraSystem::updateHeadLookAt
undefined8 * CameraSystem::updateHeadLookAt(int *this, float *outHeadTransform)
{
  char cVar1;
  int iVar2;
  undefined8 *puVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  char *pcVar7;
  float *pfStack_38;
  char *pcStack_34;
  float fVar8;
  float local_28 [5];
  undefined1 auStack_14 [4];
  float fStack_10;
  
  local_28[0] = 0.0;
  pcStack_34 = (char *)0x6cc818;
  iVar2 = FUN_00471610(); // GetFrameTime
  *(undefined8 *)outHeadTransform = *(undefined8 *)(iVar2 + 0x30);
  outHeadTransform[2] = *(float *)(iVar2 + 0x38);
  pcStack_34 = "eye_R";
  pfStack_38 = local_28;
  cVar1 = (**(code **)(*this + 0x94))(); // GetBoneWorldPosition
  if (cVar1 != '\0') {
    (**(code **)(*this + 0xa4))(auStack_14,&stack0xffffffd0); // GetBoneRotation
    fStack_10 = fStack_10 - outHeadTransform[1];
    if (fStack_10 < _DAT_00d5ca64) {
      fStack_10 = _DAT_00d5ca64;
    }
    outHeadTransform[1] = outHeadTransform[1] + fStack_10;
  }
  puVar3 = (undefined8 *)FUN_007f7c50(); // IsPlayerControlled
  if ((char)puVar3 == '\0') {
    return puVar3;
  }
  if ((char)this == '\0') {
    iVar2 = FUN_00471610(); // GetFrameTime
    *outHeadTransform = *outHeadTransform - *(float *)(iVar2 + 0x20) * _DAT_00d5cf70;
    iVar2 = FUN_00471610(); // GetFrameTime
    fVar6 = *(float *)(iVar2 + 0x28) * _DAT_00d5cf70;
    puVar3 = (undefined8 *)(iVar2 + 0x20);
  }
  else {
    pcVar7 = "m_neck1";
    puVar3 = (undefined8 *)(**(code **)(*this + 0x94))(&stack0xffffffd0); // GetBoneWorldPosition
    if ((char)puVar3 == '\0') {
      return puVar3;
    }
    (**(code **)(*this + 0xa4))(&pcStack_34,&pfStack_38); // GetBoneRotation
    fVar4 = (float)pcVar7 - *outHeadTransform;
    pfStack_38 = (float *)((float)pfStack_38 - outHeadTransform[1]);
    pcStack_34 = (char *)((float)pcStack_34 - outHeadTransform[2]);
    puVar3 = (undefined8 *)FUN_00471610(); // GetFrameTime
    fVar6 = DAT_00e510a0;
    local_28[0] = *(float *)(puVar3 + 1);
    fVar8 = (float)*puVar3;
    fVar5 = (float)((ulonglong)*puVar3 >> 0x20) * (float)pfStack_38 + fVar8 * fVar4 +
            local_28[0] * (float)pcStack_34;
    if (DAT_00e510a4 < fVar5) {
      local_28[0] = DAT_00e510a0 * local_28[0];
      *outHeadTransform = DAT_00e510a0 * fVar8 + *outHeadTransform;
      outHeadTransform[2] = local_28[0] + outHeadTransform[2];
      return puVar3;
    }
    if (DAT_00e44564 - DAT_00e510a4 <= fVar5) {
      iVar2 = FUN_00471610(); // GetFrameTime
      fVar6 = (float)*(undefined8 *)(iVar2 + 0x20);
      if ((float)((ulonglong)*(undefined8 *)(iVar2 + 0x20) >> 0x20) * (float)pfStack_38 +
          fVar6 * fVar4 + *(float *)(iVar2 + 0x28) * (float)pcStack_34 <= _DAT_00e5109c) {
        return (undefined8 *)(iVar2 + 0x20);
      }
      fVar4 = DAT_00e51098 * *(float *)(iVar2 + 0x28);
      *outHeadTransform = DAT_00e51098 * fVar6 + *outHeadTransform;
      outHeadTransform[2] = fVar4 + outHeadTransform[2];
      return (undefined8 *)(iVar2 + 0x20);
    }
    *outHeadTransform = *outHeadTransform - DAT_00e510a0 * fVar8;
    fVar6 = fVar6 * local_28[0];
  }
  outHeadTransform[2] = outHeadTransform[2] - fVar6;
  return puVar3;
}