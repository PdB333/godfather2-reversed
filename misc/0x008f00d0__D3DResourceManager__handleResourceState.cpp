// FUNC_NAME: D3DResourceManager::handleResourceState
char __thiscall D3DResourceManager::handleResourceState(int this, int *resourceData, uint *hashInput, undefined4 unkParam4, int unkParam5)
{
  uint uVar1;
  uint uVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int *piVar9;
  int *piVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  longlong lVar13;
  undefined4 local_3c;
  undefined4 local_38;
  uint local_34;
  undefined4 local_30;
  int local_c [3];
  
  // Magic constants for identification
  local_3c = 0xbadbadba;
  local_38 = 0xbeefbeef;
  local_34 = 0xeac15a55;
  local_30 = 0x91100911;
  
  // Check if resource data is zero (empty handle)
  if ((((*resourceData == 0) && (resourceData[1] == 0)) && (resourceData[2] == 0)) && (resourceData[3] == 0)) {
    return '\0';
  }
  
  // Hash computation using __allmul (64-bit multiply)
  uVar1 = hashInput[2];
  uVar2 = hashInput[3];
  lVar13 = __allmul((ulonglong)*hashInput * 0x21 + (ulonglong)hashInput[1], 0x21, 0);
  iVar4 = __allmul(lVar13 + (ulonglong)uVar1, 0x21, 0);
  iVar8 = DAT_0122337c;
  iVar4 = iVar4 + uVar2;
  hashInput = (uint *)iVar4;
  
  // Query resource states
  iVar5 = FUN_004059b0(iVar4);  // getResourceType
  iVar6 = FUN_008ecbc0(iVar4);  // getResourceNode
  iVar7 = FUN_004025a0(iVar5);  // getResourceObject
  if ((iVar7 == 0) || (*(int *)(iVar7 + 0x24) != 3)) {  // +0x24 = resource state
    if (iVar5 == 0) goto LAB_008f027e;
    if (*(int *)(iVar8 + 0x84) == 0) {  // +0x84 = current context
      iVar8 = 0;
    }
    else {
      iVar8 = *(int *)(*(int *)(iVar8 + 0x84) + 0x1c);  // +0x1c = context state
    }
    if (iVar5 != iVar8) goto LAB_008f027e;
  }
  
  // Handle loading state (state < 3 = loading)
  if ((iVar6 != 0) && (*(int *)(iVar6 + 8) < 3)) {  // +0x8 = node state
    cVar3 = FUN_008ef8a0(unkParam4, 0);  // checkResourceLoading
    iVar8 = unkParam5;
    if (cVar3 == '\0') {
      return '\0';
    }
    *(undefined4 *)(iVar6 + 8) = 2;  // Set state to loading
    FUN_00408bf0();  // markResourceDirty
    local_3c = DAT_0112fdf8;
    local_38 = 0;
    local_34 = local_34 & 0xffffff00;
    if (iVar8 != 0) {
      FUN_00408bf0();
      return cVar3;
    }
    FUN_00408bf0();
    return cVar3;
  }
  
LAB_008f027e:
  // Check for cached or pending resources
  iVar8 = FUN_008ecc20(iVar4);  // getCachedResource
  if ((iVar8 != 0) || (iVar8 = FUN_008ecc80(iVar4), uVar11 = unkParam4, iVar8 != 0)) {  // getPendingResource
    uVar11 = unkParam4;
    cVar3 = FUN_008ef8a0(unkParam4, iVar8);  // checkResourceAvailable
    if (cVar3 == '\0') {
      return '\0';
    }
    piVar9 = (int *)FUN_008ecc20(iVar4);  // getCachedResource
    if (piVar9 == (int *)0x0) {
      piVar9 = (int *)FUN_008ecc80(iVar4);  // getPendingResource
    }
    iVar8 = FUN_009c8e50(0x2c);  // allocateResourceNode (size 0x2c)
    if (iVar8 == 0) {
      piVar10 = (int *)0x0;
    }
    else {
      piVar10 = (int *)FUN_008eac00(&local_3c, 0, uVar11, unkParam5);  // createResourceNode
    }
    *piVar10 = *piVar9;
    piVar10[1] = 0;
    if (*piVar9 != 0) {
      *(int **)(*piVar9 + 4) = piVar10;
      *piVar9 = (int)piVar10;
      return cVar3;
    }
    piVar9[1] = (int)piVar10;
    *piVar9 = (int)piVar10;
    return cVar3;
  }
  
  // Default path - create new resource
  cVar3 = FUN_008efbf0();  // createNewResource
  iVar8 = unkParam5;
  if (cVar3 == '\0') {
    return '\0';
  }
  if (iVar6 != 0) {
    // Handle existing resource node states
    if (*(int *)(iVar6 + 8) == 3) {  // State: created
      *(undefined4 *)(iVar6 + 8) = 2;  // Set to loading
      local_3c = DAT_0112fddc;
      local_38 = 0;
      local_34 = local_34 & 0xffffff00;
      FUN_00408bf0();
      if (iVar8 != 0) {
        FUN_00408bf0();
        return '\x01';
      }
      FUN_00408bf0();
      return '\x01';
    }
    if (*(int *)(iVar6 + 8) == 4) {  // State: ready
      uVar11 = FUN_008eac00(&local_3c, 0, uVar11, unkParam5);  // createResourceNode
      FUN_008ef410(iVar6, iVar4, 0, uVar11);  // attachResourceNode
      if (local_c[0] != 0) {
        FUN_004daf90(local_c);  // cleanupNode
        return '\x01';
      }
      return '\x01';
    }
    return '\x01';
  }
  
  // Handle resource pool limits
  if (*(uint *)(this + 0x18) <= *(uint *)(this + 0x14)) {  // +0x18 = poolCount, +0x14 = maxPool
    FUN_008ef250(&hashInput);  // evictOldestResource
    iVar8 = FUN_009c8e50(0x2c);  // allocateResourceNode
    if (iVar8 != 0) {
      uVar11 = FUN_008eac00(&local_3c, 0, uVar11, unkParam5);  // createResourceNode
      FUN_008eb500(uVar11);  // addResource
      return '\x01';
    }
    FUN_008eb500(0);
    return '\x01';
  }
  
  // Normal path - create and attach new resource
  uVar12 = FUN_008ef150(&hashInput);  // findResourceSlot
  uVar11 = FUN_008eac00(&local_3c, 0, uVar11, unkParam5);  // createResourceNode
  FUN_008ef410(uVar12, iVar4, 0, uVar11);  // attachResourceNode
  if (local_c[0] != 0) {
    FUN_004daf90(local_c);
    return '\x01';
  }
  return '\x01';
}