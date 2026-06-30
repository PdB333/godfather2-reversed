// FUNC_NAME: GodfatherGameManager::shutdown
void GodfatherGameManager::shutdown(void)
{
  int iVar1;
  bool bVar2;
  
  iVar1 = DAT_01129bc0; // some global pointer, likely a manager instance
  bVar2 = DAT_01129bc0 != 0;
  *(undefined4 *)(DAT_012233b4 + 0x570) = 0; // clear some flag at offset 0x570
  if (bVar2) {
    FUN_006938d0(); // likely cleanup/shutdown helper
    FUN_009c8eb0(iVar1); // likely delete/free the manager instance
  }
  return;
}