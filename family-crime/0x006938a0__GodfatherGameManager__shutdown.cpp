// FUNC_NAME: GodfatherGameManager::shutdown
void GodfatherGameManager::shutdown(void)
{
  // Call base class shutdown or cleanup
  FUN_00691a70();
  
  // Release global singleton pointer
  FUN_004086d0(&DAT_01206a08);
  
  // If the singleton instance exists, notify it to shutdown (param 1 = shutdown)
  if (DAT_01129bc4 != (undefined4 *)0x0) {
    (**(code **)*DAT_01129bc4)(1);
  }
  
  // Clear the singleton instance pointer
  DAT_01129bc4 = (undefined4 *)0x0;
}