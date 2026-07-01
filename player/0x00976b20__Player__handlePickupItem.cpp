// FUNC_NAME: Player::handlePickupItem
void __thiscall Player::handlePickupItem(int *this, int itemEntity, int param_3)
{
  int entityData;
  code *vtableFunc;
  int entityType;
  int itemId;
  
  *(undefined1 *)((int)this + 0x1c1) = 0; // +0x1c1: some flag, cleared
  entityData = FUN_006b0ee0(itemEntity); // get entity data from entity handle
  if (entityData != 0) {
    if (*(int *)(entityData + 0xc4) == 1) { // +0xc4: entity type check (1 = weapon?)
      FUN_0095be90(entityData, param_3); // pickup weapon
      itemId = 4; // weapon pickup sound/effect
    }
    else {
      FUN_009525f0(entityData, param_3, 0); // pickup item (ammo/health/etc)
      itemId = 5; // item pickup sound/effect
    }
    FUN_00957780(itemId); // play pickup sound/effect
    entityType = *(int *)(entityData + 0x48); // +0x48: entity type ID
    this[0x18] = this[0x18] | 0x20; // +0x60: set some flag (bit 5)
    *(undefined8 *)(this + 0x25) = *(undefined8 *)(entityData + 0x10); // +0x94: copy position/transform
    this[0x27] = *(int *)(entityData + 0x18); // +0x9C: copy rotation/angle
    vtableFunc = *(code **)(*this + 0x28); // vtable offset 0x28: some update function
    this[0x24] = entityType; // +0x90: store entity type ID
    (*vtableFunc)(); // call update
  }
  return;
}