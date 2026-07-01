// FUNC_NAME: CameraManager::updateCameraTransform
void __thiscall CameraManager::updateCameraTransform(int *this, float *position, float *rotation, undefined4 param4)
{
  float fVar1;
  float fVar2;
  bool bVar3;
  char cVar4;
  float *pfVar5;
  int iVar6;
  float *pfVar7;
  float10 fVar8;
  double dVar9;
  float fStack_5c;
  float local_58;
  float fStack_54;
  float local_50 [4];
  undefined8 local_40;
  undefined4 local_38;
  undefined8 local_30;
  float local_28;
  
  FUN_00544d10(position);
  if (((uint)this[0x322] >> 0xc & 1) == 0) {
    FUN_00868d70(param4,1,rotation);
  }
  else {
    pfVar5 = (float *)FUN_00471610();
    fVar1 = rotation[2];
    fVar2 = rotation[1];
    local_28 = rotation[2];
    local_50[0] = fVar1 - fVar2 * 0.0;
    pfVar7 = local_50;
    for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
      *pfVar7 = *pfVar5;
      pfVar5 = pfVar5 + 1;
      pfVar7 = pfVar7 + 1;
    }
    local_50[2] = fVar2 * 0.0 - *rotation;
    local_38 = DAT_00d75698;
    local_40 = DAT_00d75690;
    local_30 = *(undefined8 *)rotation;
    local_50[1] = *rotation * 0.0 - fVar1 * 0.0;
    (**(code **)(*this + 0x28))(local_50);
  }
  if (this[0x3cb] != 1) {
    fVar1 = (float)this[0x3f1];
    fVar2 = (float)this[0x452];
    local_58 = position[1];
    if (fVar1 == _DAT_00d577a0) {
      fStack_5c = *position;
      fStack_54 = position[2];
    }
    else {
      dVar9 = (double)fVar2;
      FUN_00b99e20();
      fStack_5c = *position - (float)dVar9 * fVar1;
      dVar9 = (double)fVar2;
      FUN_00b99fcb();
      fStack_54 = (float)dVar9 * fVar1 + position[2];
    }
    if ((0 < this[0x3f4]) && (cVar4 = FUN_00860fa0(&fStack_5c), cVar4 != '\0')) {
      this[0x3f4] = 0;
      fVar8 = (float10)FUN_0085ec00(0,this[0x3f5] & 0x7fffffff,(uint)this[0x3f5] >> 0x1f);
      fVar2 = (float)fVar8;
      this[0x3f1] = (int)(float)fVar8;
      bVar3 = fVar2 == _DAT_00d577a0;
      this[0x3f2] = (int)(float)fVar8;
      fVar1 = (float)this[0x452];
      local_58 = position[1];
      if (bVar3) {
        fStack_5c = *position;
        fStack_54 = position[2];
      }
      else {
        dVar9 = (double)fVar1;
        FUN_00b99e20();
        fStack_5c = *position - (float)dVar9 * fVar2;
        dVar9 = (double)fVar1;
        FUN_00b99fcb();
        fStack_54 = (float)dVar9 * fVar2 + position[2];
      }
    }
    FUN_00544d10(&fStack_5c);
    this[0x3ca] = this[0x3ca] & 0xffff7fff;
  }
  return;
}