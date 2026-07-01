// FUNC_NAME: GodfatherGameManager::applyGraphicsSettings
void GodfatherGameManager::applyGraphicsSettings(void)
{
  int iVar1;
  
  iVar1 = DAT_01129938;  // pointer to some graphics config object
  FUN_0090cdb0(DAT_00e57548,0);  // set some graphics option 1
  FUN_0090ce30(DAT_00e57549);    // set some graphics option 2
  FUN_0090ce50(DAT_00e5754a);    // set some graphics option 3
  if (DAT_00e5754b == '\0') {
    *(uint *)(iVar1 + 0x14) = *(uint *)(iVar1 + 0x14) & 0xffffffef;  // clear bit 4
  }
  else {
    *(uint *)(iVar1 + 0x14) = *(uint *)(iVar1 + 0x14) | 0x10;  // set bit 4
  }
  if (DAT_00e5754c == '\0') {
    *(uint *)(iVar1 + 0x14) = *(uint *)(iVar1 + 0x14) & 0xffffffdf;  // clear bit 5
  }
  else {
    *(uint *)(iVar1 + 0x14) = *(uint *)(iVar1 + 0x14) | 0x20;  // set bit 5
  }
  FUN_0090ca30(_DAT_00e57550);  // apply some graphics setting
  FUN_0090ca80(_DAT_00e57554);  // apply some graphics setting
  FUN_0090cd70(DAT_00e57558);   // apply some graphics setting
  FUN_0090c980(_DAT_00e5755c);  // apply some graphics setting
  FUN_0090c9c0(_DAT_00e57560);  // apply some graphics setting
  return;
}