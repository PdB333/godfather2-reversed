// FUNC_NAME: Entity::initFromSource
void __thiscall Entity::initFromSource(Entity *this, undefined4 source)
{
  // Copy source data into sub-object at this+0x8 (likely a struct/class member)
  FUN_004a93a0(source, this + 8);
  // Use byte flag at this+0x1c to trigger secondary initialization
  FUN_0064bb50(*(byte *)(this + 0x1c));
}