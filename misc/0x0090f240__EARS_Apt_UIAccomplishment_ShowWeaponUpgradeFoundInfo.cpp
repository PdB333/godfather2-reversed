// Xbox PDB: EARS_Apt_UIAccomplishment_ShowWeaponUpgradeFoundInfo
// FUNC_NAME: UIFanfareWeapon::showFoundWeaponUpgrade

void __thiscall UIFanfareWeapon::showFoundWeaponUpgrade(void *this)
{
  uint packedIds = *(uint *)((int)this + 0x80); // +0x80: packed weapon ID (low 16 bits) and upgrade level (high 16 bits)
  int upgradeLevel = (short)(packedIds >> 0x10);
  int weaponId = packedIds & 0xffff;
  
  // Start the "gotoAndPlay" animation with label "weapon" on the fanfare movie clip
  FUN_005a04a0("gotoAndPlay", 0, &DAT_00d83810, 1, "weapon");
  
  int unkResult; // from either FUN_007aa2f0 or FUN_007aa340 – likely a weapon upgrade data index
  if (upgradeLevel == 1) {
    unkResult = FUN_007aa2f0(weaponId);
  } else {
    unkResult = FUN_007aa340(upgradeLevel - 1, weaponId);
  }
  
  // local_20 will hold a string pointer (e.g., localized weapon name)
  const char *weaponNameStr = nullptr;
  int stringLen = 0;
  int someFlags = 0;
  code *deallocFunc = nullptr;
  FUN_007aa5c0(unkResult, &weaponNameStr, &stringLen, &someFlags, &deallocFunc);
  
  if (stringLen != 0) {
    // Prepare message text
    const char *formattedWeaponName = weaponNameStr;
    if (formattedWeaponName == nullptr) {
      formattedWeaponName = &DAT_0120546e; // default empty string
    }
    int paramForFunc = FUN_004dafd0(formattedWeaponName); // possibly a hash or string ID
    
    // Build a localized message string
    const char *messageStr = nullptr;
    int msgLen = 0;
    int msgFlags = 0;
    code *msgDealloc = nullptr;
    FUN_004d4ad0(&messageStr, &PTR_LAB_00d78708, paramForFunc); // PTR_LAB_00d78708 likely a string table or format
  
    // Show the fanfare message with localized text
    const char *finalWeaponName = weaponNameStr;
    if (finalWeaponName == nullptr) {
      finalWeaponName = &DAT_0120546e;
    }
    FUN_005a04a0("ShowMessage", 0, &DAT_00d83810, 3,
                 "$fanfare_weapon_upgrade_found_01", // first part of message
                 finalWeaponName,                     // weapon name
                 "$fanfare_weapon_upgrade_found_03"); // third part (probably "!" or similar)
    
    // Set the weapon icon/image
    const char *iconName = weaponNameStr;
    if (iconName == nullptr) {
      iconName = &DAT_0120546e;
    }
    FUN_005a04a0("SetWeaponImage", 0, &DAT_00d83810, 1, iconName);
    
    // Deallocate the message string if necessary
    if (messageStr != nullptr) {
      msgDealloc(messageStr);
    }
  }
  
  // Deallocate the weapon name string if necessary
  if (weaponNameStr != nullptr) {
    deallocFunc(weaponNameStr);
  }
}