// FUNC_NAME: Entity::getHealth
void __thiscall Entity_getHealth(int this, byte *outHealth)
{
  // Dereference pointer at +0x18 to get health data container,
  // then read byte at offset +0x11 from that container.
  *outHealth = *(byte *)(*(int *)(this + 0x18) + 0x11);
  return;
}