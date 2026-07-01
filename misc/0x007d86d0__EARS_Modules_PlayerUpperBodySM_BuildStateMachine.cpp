// Xbox PDB: EARS_Modules_PlayerUpperBodySM_BuildStateMachine
// FUNC_NAME: Player::initPlayerUpperBodyStateMachine
void Player::initPlayerUpperBodyStateMachine(void)
{
    uint stateTableID;
    int tableExists;

    // Get string ID for the main state table
    stateTableID = StateMachine::getStateTableID("playerUpperBodyStateTable");
    tableExists = StateMachine::isStateTableDefined(stateTableID);

    if (tableExists == 0) {
        // Create and register the main player upper body state table
        stateTableID = StateMachine::createStateTable();
        StateMachine::registerStateTable("playerUpperBodyStateTable", stateTableID);

        // Set default terminator for the main table (-1 means no parent state)
        StateMachine::setStateTerminator(&DAT_00d64b74, 0xffffffff);

        // Define states and transitions for "useItem" (two sub-states: 0x24, 0x13)
        StateMachine::addStateEntry("useItem", 0x24);
        StateMachine::addStateEntry("useItem", 0x13);
        StateMachine::addStateEntry("reloadItem", 0x25);
        StateMachine::addStateEntry("reloadItem", 0x15);
        StateMachine::addStateEntry("switchItem", 0x16);
        StateMachine::addStateEntry("revealItem", 0x17);
        StateMachine::addStateEntry("concealItem", 0x18);
        StateMachine::addStateEntry("holdingDisposableItem", 0x19);
        StateMachine::addStateEntry("lungeAttack", 0x1a);

        // Finalize "useItem" and create its sub-state machine
        StateMachine::setStateTerminator("useItem", 0xffffffff);
        StateMachine::initializeSubStateTable("playerUseItemStateTable", 1);

        // Add sub-states to the main table (referenced by the main table string)
        StateMachine::addStateEntry(&DAT_00d64b74, 0x1b);
        StateMachine::addStateEntry(&DAT_00d64b74, 1);

        // Finalize "switchItem" and create its sub-state machine
        StateMachine::setStateTerminator("switchItem", 0xffffffff);
        StateMachine::initializeSubStateTable("playerSwitchItemStateTable", 1);

        StateMachine::addStateEntry(&DAT_00d64b74, 0x1d);
        StateMachine::addStateEntry(&DAT_00d64b74, 1);

        // Finalize "revealItem" and create its sub-state machine
        StateMachine::setStateTerminator("revealItem", 0xffffffff);
        StateMachine::initializeSubStateTable("playerRevealItemStateTable", 1);

        StateMachine::addStateEntry(&DAT_00d64b74, 0x1e);
        StateMachine::addStateEntry(&DAT_00d64b74, 1);

        // Finalize "concealItem" and create its sub-state machine
        StateMachine::setStateTerminator("concealItem", 0xffffffff);
        StateMachine::initializeSubStateTable("playerConcealItemStateTable", 1);

        StateMachine::addStateEntry(&DAT_00d64b74, 0x1f);
        StateMachine::addStateEntry(&DAT_00d64b74, 1);

        // Finalize "reloadItem" and create its sub-state machine
        StateMachine::setStateTerminator("reloadItem", 0xffffffff);
        StateMachine::initializeSubStateTable("playerReloadStateTable", 1);

        StateMachine::addStateEntry(&DAT_00d64b74, 0x20);
        StateMachine::addStateEntry("useItem", 0x14);
        StateMachine::addStateEntry(&DAT_00d64b74, 1);

        // Finalize "throwItem" and create its sub-state machine
        StateMachine::setStateTerminator("throwItem", 0xffffffff);
        StateMachine::initializeSubStateTable("playerThrowItemStateTable", 1);

        StateMachine::addStateEntry(&DAT_00d64b74, 0x21);
        StateMachine::addStateEntry(&DAT_00d64b74, 1);

        // Finalize "holdingDisposableItem" and create its sub-state machine
        StateMachine::setStateTerminator("holdingDisposableItem", 0xffffffff);
        StateMachine::initializeSubStateTable("playerUseDisposableItemStateTable", 1);

        // Add additional transitions for lungeAttack (back to main table sub-states)
        StateMachine::addStateEntry("throwItem", 0x1c);
        StateMachine::addStateEntry("revealItem", 0x17);
        StateMachine::addStateEntry(&DAT_00d64b74, 0x18);
        StateMachine::addStateEntry(&DAT_00d64b74, 0x22);
        StateMachine::addStateEntry(&DAT_00d64b74, 0x23);
        StateMachine::addStateEntry(&DAT_00d64b74, 1);

        // Finalize "lungeAttack" and create its sub-state machine (note: second param 0 indicates no sub-states?)
        StateMachine::setStateTerminator("lungeAttack", 0xffffffff);
        StateMachine::initializeSubStateTable("playerLungeAttackStateTable", 0);

        StateMachine::addStateEntry(&DAT_00d64b74, 1);

        // Register the animation-based state machine for the player upper body
        StateMachine::registerAnimationStateMachine(0x73b715d2, &LAB_007d8690, "PlayerUpperBodySM");

        // Finalize all state machine setup
        StateMachine::finalizeStateMachineSetup();
    }
}