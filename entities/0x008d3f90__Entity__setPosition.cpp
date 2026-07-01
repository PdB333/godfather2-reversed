// FUNC_NAME: Entity::setPosition
void __thiscall Entity::setPosition(int this, undefined4 param_2, undefined4 param_3)
{
  // +0x58: position x component (float)
  // +0x68: position y component (float)
  FUN_00408980(this + 0x68, param_3); // Set Y position
  FUN_00408980(this + 0x58, param_2); // Set X position
  return;
}