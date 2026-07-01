// Xbox PDB: EARS_Modules_RecoverStateMachine_BuildRecoverStateTable
// FUNC_NAME: RecoverStateMachine::initStateTable
// Function address: 0x00772220
// Builds the recover state machine table for player ground states (getting up from knockdown).
// Called once on initialization to populate the state machine with transitions, animations, and flags.

void RecoverStateMachine::initStateTable(void)
{
  // Look up the recover state table; if it doesn't exist, create and populate it.
  void* stateTable = gStateMachineMgr->findStateTable("recoverStateTable");
  if (stateTable == 0) {
    stateTable = gStateMachineMgr->createStateTable("recoverStateTable");

    // Register all states with initial transition values.
    gStateMachineMgr->registerState(stateTable, "recoverInit", 0xFFFFFFFF);

    // Add state timers (flags/timers for state behavior).
    gStateMachineMgr->addStateFlag(stateTable, 0x17);  // +0x17 flag
    gStateMachineMgr->addStateFlag(stateTable, 0x0C);

    // Add transitions with conditions (3 parameters: from, to, condition, enabled?).
    gStateMachineMgr->addTransitionCondition(stateTable, "flatToCrawl", 0x0C, 3, 1);
    gStateMachineMgr->addTransitionCondition(stateTable, "crawl", 0x0C, 2, 1);
    gStateMachineMgr->addTransitionCondition(stateTable, "kneel", 0x0C, 1, 1);
    gStateMachineMgr->addTransitionCondition(stateTable, "fallToKnees", 10, 0x80, 1);

    // Set state animations.
    gStateMachineMgr->setStateAnimation(stateTable, "terminate", 4);

    // Add transitions (from, to).
    gStateMachineMgr->addTransition(stateTable, "flatToCrawl", 0xFFFFFFFF);
    gStateMachineMgr->addAnimation(stateTable, 0xBF6796A9, 1, 1, 0, 0x3F800000); // animation hash + blend params
    gStateMachineMgr->setAnimationDuration(stateTable, 8); // frames?

    gStateMachineMgr->setStateAnimation(stateTable, "crawl", 7);
    gStateMachineMgr->addTransition(stateTable, "crawl", 0xFFFFFFFF);
    gStateMachineMgr->setStateAnimation(stateTable, "crawlToStandBlocking", 0x11);
    gStateMachineMgr->setStateAnimation(stateTable, "crawlIdle", 4);
    gStateMachineMgr->addTransition(stateTable, "crawlIdle", 0xFFFFFFFF);
    gStateMachineMgr->addStateFlag(stateTable, 0x14);
    gStateMachineMgr->addAnimation(stateTable, 0xC41301CC, 1, 0, 0, 0x3F800000);
    gStateMachineMgr->setAnimationDuration(stateTable, 8);

    gStateMachineMgr->setStateAnimation(stateTable, "crawlToKneel", 0x0D);
    gStateMachineMgr->addTransition(stateTable, "crawlToStandBlocking", 0xFFFFFFFF);
    gStateMachineMgr->addAnimation(stateTable, 0x2BC4B458, 1, 0, 0, 0x3F800000);
    gStateMachineMgr->setAnimationDuration(stateTable, 8);
    gStateMachineMgr->addStateFlag(stateTable, 0x12, 0x2000, 1);
    gStateMachineMgr->setStateAnimation(stateTable, "terminate", 7);
    gStateMachineMgr->addTransition(stateTable, "crawlToKneel", 0xFFFFFFFF);
    gStateMachineMgr->removeStateFlag(stateTable, 0x12, 4, 1);
    gStateMachineMgr->addAnimation(stateTable, 0xBAC0CB9D, 1, 0, 0, 0x3F800000);
    gStateMachineMgr->setAnimationDuration(stateTable, 8);
    gStateMachineMgr->setStateAnimation(stateTable, "kneelIdle", 7);
    gStateMachineMgr->addTransition(stateTable, "kneel", 0xFFFFFFFF);
    gStateMachineMgr->setStateAnimation(stateTable, "kneelToStandBlock", 0x11);
    gStateMachineMgr->setStateAnimation(stateTable, "kneelIdle", 4);
    gStateMachineMgr->addTransition(stateTable, "kneelIdle", 0xFFFFFFFF);
    gStateMachineMgr->addStateFlag(stateTable, 0x15);
    gStateMachineMgr->addAnimation(stateTable, 0x7FA41DAA, 1, 0, 0, 0x3F800000);
    gStateMachineMgr->setStateAnimation(stateTable, "kneelToStandBlock", 0x10);
    gStateMachineMgr->setStateAnimation(stateTable, "kneelToStand", 0x0F);
    gStateMachineMgr->addTransition(stateTable, "fallToKnees", 0xFFFFFFFF);
    gStateMachineMgr->addAnimation(stateTable, 0xCDB88EF5, 1, 0, 0, 0x3F800000);
    gStateMachineMgr->setAnimationDuration(stateTable, 8);
    gStateMachineMgr->setStateAnimation(stateTable, "kneelIdle", 7);
    gStateMachineMgr->addTransition(stateTable, "kneelEndDontStand", 0xFFFFFFFF);
    gStateMachineMgr->addAnimation(stateTable, 0x7FA41DAA, 1, 0, 0, 0x3F800000);
    gStateMachineMgr->setStateAnimation(stateTable, "terminate", 7);
    gStateMachineMgr->addTransition(stateTable, "kneelToStand", 0xFFFFFFFF);
    gStateMachineMgr->addAnimation(stateTable, 0x4EEDEA28, 1, 0, 0, 0x3F800000);
    gStateMachineMgr->addStateFlag(stateTable, 0x19);
    gStateMachineMgr->removeStateFlag(stateTable, 0x12, 8, 1);
    gStateMachineMgr->removeStateFlag(stateTable, 0x12, 0x80, 1);
    gStateMachineMgr->setAnimationDuration(stateTable, 8);
    gStateMachineMgr->setStateAnimation(stateTable, "terminate", 7);
    gStateMachineMgr->addTransition(stateTable, "kneelToStandBlock", 0xFFFFFFFF);
    gStateMachineMgr->addAnimation(stateTable, 0xE3048536, 1, 0, 0, 0x3F800000);
    gStateMachineMgr->addStateFlag(stateTable, 0x19);
    gStateMachineMgr->removeStateFlag(stateTable, 0x12, 8, 1);
    gStateMachineMgr->removeStateFlag(stateTable, 0x12, 0x80, 1);
    gStateMachineMgr->setAnimationDuration(stateTable, 8);
    gStateMachineMgr->addStateFlag(stateTable, 0x12, 0x2000, 1);
    gStateMachineMgr->setStateAnimation(stateTable, "terminate", 7);
    gStateMachineMgr->addTransition(stateTable, "beginStun", 0xFFFFFFFF);
    gStateMachineMgr->addAnimation(stateTable, 0xFE89478A, 1, 0, 0, 0x3F800000);
    gStateMachineMgr->setAnimationDuration(stateTable, 8);
    gStateMachineMgr->setStateAnimation(stateTable, "stunned", 7);
    gStateMachineMgr->addStateFlag(stateTable, 0x12, 2, 1);
    gStateMachineMgr->addTransition(stateTable, "stunned", 0xFFFFFFFF);
    gStateMachineMgr->addStateFlag(stateTable, 0x16);
    gStateMachineMgr->removeStateFlag(stateTable, 0x13, 2, 1);
    gStateMachineMgr->addAnimation(stateTable, 0xDE2D941C, 1, 0, 0, 0x3F800000);
    gStateMachineMgr->setAnimationDuration(stateTable, 8);
    gStateMachineMgr->setStateAnimation(stateTable, "endStun", 0x0E);
    gStateMachineMgr->addStateFlag(stateTable, 0x12, 2, 1);
    gStateMachineMgr->addTransition(stateTable, "endStun", 0xFFFFFFFF);
    gStateMachineMgr->removeStateFlag(stateTable, 0x13, 2, 1);
    gStateMachineMgr->addAnimation(stateTable, 0x15635483, 1, 0, 0, 0x3F800000);
    gStateMachineMgr->setAnimationDuration(stateTable, 8);
    gStateMachineMgr->setStateAnimation(stateTable, "terminate", 7);
    gStateMachineMgr->addStateFlag(stateTable, 0x12, 2, 1);
    gStateMachineMgr->addTransition(stateTable, "terminate", 0xFFFFFFFF);
    gStateMachineMgr->addStateFlag(stateTable, 0x18);
    gStateMachineMgr->addStateFlag(stateTable, 2);

    // Register the state machine with a debug name and finalize.
    gStateMachineMgr->registerStateMachine(0x1C07B25, "RecoverStateMachine");
    gStateMachineMgr->finalizeStateMachine();
  }
  return;
}