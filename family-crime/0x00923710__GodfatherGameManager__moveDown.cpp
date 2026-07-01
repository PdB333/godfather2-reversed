// FUNC_NAME: GodfatherGameManager::moveDown
void GodfatherGameManager::moveDown(void)
{
  undefined4 local_c;
  undefined4 local_8;
  undefined1 local_4;
  
  // Call to move the camera or player down (e.g., in a menu or free-roam)
  FUN_005a04a0("MoveDown",0,&DAT_00d87288,0);
  
  // Store current state and call a function to process it
  local_c = DAT_011302b0; // +0x?? some state or input flag
  local_8 = 0;
  local_4 = 0;
  FUN_00408a00(&local_c,0);
  return;
}