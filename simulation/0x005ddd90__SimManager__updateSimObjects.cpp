// FUNC_NAME: SimManager::updateSimObjects
undefined1 SimManager::updateSimObjects(undefined4 param_1, int param_2)
{
  byte *pbVar1;
  undefined1 uVar2;
  int iVar3;
  char cVar4;
  int iVar5;
  undefined4 *puVar6;
  uint local_40;
  
  iVar3 = param_2;
  pbVar1 = (byte *)(param_2 + 0x24); // +0x24: flags field (bit 0 = active)
  param_2._0_1_ = 1;
  if ((*pbVar1 & 1) == 0) {
    return 0;
  }
  FUN_005ddd30(); // likely lock or begin iteration
  puVar6 = *(undefined4 **)(iVar3 + 0x2c); // +0x2c: pointer to object list
  if ((puVar6 != (undefined4 *)0x0) && (local_40 = 0, uVar2 = 1, *(int *)(iVar3 + 0x28) != 0)) { // +0x28: object count
    do {
      if (puVar6 == (undefined4 *)0x0) {
        param_2._0_1_ = 0;
      }
      else {
        iVar5 = FUN_005dc670(*puVar6); // likely isObjectValid or isObjectActive
        if (iVar5 == 0) {
LAB_005dde48:
          param_2._0_1_ = 0;
        }
        else {
          cVar4 = FUN_005dd510(); // likely updateSingleObject
          param_2._0_1_ = uVar2;
          if (cVar4 == '\0') goto LAB_005dde48;
        }
        puVar6 = (undefined4 *)puVar6[10]; // +0x28: next pointer in linked list
      }
      local_40 = local_40 + 1;
      uVar2 = (undefined1)param_2;
    } while (local_40 < *(uint *)(iVar3 + 0x28));
  }
  return (undefined1)param_2;
}