// FUNC_NAME: EntityDataManager::loadEntityDataFromXML
void EntityDataManager::loadEntityDataFromXML(int param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4,
                 undefined4 param_5, undefined4 param_6)

{
  char cVar1;
  int *piVar2;
  undefined4 uVar3;
  undefined1 *puVar4;
  undefined4 uStack_160;
  undefined4 local_158;
  undefined4 local_154;
  undefined4 local_150;
  undefined1 local_148 [64]; // buffer for string parsing
  float local_108; // temporary float value
  undefined1 local_104;
  int local_4; // integer value from XML
  int *entityDataPtr; // pointer to entity data
  
  local_148[0] = 0;
  local_108 = 0.0;
  local_104 = 0;
  local_4 = 0;
  local_158 = 0;
  local_154 = 0;
  local_150 = 0;
  
  // Get entity data manager singleton
  piVar2 = (int *)FUN_00ad8d40(); // likely getEntityDataManager()
  if (piVar2 != (int *)0x0) {
    // Get entity data list
    piVar2 = (int *)(**(code **)(*piVar2 + 0x48))(); // likely getEntityDataList()
    if (piVar2 != (int *)0x0) {
      // Parse entity ID from XML
      cVar1 = FUN_00af5d90(param_3, &local_158); // likely parseXMLAttribute(param_3, &entityId)
      if (cVar1 != '\\0') {
        // Find entity data by ID
        piVar2 = (int *)(**(code **)(*piVar2 + 0x18))(local_158, local_154); // likely findEntityData(entityId)
        *(int **)(param_1 + 0x10) = piVar2; // store pointer to entity data at +0x10
        uVar3 = (**(code **)(*piVar2 + 4))(); // likely getEntityDataSize()
        FUN_004d3d90(uVar3); // likely allocate memory for entity data
      }
    }
  }
  
  puVar4 = local_148;
  uVar3 = FUN_00916c70(DAT_00e54d0c); // likely getStringFromResource()
  uVar3 = FUN_00907680(uVar3); // likely convertToHash()
  cVar1 = FUN_00ae6c80(param_3, uVar3, puVar4); // likely parseXMLAttribute(param_3, hash, buffer)
  if ((cVar1 != '\\0') && (0 < local_4)) {
    *(int *)(param_1 + 0x2c) = local_4; // store integer value at +0x2c
  }
  
  puVar4 = local_148;
  uVar3 = FUN_00907680(param_4); // likely convertToHash(param_4)
  cVar1 = FUN_00ae6c80(param_3, uVar3, puVar4); // parse XML attribute
  if (cVar1 != '\\0') {
    uStack_160 = (undefined4)(longlong)ROUND(local_108); // round float to int
    *(undefined4 *)(param_1 + 0x14) = uStack_160; // store at +0x14
  }
  
  puVar4 = local_148;
  uVar3 = FUN_00907680(param_5); // convertToHash(param_5)
  cVar1 = FUN_00ae6c80(param_3, uVar3, puVar4); // parse XML attribute
  if (cVar1 != '\\0') {
    uStack_160 = (undefined4)(longlong)ROUND(local_108);
    *(undefined4 *)(param_1 + 0x18) = uStack_160; // store at +0x18
  }
  
  puVar4 = local_148;
  uVar3 = FUN_00907680(param_6); // convertToHash(param_6)
  cVar1 = FUN_00ae6c80(param_3, uVar3, puVar4); // parse XML attribute
  if (cVar1 != '\\0') {
    uStack_160 = (undefined4)(longlong)ROUND(local_108);
    *(undefined4 *)(param_1 + 0x1c) = uStack_160; // store at +0x1c
  }
  
  return;
}