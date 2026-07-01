// FUNC_NAME: Entity::setName
void __thiscall Entity::setName(int this, char *name)
{
  _strncpy((char *)(this + 0x230), name, 4); // +0x230: name buffer (4 bytes)
  *(undefined1 *)(this + 0x233) = 0; // null-terminate at +0x233
  return;
}