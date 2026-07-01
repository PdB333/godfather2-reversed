// FUNC_NAME: GodfatherGameManager::updatePlayerInput
void __fastcall GodfatherGameManager::updatePlayerInput(int this)
{
  int vtable;
  float deltaTime;
  
  *(uint *)(this + 0x24a0) = *(uint *)(this + 0x24a0) & 0xfffffeff; // Clear bit 8 (input disabled flag)
  vtable = **(int **)(this + 0x5f4); // Get InputDeviceManager vtable (+0x5f4)
  deltaTime = (float)(**(code **)(**(int **)(this + 0x5f4) + 0x2c))(); // InputDeviceManager::getDeltaTime()
  (**(code **)(vtable + 0x3c))(deltaTime); // InputDeviceManager::update(deltaTime)
  return;
}