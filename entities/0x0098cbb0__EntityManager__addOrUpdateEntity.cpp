// FUNC_NAME: EntityManager::addOrUpdateEntity
void __thiscall EntityManager::addOrUpdateEntity(int this, int entityId, undefined4 param3, undefined4 param4, undefined4 *transform, undefined4 param6)
{
  int iVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  undefined4 *puVar7;
  int *piVar8;
  undefined4 *local_14 [4];
  
  iVar6 = FUN_004dafd0(param4); // likely getResourceHandle or similar
  piVar8 = *(int **)(this + 0x230); // +0x230: entity list begin
  while( true ) {
    if (piVar8 == *(int **)(this + 0x234)) { // +0x234: entity list end
      puVar7 = (undefined4 *)FUN_009c8e50(0x50); // allocate 0x50 bytes for new entity
      if (puVar7 == (undefined4 *)0x0) {
        puVar7 = (undefined4 *)0x0;
      }
      else {
        *puVar7 = 0;
        puVar7[1] = 0;
        puVar7[2] = 0;
        puVar7[3] = 0;
        puVar7[4] = 0;
        puVar7[5] = 0;
        puVar7[6] = 0;
        puVar7[7] = 0;
        puVar7[0xc] = 0; // +0x30: entityId
        puVar7[0xd] = 0; // +0x34: resourceHandle
        puVar7[0xe] = 0x100; // +0x38: flags (0x100 = active?)
        puVar7[0xf] = 0; // +0x3C: unknown
        puVar7[0x10] = 0; // +0x40: param6
      }
      puVar7[0xc] = entityId; // +0x30: set entity ID
      local_14[0] = puVar7;
      FUN_004d3d90(param3); // likely addRef or retain
      FUN_004d3d90(param4); // likely addRef or retain
      puVar7[0xd] = iVar6; // +0x34: set resource handle
      puVar7[0x10] = param6; // +0x40: set param6
      uVar3 = transform[1];
      uVar4 = transform[2];
      uVar5 = transform[3];
      puVar7[8] = *transform; // +0x20: transform.x
      puVar7[9] = uVar3; // +0x24: transform.y
      puVar7[10] = uVar4; // +0x28: transform.z
      puVar7[0xb] = uVar5; // +0x2C: transform.w
      puVar2 = *(undefined4 **)(this + 0x234); // +0x234: entity list end
      if (puVar2 < *(undefined4 **)(this + 0x238)) { // +0x238: entity list capacity
        *(undefined4 **)(this + 0x234) = puVar2 + 1;
        if (puVar2 != (undefined4 *)0x0) {
          *puVar2 = puVar7;
          return;
        }
      }
      else {
        FUN_0098c740(puVar2,local_14); // grow list and add
      }
      return;
    }
    iVar1 = *piVar8;
    if ((*(int *)(iVar1 + 0x30) == entityId) || (*(int *)(iVar1 + 0x34) == iVar6)) break; // +0x30: entityId, +0x34: resourceHandle
    piVar8 = piVar8 + 1;
  }
  // Entity already exists, update it
  if (entityId != 0) {
    *(int *)(iVar1 + 0x30) = entityId; // +0x30: update entity ID
    FUN_004d3d90(param3); // retain new param3
    *(undefined4 *)(*piVar8 + 0x40) = param6; // +0x40: update param6
  }
  if (iVar6 != 0) {
    FUN_004d3d90(param4); // retain new param4
    *(int *)(*piVar8 + 0x34) = iVar6; // +0x34: update resource handle
  }
  iVar6 = *piVar8;
  uVar3 = transform[1];
  uVar4 = transform[2];
  uVar5 = transform[3];
  *(undefined4 *)(iVar6 + 0x20) = *transform; // +0x20: update transform.x
  *(undefined4 *)(iVar6 + 0x24) = uVar3; // +0x24: update transform.y
  *(undefined4 *)(iVar6 + 0x28) = uVar4; // +0x28: update transform.z
  *(undefined4 *)(iVar6 + 0x2c) = uVar5; // +0x2C: update transform.w
  return;
}