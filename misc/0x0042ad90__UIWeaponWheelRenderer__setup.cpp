// FUNC_NAME: UIWeaponWheelRenderer::setup

void UIWeaponWheelRenderer::setup(int *this, int weaponIndex)
{
  int iVar2;
  int uVar1;
  
  // Clamp global resolution variables to minimum 168 (0xa8)
  if (g_ScreenHeight < 0xa8) {
    g_ScreenHeight = 0xa8;
  }
  if (0xa7 < g_ScreenWidth) {
    g_ScreenWidth = 0xa8;
  }
  // Reset some flag
  g_SomeFlag1 = 0;
  
  // Clamp to minimum 190 (0xbe)
  if (g_ScreenHeight < 0xbe) {
    g_ScreenHeight = 0xbe;
  }
  if (0xbd < g_ScreenWidth) {
    g_ScreenWidth = 0xbe;
  }
  // Reset another flag
  g_SomeFlag2 = 0;
  
  // Lookup weapon data based on weaponIndex (param_2)
  iVar2 = FUN_00417920(weaponIndex);
  uVar1 = *(int *)(&g_WeaponOffsetXArray + iVar2 * 4);
  iVar2 = *(int *)(&g_WeaponOffsetYArray + iVar2 * 4);
  
  // Free previous weapon sprite (assuming this[2] is a sprite pointer)
  FUN_0060a460(this[2]);
  
  // Setup weapon wheel layout parameters
  g_WeaponWheelLayout.numItems = 2;       // +0x00 (DAT_011f41dc)
  g_WeaponWheelLayout.startAngle = 2;     // +0x04 (DAT_011f41e0)
  g_WeaponWheelLayout.radius = 0xef - iVar2; // +0x18 (DAT_011f41f4)
  g_WeaponWheelLayout.someInt1 = 3;       // +0x08 (DAT_011f41e4)
  g_WeaponWheelLayout.someInt2 = 4;       // +0x0C (DAT_011f41e8)
  g_WeaponWheelLayout.weaponIconX = uVar1;  // +0x10 (DAT_011f41ec)
  g_WeaponWheelLayout.weaponIconY = iVar2;  // +0x14 (DAT_011f41f0)
  
  // Update UI element with new radius
  FUN_0042a720(g_WeaponWheelLayout.radius);
  
  // Render the weapon wheel background (layer? order? params: 2,2,3)
  FUN_0041e4d0(2, 2, 3);
  
  // Render the weapon icon (sprite ID? params: 4, uVar1, iVar2)
  FUN_0041e560(4, uVar1, iVar2);
  
  // Clamp screen resolution to minimum 52 (0x34)
  if (g_ScreenWidth < 0x34) {
    g_ScreenWidth = 0x34;
  }
  if (0x34 < g_SomeHeightVar) {
    g_SomeHeightVar = 0x34;
  }
  
  // Set state flags
  g_WeaponWheelState.isActive = 1;    // DAT_011f3aa8
  g_WeaponWheelLayout.someFlag = 0;   // +0x1C (DAT_011f41f8)
  g_WeaponWheelState.currentSlot = 1; // DAT_011f41d8
  
  // Call virtual function at offset 0x30 (show/setVisible?) with args (weaponIndex, 1)
  (*(this->vtable[0x30]))(weaponIndex, 1);
  
  // Set some global to 8
  g_AnotherGlobal = 8; // DAT_0110b874
  
  // Clamp again
  if (g_ScreenWidth < 0x3b) {
    g_ScreenWidth = 0x3b;
  }
  if (0x3b < g_SomeHeightVar) {
    g_SomeHeightVar = 0x3b;
  }
  
  // Reset another flag
  g_WeaponWheelState.someFlag = 0; // DAT_011f3ac4
  
  // Re-render elements (now with state currentSlot=2)
  FUN_0041e4d0(1, 1, 1);
  FUN_0041e560(g_WeaponWheelLayout.someInt2, g_WeaponWheelLayout.weaponIconX, g_WeaponWheelLayout.weaponIconY);
  
  // Final clamp and state updates
  if (g_ScreenWidth < 0x34) {
    g_ScreenWidth = 0x34;
  }
  g_WeaponWheelState.isActive = 1;
  g_WeaponWheelState.currentSlot = 2;
  if (0x34 < g_SomeHeightVar) {
    g_SomeHeightVar = 0x34;
  }
  
  return;
}