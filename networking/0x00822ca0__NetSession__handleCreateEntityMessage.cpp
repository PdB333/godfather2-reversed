// FUNC_NAME: NetSession::handleCreateEntityMessage
undefined4 __thiscall NetSession::handleCreateEntityMessage(int this, int messageType, int *entityData)
{
  undefined4 *vtable;
  int entityHandle;
  int *newEntity;
  int local_c[3];
  
  if (messageType != -0x7dddd2d2) {
    return 0;
  }
  FUN_00822310(local_c, entityData);
  if (local_c[0] == 0) {
    vtable = (undefined4 *)FUN_009c89b0(); // Get some global vtable/allocator
    local_c[0] = 2;
    local_c[1] = 0x10;
    local_c[2] = 0;
    entityHandle = (**(code **)*vtable)(0x130, local_c); // Allocate 0x130 bytes
    if (entityHandle != 0) {
      newEntity = (int *)FUN_008208c0(); // Create entity object
      if (newEntity == (int *)0x0) {
        return 1;
      }
      newEntity[7] = *entityData;          // +0x1C
      newEntity[8] = entityData[1];        // +0x20
      newEntity[9] = entityData[2];        // +0x24
      newEntity[10] = entityData[3];       // +0x28
      int iVar2 = *(int *)(this + 8);      // +0x08 - some session data
      if (iVar2 != 0) {
        newEntity[0xf] = *(int *)(iVar2 + 0x24);  // +0x3C
        newEntity[0x10] = *(int *)(iVar2 + 0x28); // +0x40
        newEntity[0x11] = *(int *)(iVar2 + 0x2c); // +0x44
        newEntity[0x12] = *(int *)(iVar2 + 0x30); // +0x48
      }
      (**(code **)(*newEntity + 4))(0x82222d2e); // Call vtable method at offset 4
      FUN_00822ac0(newEntity); // Register/activate entity
      return 1;
    }
  }
  else {
    FUN_00820dd0(); // Error handling
  }
  return 1;
}