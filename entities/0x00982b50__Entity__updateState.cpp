// FUNC_NAME: Entity::updateState
void __fastcall Entity::updateState(int *entity)
{
  // Check if entity is not in certain states (likely idle, dead, or inactive)
  // +0x6C = state field 1 (0x1b * 4)
  // +0x7C = state field 2 (0x1f * 4)
  // +0x68 = state field 3 (0x1a * 4)
  if (((entity[0x1b] == 0) && (entity[0x1f] == 0)) && (entity[0x1a] == 0)) {
    // Schedule a callback to be called on next frame
    // entity + 0x10 = callback data pointer
    FUN_005c02f0(entity + 4, &LAB_00982b20, 1);
    
    // Call virtual function at vtable offset 0x2c (likely updateAnimation or similar)
    (**(code **)(*entity + 0x2c))();
    return;
  }
  return;
}