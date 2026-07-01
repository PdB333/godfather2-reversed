// FUNC_NAME: Player::updateWeaponState
void __thiscall Player::updateWeaponState(int this, undefined4 param_2)
{
  char cVar1;
  
  cVar1 = FUN_008dee80(); // likely isPlayerAlive() or isPlayerControllable()
  if (cVar1 == '\0') {
    cVar1 = FUN_00481620(); // likely isGamePaused() or isCutsceneActive()
    if (cVar1 != '\0') {
      // Call virtual function at vtable+0x28 (offset 0x28) with argument 0x40
      // This is likely a weapon state change or animation request
      (**(code **)(*(int *)(this + 0x58) + 0x28))(0x40);
      
      // Check if weapon data exists (+0x190 = 400) and if current weapon ID (+0x230) 
      // matches the weapon's stored ID (+0x1ef4 offset in weapon data)
      if ((*(int *)(this + 400) == 0) ||
         (*(int *)(*(int *)(this + 400) + 0x1ef4) != *(int *)(this + 0x230))) {
        FUN_008de5a0(0); // likely resetWeaponState() or equipDefaultWeapon()
      }
    }
  }
  FUN_008dab30(param_2); // likely updateWeaponAnimation() or processWeaponInput()
  return;
}