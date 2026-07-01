// FUNC_NAME: isKnownWeaponType
bool isKnownWeaponType(int weaponType)
{
  int type = *(int *)(weaponType + 4);
  
  // Check if weapon type matches any known weapon IDs
  if ((((type != 0x0112ebdc) && (type != 0x0112ebe4)) && (type != 0x0112ebcc)) &&
     (((type != 0x0112ec74 && (type != 0x0112ebd4)) &&
      ((type != 0x0112ebf4 && (type != 0x0112ebec)))))) {
    return false;
  }
  return true;
}