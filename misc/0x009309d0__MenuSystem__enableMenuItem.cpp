// FUNC_NAME: MenuSystem::enableMenuItem
void MenuSystem::enableMenuItem(void)
{
  // Build a buffer of 8 bytes, likely a GUID or some identifier
  char buffer[8];
  
  // Call a function to fill the buffer with data from a static address (DAT_00e3266c, size 4)
  // This likely resolves a menu item identifier or control name
  FUN_005c4630(buffer, 8, &DAT_00e3266c, 4);
  
  // Call a function to enable a menu item
  // Parameters: "EnableMenuItem" command, 0 (unknown), DAT_00d8963c (menu handle?), 2 (enable flag?), buffer (item identifier), DAT_00e36d94 (unknown)
  FUN_005a04a0("EnableMenuItem", 0, &DAT_00d8963c, 2, buffer, &DAT_00e36d94);
  
  return;
}