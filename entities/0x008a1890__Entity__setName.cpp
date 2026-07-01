// FUNC_NAME: Entity::setName
void __thiscall Entity::setName(int this, char *name)
{
  _strncpy((char *)(this + 0x1c8), name, 0x40); // +0x1c8: name buffer (64 bytes)
  (**(code **)(*(int *)(this + 0xc) + 0x8c))((char *)(this + 0x1c8)); // vtable call: notifyNameChanged
  *(undefined4 *)(this + 0x1c) = 1; // +0x1c: nameDirty flag
  return;
}