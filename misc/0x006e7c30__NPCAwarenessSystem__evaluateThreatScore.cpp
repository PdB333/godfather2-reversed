// FUNC_NAME: NPCAwarenessSystem::evaluateThreatScore
undefined1 FUN_006e7c30(float param_1,undefined4 *param_2,float *param_3)

{
  int iVar1;
  float *pfVar2;
  int iVar3;
  char cVar4;
  float10 fVar5;
  float fVar6;
  float fVar7;
  undefined1 local_1d;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  iVar3 = (int)param_1;
  local_1d = 0;
  if ((((param_1 != 0.0) && ((*(byte *)(param_2 + 10) & *(byte *)((int)param_1 + 0x88)) != 0)) &&
      (cVar4 = FUN_006e7110(param_2[7]), cVar4 != '\0')) &&
     ((*(byte *)((int)param_1 + 0x8a) & 8) != 0)) {
    pfVar2 = (float *)param_2[3];
    local_14 = *(float *)((int)param_1 + 0x48) - pfVar2[1];
    local_10 = *(float *)((int)param_1 + 0x4c) - pfVar2[2];
    local_18 = *(float *)((int)param_1 + 0x44) - *pfVar2;
    iVar1 = (int)param_1 + 0x44;
    fVar6 = local_10 * local_10 + local_14 * local_14 + local_18 * local_18;
    if ((fVar6 < (float)param_2[0xb]) && ((float)param_2[0xc] <= fVar6)) {
      pfVar2 = (float *)param_2[5];
      fVar7 = pfVar2[1] * local_14 + *pfVar2 * local_18 + pfVar2[2] * local_10;
      param_1 = 0.0;
      if ((fVar7 <= 0.0) || (fVar7 <= (float)param_2[0xd] - DAT_00e445ac)) {
        fVar5 = (float10)FUN_006b6f90(0x3f800000);
        *param_3 = (float)ABS((float10)fVar6 - fVar5 * (float10)(float)param_2[0xf]);
        cVar4 = FUN_00690150(0x2e);
        if ((cVar4 != '\0') || (cVar4 = FUN_00717d00(), cVar4 != '\0')) {
          fVar5 = (float10)FUN_0045c470(param_2[4],iVar1);
          *param_3 = (float)(ABS(fVar5 - (float10)(float)param_2[0xf]) + (float10)*param_3);
          FUN_0054ba20(&local_c,&local_18,0);
          pfVar2 = (float *)param_2[2];
          param_1 = (pfVar2[1] * local_8 + *pfVar2 * local_c + pfVar2[2] * local_4) * _DAT_00d5fb48;
        }
        cVar4 = FUN_006e5bb0(param_2[4]);
        if (cVar4 == '\0') {
          param_1 = DAT_0112a9a8 + param_1;
        }
        *param_3 = *param_3 + param_1;
        cVar4 = (**(code **)*param_2)(iVar3);
        if (cVar4 != '\0') {
          *param_3 = *param_3 + _DAT_0112a9ac;
        }
        if ((((*param_3 <= (float)param_2[0xe] && (float)param_2[0xe] != *param_3) &&
             (cVar4 = FUN_006e7470(param_2[7]), cVar4 != '\0')) &&
            (cVar4 = FUN_00718d40(iVar1), cVar4 != '\0')) &&
           (cVar4 = FUN_006e7a40(iVar3,param_2[8],param_2[9]), cVar4 == '\0')) {
          local_1d = 1;
        }
      }
    }
  }
  return local_1d;
}