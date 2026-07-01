// FUNC_NAME: EntityDataManager::applyEntityData
void __thiscall EntityDataManager::applyEntityData(int this, int *entityData)
{
  uint uVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  uint *puVar6;
  uint uVar7;
  uint local_14;
  undefined4 *local_10;
  uint local_c;
  uint local_4;
  
  iVar3 = DAT_0112999c; // gEntityDataManager
  if ((*entityData == *(int *)(this + 0x14)) && (DAT_0112999c != 0)) {
    local_14 = 0;
    *(undefined4 *)(DAT_0112999c + 0x14) = *(undefined4 *)(this + 0x1c); // +0x1c: entityType
    *(undefined4 *)(iVar3 + 0x20) = *(undefined4 *)(this + 0x3c); // +0x3c: some float
    *(undefined4 *)(iVar3 + 0x28) = *(undefined4 *)(this + 0x40); // +0x40: some float
    *(undefined4 *)(iVar3 + 0x54) = *(undefined4 *)(this + 0x24); // +0x24: some int
    *(undefined4 *)(iVar3 + 0x68) = *(undefined4 *)(this + 0x28); // +0x28: some int
    *(undefined4 *)(iVar3 + 0x7c) = *(undefined4 *)(this + 0x2c); // +0x2c: some int
    *(undefined4 *)(iVar3 + 0x90) = *(undefined4 *)(this + 0x30); // +0x30: some int
    iVar2 = DAT_01129904; // gEntityDataList
    piVar4 = (int *)(DAT_01129904 + 0x24); // +0x24: entityDataArray
    if (*(int *)(DAT_01129904 + 0x28) != 0) { // +0x28: entityDataCount
      do {
        uVar1 = *(uint *)(*(int *)(*piVar4 + local_14 * 4) + 0x54); // +0x54: entityId
        local_c = 0;
        local_10 = (undefined4 *)(this + 0x4c); // +0x4c: componentData array
        local_4 = uVar1;
        do {
          iVar5 = FUN_008d7190(&local_4); // findComponentIndex
          if ((iVar5 < 0) ||
             (puVar6 = (uint *)(iVar5 * 0x2c + 4 + *(int *)(iVar3 + 0x2c)), puVar6 == (uint *)0x0))
          {
            iVar5 = 0;
            if (0 < *(int *)(iVar3 + 0x30)) { // +0x30: componentCount
              puVar6 = *(uint **)(iVar3 + 0x2c); // +0x2c: componentArray
              do {
                if (uVar1 == *puVar6) {
                  puVar6 = (uint *)0x0;
                  goto LAB_008d7f18;
                }
                if (uVar1 < *puVar6) break;
                iVar5 = iVar5 + 1;
                puVar6 = puVar6 + 0xb;
              } while (iVar5 < *(int *)(iVar3 + 0x30));
            }
            puVar6 = (uint *)FUN_008d7980(iVar5); // allocateComponent
            *puVar6 = uVar1;
            puVar6 = puVar6 + 1;
LAB_008d7f18:
            iVar5 = 2;
            do {
              FUN_008d5df0(); // componentInit
              iVar5 = iVar5 + -1;
            } while (iVar5 != 0);
          }
          uVar7 = local_c + 0x14;
          *(undefined4 *)(local_c + 8 + (int)puVar6) = local_10[-2]; // copy component data
          *(undefined4 *)(local_c + 0x10 + (int)puVar6) = *local_10;
          local_10 = local_10 + 1;
          local_c = uVar7;
        } while (uVar7 < 0x28);
        local_4 = uVar1;
        iVar5 = FUN_008d72e0(&local_4); // findPropertyIndex
        if ((iVar5 < 0) ||
           (puVar6 = (uint *)(*(int *)(iVar3 + 0x38) + 4 + iVar5 * 0x18), puVar6 == (uint *)0x0)) {
          iVar5 = 0;
          if (0 < *(int *)(iVar3 + 0x3c)) { // +0x3c: propertyCount
            puVar6 = *(uint **)(iVar3 + 0x38); // +0x38: propertyArray
            do {
              if (uVar1 == *puVar6) {
                puVar6 = (uint *)0x0;
                goto LAB_008d7fb0;
              }
              if (uVar1 < *puVar6) break;
              iVar5 = iVar5 + 1;
              puVar6 = puVar6 + 6;
            } while (iVar5 < *(int *)(iVar3 + 0x3c));
          }
          puVar6 = (uint *)FUN_008d7220(iVar5); // allocateProperty
          *puVar6 = uVar1;
          puVar6 = puVar6 + 1;
LAB_008d7fb0:
          FUN_008d5e80(); // propertyInit
        }
        if (uVar1 == 0x637b907) { // special entity ID
          uVar1 = *(uint *)(this + 0x38); // +0x38: specialValue
        }
        else {
          uVar1 = *(uint *)(this + 0x34); // +0x34: defaultPropertyValue
        }
        puVar6[2] = uVar1; // set property value
        local_14 = local_14 + 1;
      } while (local_14 < *(uint *)(iVar2 + 0x28)); // iterate over all entities
    }
    *(undefined4 *)(iVar3 + 0x9c) = *(undefined4 *)(this + 0x20); // +0x20: some final value
  }
  return;
}