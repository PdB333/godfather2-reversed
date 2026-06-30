// FUNC_NAME: EntityManager::findEntityByName
undefined1 EntityManager::findEntityByName(int *this, byte *name, undefined4 param_3)

{
  byte bVar1;
  int iVar2;
  undefined1 uVar3;
  byte *pbVar4;
  int iVar5;
  byte *pbVar6;
  int *piVar7;
  uint uVar8;
  bool bVar9;
  undefined1 local_1;
  
  FUN_00ab4db0(&DAT_00e2cbe8); // Enter critical section
  uVar8 = 0;
  local_1 = 0;
  uVar3 = local_1;
  local_1 = 0;
  if (this[0xca] != 0) { // this->entityCount at +0x328
    piVar7 = this + 0x8a; // this->entityList at +0x228
    do {
      if (*(int *)(*piVar7 + 0x104) != 0) { // entity->name at +0x104
        iVar2 = *(int *)(*piVar7 + 4); // entity->name string pointer
        pbVar4 = (byte *)(iVar2 + 8); // skip string header
        pbVar6 = name;
        do {
          bVar1 = *pbVar4;
          bVar9 = bVar1 < *pbVar6;
          if (bVar1 != *pbVar6) {
LAB_005699a5:
            iVar5 = (1 - (uint)bVar9) - (uint)(bVar9 != 0);
            goto LAB_005699aa;
          }
          if (bVar1 == 0) break;
          bVar1 = pbVar4[1];
          bVar9 = bVar1 < pbVar6[1];
          if (bVar1 != pbVar6[1]) goto LAB_005699a5;
          pbVar4 = pbVar4 + 2;
          pbVar6 = pbVar6 + 2;
        } while (bVar1 != 0);
        iVar5 = 0;
LAB_005699aa:
        if (iVar5 == 0) { // String match found
          local_1 = (**(code **)(*this + 0x14))(iVar2,0,param_3); // Call virtual function at vtable+0x14
          break;
        }
      }
      uVar8 = uVar8 + 1;
      piVar7 = piVar7 + 1;
      local_1 = uVar3;
    } while (uVar8 < (uint)this[0xca]); // Loop through all entities
  }
  FUN_00ab4e70(); // Leave critical section
  return local_1;
}