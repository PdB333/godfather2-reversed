// FUNC_NAME: Entity::setVisibility
void __fastcall Entity::setVisibility(Entity* this)
{
  byte oldVisibility;
  int entityData;
  uint flags;
  
  this->vtable = &ENTITY_VTABLE; // +0x00
  Entity::updateVisibility(); // 0x0080e5f0
  if ((this->flags & 4) != 0) { // +0x54 flags
    entityData = this->entityData; // +0x50
    oldVisibility = *(byte *)(entityData + 0x4a4);
    if ((this->flags & 2) == 0) {
      // Clear visibility flag
      *(uint *)(entityData + 0x4a4) = *(uint *)(entityData + 0x4a4) | 1;
      if ((~oldVisibility & 1) == 0) goto LAB_0080ead1;
      flags = this->flags;
      if ((flags & 4) == 0) {
        this->flags = flags | 6;
        Entity::notifyVisibilityChanged(); // 0x004ac1e0
        return;
      }
    }
    else {
      // Set visibility flag
      *(uint *)(entityData + 0x4a4) = *(uint *)(entityData + 0x4a4) & 0xfffffffe;
      if ((~oldVisibility & 1) != 0) goto LAB_0080ead1;
      flags = this->flags;
      if ((flags & 4) == 0) {
        this->flags = flags & 0xfffffffd | 4;
        Entity::notifyVisibilityChanged(); // 0x004ac1e0
        return;
      }
    }
    this->flags = flags & 0xfffffffb;
  }
LAB_0080ead1:
  Entity::notifyVisibilityChanged(); // 0x004ac1e0
  return;
}