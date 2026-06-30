// FUNC_NAME: UIHudMinimapMarkerManager::renderMarker

undefined4 __thiscall UIHudMinimapMarkerManager::renderMarker(int pMarkerData, int pTransform, int pTexture, float *pParams, undefined4 arg5, undefined4 arg6)
{
  bool bVar1;
  undefined1 uVar2;
  int in_EAX;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  uint uVar7;
  float fVar8;
  float fVar9;
  undefined4 local_70;
  int local_6c;
  int local_68;
  undefined4 local_64;
  int local_60;
  undefined4 local_5c;
  int local_58;
  undefined4 local_54;
  float local_50;
  float local_4c;
  undefined4 local_48;
  int local_44;
  float local_40;
  undefined4 local_3c;
  undefined4 local_38;
  int local_34;
  undefined1 local_30 [24];
  undefined1 local_18 [24];
  
  if (((in_EAX == 0) || (pMarkerData == 0)) || (pTexture == 0)) {
    return 0;
  }
  uVar7 = *(uint *)(pMarkerData + 4) & 0xff;
  if (uVar7 < 10) {
    iVar3 = *(int *)(pMarkerData + 0x24);
  }
  else {
    iVar3 = *(int *)(pMarkerData + 0x2c);
  }
  if (iVar3 == 0) {
    return 0;
  }
  if ((8 < uVar7) && (iVar3 = getSomeId(), iVar3 != *(short *)(pTransform + 0xb2))) {
    return 0;
  }
  iVar3 = getObjectFromManager(*(undefined4 *)(*(int *)(in_EAX + 4) + 4));
  local_68 = (int)*(short *)(pTransform + 0xb2);
  local_64 = 0;
  local_70 = 0;
  local_58 = 0;
  local_6c = iVar3;
  uVar2 = setupSomething(&local_64, &local_70, &local_58, iVar3 + 0x14, pTransform);
  *(undefined1 *)(iVar3 + 0x10) = uVar2;
  iVar3 = getGameState();
  bVar1 = false;
  if ((((iVar3 == 1) || (iVar3 == 3)) || (iVar3 == 4)) && (*(char *)(pParams + 4) == '\0')) {
    bVar1 = true;
  }
  local_50 = *pParams;
  uVar4 = createRenderObject();
  fVar8 = local_50;
  local_5c = uVar4;
  drawSomething(local_70, local_68);
  local_54 = DAT_012234e8;
  local_60 = checkAvailability();
  if (local_60 != 0) {
    pushRenderState();
    pushMatrix();
    popMatrix();
    popRenderState();
    restoreRenderState();
    return uVar4;
  }
  if (pParams[3] == DAT_00e2b05c) {
    pushRenderState();
    local_3c = local_70;
    local_38 = local_64;
    local_34 = local_68;
    local_48 = uVar4;
    local_44 = pMarkerData;
    local_40 = fVar8;
    copyTransform(local_18, uVar4);
    callCallback(arg6);
    restoreRenderState();
    return uVar4;
  }
  uVar5 = createRenderObject();
  uVar6 = createRenderObject();
  fVar8 = (float)(int)pParams[1];
  fVar9 = (float)(int)pParams[2];
  local_4c = fVar9;
  drawSomething(local_70, local_68);
  drawSomething(local_70, local_68);
  local_58 = checkAvailability();
  local_60 = checkAvailability();
  uVar4 = local_5c;
  if (local_58 == 0) {
    local_48 = uVar5;
    if (local_60 == 0) {
      if (bVar1) {
        pushRenderState();
        local_3c = local_70;
        local_34 = local_68;
        local_48 = uVar4;
        local_40 = local_50;
        local_38 = local_64;
        local_44 = pMarkerData;
        copyTransform(local_18, uVar4);
        callCallback(arg6);
        goto LAB_00594168;
      }
      copyTransform(&local_48, uVar5);
      pushRenderState();
      local_3c = local_70;
      local_38 = local_64;
      local_34 = local_68;
      local_44 = pMarkerData;
      local_40 = fVar8;
      callCallback(arg6);
      copyTransform(local_30, uVar6);
      pushRenderState();
      local_40 = local_4c;
      goto LAB_0059410e;
    }
    pushRenderState();
    pushMatrix();
    popMatrix();
    popRenderState();
    copyTransform(&local_48, uVar5);
    pushRenderState();
    local_3c = local_70;
    local_38 = local_64;
    local_34 = local_68;
    local_44 = pMarkerData;
    local_40 = fVar8;
    callCallback(arg6);
    fVar8 = pParams[3];
  }
  else if (local_60 == 0) {
    pushRenderState();
    pushMatrix();
    popMatrix();
    popRenderState();
    copyTransform(local_30, uVar6);
    pushRenderState();
    local_40 = fVar9;
LAB_0059410e:
    local_3c = local_70;
    local_38 = local_64;
    local_34 = local_68;
    local_48 = uVar6;
    local_44 = pMarkerData;
    callCallback(arg6);
    fVar8 = pParams[3];
  }
  else {
    pushRenderState();
    pushRenderState();
    pushMatrix();
    pushMatrix();
    popMatrix();
    popMatrix();
    popRenderState();
    popRenderState();
    fVar8 = pParams[3];
  }
  local_5c = someMathFunction(fVar8, arg5);
LAB_00594168:
  cleanupRender();
  cleanupRender();
  uVar4 = local_5c;
  restoreRenderState();
  return uVar4;
}