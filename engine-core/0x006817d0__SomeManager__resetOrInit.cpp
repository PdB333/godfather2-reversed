// FUNC_NAME: SomeManager::resetOrInit
void SomeManager::resetOrInit(void)
{
  // DAT_01129878 is likely a global pointer to a manager instance
  // +0x20 is an offset within that manager's data structure
  undefined4 *someField = (undefined4 *)(DAT_01129878 + 0x20);
  
  // Call a sub-function that likely performs initialization or cleanup
  FUN_006809b0();
  
  // Set the field at offset +0x20 to 0 (null or false)
  *someField = 0;
  
  return;
}