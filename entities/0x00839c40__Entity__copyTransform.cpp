// FUNC_NAME: Entity::copyTransform
void __thiscall Entity::copyTransform(int this, int other)
{
  // Copy position (vec3) from other entity to this entity
  // +0x4C: position.x
  // +0x50: position.y
  // +0x54: position.z
  // +0x58: position.w (or padding)
  *(undefined4 *)(this + 0x4c) = *(undefined4 *)(other + 0x11c);
  *(undefined4 *)(this + 0x50) = *(undefined4 *)(other + 0x120);
  *(undefined4 *)(this + 0x54) = *(undefined4 *)(other + 0x124);
  *(undefined4 *)(this + 0x58) = *(undefined4 *)(other + 0x128);
  return;
}