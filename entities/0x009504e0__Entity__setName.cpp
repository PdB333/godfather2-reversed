// FUNC_NAME: Entity::setName
void __thiscall Entity::setName(int this, int name, int subtitle)
{
  if (name == 0) {
    *(char *)(this + 0x184) = 0; // +0x184: name string (null-terminated)
  }
  else {
    FUN_005c4660(this + 0x184, name, 0x40, 0); // strncpy-like copy, max 0x40 bytes
  }
  if (subtitle != 0) {
    FUN_005c4660(this + 0x1c4, subtitle, 0x40, 0); // +0x1c4: subtitle string
    return;
  }
  *(char *)(this + 0x1c4) = 0; // null-terminate subtitle
  return;
}