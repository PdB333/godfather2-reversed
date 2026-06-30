// FUNC_NAME: GodfatherGameManager::shutdown
void GodfatherGameManager::shutdown(void)
{
  undefined1 local_14 [20];
  
  FUN_0091ebb0(); // likely ~GodfatherGameManager() or cleanup
  FUN_0068b580(local_14,0); // likely some string/object init with 0
  FUN_008ec620(); // likely ~SimManager() or similar
  FUN_0088d640(); // likely ~PlayerManager() or similar
  FUN_0067c4f0(); // likely ~BuildingManager() or similar
  FUN_00682860(); // likely ~NPCManager() or similar
  *(uint *)(DAT_01223394 + 0x6c) = *(uint *)(DAT_01223394 + 0x6c) & 0xfffffffe; // clear bit 0 of some flag at +0x6c
  return;
}