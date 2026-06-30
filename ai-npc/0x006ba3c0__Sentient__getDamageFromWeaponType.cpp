// FUNC_NAME: Sentient::getDamageFromWeaponType
uint __fastcall Sentient::getDamageFromWeaponType(int thisPtr)
{
  uint damage;
  uint maxDamage;
  
  // Get base damage from weapon type table at offset +0xB8, indexed by weapon type at +0x90
  damage = *(uint *)(thisPtr + 0xb8 + *(int *)(thisPtr + 0x90) * 0xc);
  maxDamage = *(uint *)(thisPtr + 0x98); // +0x