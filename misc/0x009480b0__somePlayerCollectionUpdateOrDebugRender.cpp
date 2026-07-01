// FUNC_NAME: somePlayerCollectionUpdateOrDebugRender
void FUN_009480b0(void)
{
  int *gameManager;
  int *entityMgr;
  int *player1;
  int *player1Crew;
  int *player1Lt1;
  int *player1Lt2;
  undefined4 stackVal;
  undefined4 allocResult;
  
  // DAT_01223484 likely points to a global game manager singleton (e.g. GodfatherGameManager)
  // Check if game manager exists, and its +0xc field (entity manager?) is non-null
  if ((((DAT_01223484 != 0) && (*(int *)(DAT_01223484 + 0xc) != 0)) &&
      (gameManager = (int *)FUN_00ad8d40(), gameManager != (int *)0x0)) &&  // Get something (maybe GetPlayerManager?)
     (entityMgr = (*(code **)(*gameManager + 0x34))(entityMgr), entityMgr != 0)) { // GetPlayerEntityManager or similar
    entityMgr = (int *)(*(code **)(*entityMgr + 0x34))();  // Get a player (first player's controller?)
    entityMgr = (int *)(*(code **)(*entityMgr + 0x24))();  // Get player's stats/crew component (+0x24 is offset to crew component)
    if (entityMgr != (int *)0x0) {
      player1Crew = (int *)(*(code **)(*entityMgr + 4))();   // +0x04: Get first lieutenant
      entityMgr = (int *)(*(code **)(*entityMgr + 8))();     // +0x08: Get second lieutenant
      if (((player1Crew != (int *)0x0) && (entityMgr != (int *)0x0)) &&
         ((player1Crew != entityMgr && ((DAT_0122344c != 0 && (FUN_00454560(player1Crew) != 0)))))  // Check something and first guy is valid
         ) {
        stackVal = (*(code **)(*entityMgr + 0xc))();  // +0x0c: Get some state/position from second lieutenant
        // Allocate memory for a debug overlay or UI element
        allocResult = FUN_009c8e50(0x38); // malloc-like (56 bytes)
        if (allocResult == 0) {
          allocResult = 0;
        }
        else {
          allocResult = FUN_00947f20(); // Constructor-like
        }
        // Construct some debug display object (maybe crew member info overlay)
        FUN_00946de0(&stack0x00000004, &stackVal);
        // Render or submit the debug overlay
        FUN_0064ef60(allocResult);
      }
    }
  }
  return;
}