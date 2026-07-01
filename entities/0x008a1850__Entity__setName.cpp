// FUNC_NAME: Entity::setName
void __thiscall Entity::setName(int this, char *name)
{
  _strncpy((char *)(this + 0x148), name, 0x80); // +0x148: entity name buffer (128 bytes)
  return;
}