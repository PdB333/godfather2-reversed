// FUNC_NAME: Entity::setFlag
void __thiscall Entity::setFlag(int *this, ushort flag)
{
  if ((*(ushort *)(this + 0x60) & 0x3000) == 0) {
    (**(code **)(*this + 0x14))(); // vtable call - likely markDirty or update
    *(ushort *)(this + 0x60) = *(ushort *)(this + 0x60) | flag;
    return;
  }
  *(ushort *)(this + 0x60) = *(ushort *)(this + 0x60) | flag;
  return;
}