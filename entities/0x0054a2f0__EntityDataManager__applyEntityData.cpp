// FUNC_NAME: EntityDataManager::applyEntityData
undefined4 * __thiscall EntityDataManager::applyEntityData(undefined4 this, undefined4 *entityData, undefined4 param_3)

{
  uint uVar1;
  code *pcVar2;
  undefined4 *puVar3;
  int in_EAX;
  int iVar4;
  int *piVar5;
  int iVar6;
  int iVar7;
  undefined1 local_c [12];
  
  puVar3 = entityData;
  *entityData = &PTR_FUN_00e39c38; // vtable setup
  entityData[1] = in_EAX; // +0x04: entity type
  entityData[2] = this; // +0x08: owning manager
  entityData[3] = param_3; // +0x0C: data source
  if (*(short *)(in_EAX + 4) != 0) {
    *(short *)(in_EAX + 6) = *(short *)(in_EAX + 6) + 1; // increment reference count
  }
  piVar5 = entityData + 2;
  if ((((*piVar5 != 0) && (entityData[3] != 0)) && (0 < *(int *)(entityData[3] + 4))) &&
     (entityData = (undefined4 *)0x0, 0 < *(int *)(*piVar5 + 0xc))) {
    do {
      iVar6 = *(int *)(*(int *)(puVar3[2] + 8) + (int)entityData * 4); // +0x08: entity list
      iVar4 = 0;
      *(undefined4 *)(iVar6 + 0xc) = 0; // +0x0C: clear some field
      if (0 < *(int *)(iVar6 + 0x78)) { // +0x78: property count
        piVar5 = *(int **)(iVar6 + 0x74); // +0x74: property list
        do {
          if (*piVar5 == 0x2f8d528a) { // hash for "position" or similar
            piVar5 = (int *)FUN_004af8c0(local_c,0x2f8d528a); // lookup property
            iVar4 = *piVar5;
            if (iVar4 < 1) {
              if ((iVar4 == -1) && (iVar6 = FUN_0054a2b0(), iVar6 != 0)) {
                pcVar2 = *(code **)(*(int *)(iVar6 + 0x10) + 8); // +0x10: vtable
                *(undefined4 *)(iVar6 + 8) = 0; // +0x08: clear
                for (iVar4 = (*pcVar2)(); iVar4 != -1;
                    iVar4 = (**(code **)(*(int *)(iVar6 + 0x10) + 0xc))(iVar4)) {
                  iVar7 = (**(code **)(*(int *)(iVar6 + 0x10) + 0x10))(iVar4);
                  if (0 < iVar7) {
                    FUN_00a68d30(iVar4,*(uint *)(*(int *)puVar3[3] + -4 + iVar7 * 4) >> 2 |
                                       0x80000000);
                  }
                }
              }
            }
            else {
              uVar1 = *(uint *)(*(int *)puVar3[3] + -4 + iVar4 * 4);
              *(uint *)(iVar6 + 0x2c) = uVar1 >> 2 | 0x80000000; // +0x2C: set value with flag
              *(uint *)(iVar6 + 0xc) = uVar1; // +0x0C: set value
            }
            break;
          }
          iVar4 = iVar4 + 1;
          piVar5 = piVar5 + 4;
        } while (iVar4 < *(int *)(iVar6 + 0x78));
      }
      entityData = (undefined4 *)((int)entityData + 1);
    } while ((int)entityData < *(int *)(puVar3[2] + 0xc)); // +0x0C: entity count
  }
  return puVar3;
}