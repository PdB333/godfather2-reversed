// FUNC_NAME: Entity::fixRelativePointers
void Entity::fixRelativePointers(void)
{
  // This function adjusts relative pointers by adding the base address of the object (in_EAX).
  // It is used after deserializing or relocating an entity to convert relative offsets
  // stored in fields to absolute pointers.
  // Offsets are stored as relative to the object's start, so we add 'this' to each.

  if (*(int *)(this + 0x20) != 0) {
    *(int *)(this + 0x20) = *(int *)(this + 0x20) + (int)this; // +0x20: relative pointer field
  }
  if (*(int *)(this + 0x24) != 0) {
    *(int *)(this + 0x24) = *(int *)(this + 0x24) + (int)this; // +0x24
  }
  if (*(int *)(this + 0x28) != 0) {
    *(int *)(this + 0x28) = *(int *)(this + 0x28) + (int)this; // +0x28
  }
  if (*(int *)(this + 0x30) != 0) {
    *(int *)(this + 0x30) = *(int *)(this + 0x30) + (int)this; // +0x30
  }
  if (*(int *)(this + 0x40) != 0) {
    *(int *)(this + 0x40) = *(int *)(this + 0x40) + (int)this; // +0x40
  }
  if (*(int *)(this + 0x44) != 0) {
    *(int *)(this + 0x44) = *(int *)(this + 0x44) + (int)this; // +0x44
  }
  if (*(int *)(this + 0x48) != 0) {
    *(int *)(this + 0x48) = *(int *)(this + 0x48) + (int)this; // +0x48
  }
  if (*(int *)(this + 0x34) != 0) {
    *(int *)(this + 0x34) = *(int *)(this + 0x34) + (int)this; // +0x34
  }
  if (*(int *)(this + 0x38) != 0) {
    *(int *)(this + 0x38) = *(int *)(this + 0x38) + (int)this; // +0x38
  }
  if (*(int *)(this + 0x50) != 0) {
    *(int *)(this + 0x50) = *(int *)(this + 0x50) + (int)this; // +0x50
  }
  if (*(int *)(this + 0x58) != 0) {
    *(int *)(this + 0x58) = *(int *)(this + 0x58) + (int)this; // +0x58
  }
  if (*(int *)(this + 0x60) != 0) {
    *(int *)(this + 0x60) = *(int *)(this + 0x60) + (int)this; // +0x60
  }
  if (*(int *)(this + 0x68) != 0) {
    *(int *)(this + 0x68) = *(int *)(this + 0x68) + (int)this; // +0x68
  }
  if (*(int *)(this + 0x70) != 0) {
    *(int *)(this + 0x70) = *(int *)(this + 0x70) + (int)this; // +0x70
  }
  if (*(int *)(this + 0x7c) != 0) {
    *(int *)(this + 0x7c) = *(int *)(this + 0x7c) + (int)this; // +0x7c
  }
  if (*(int *)(this + 0x80) != 0) {
    *(int *)(this + 0x80) = *(int *)(this + 0x80) + (int)this; // +0x80
  }
  if (*(int *)(this + 0x8c) != 0) {
    *(int *)(this + 0x8c) = *(int *)(this + 0x8c) + (int)this; // +0x8c
  }
  return;
}