// Xbox PDB: EARS_Modules_NPCActionSM_BuildStateMachine
// FUNC_NAME: NPC::buildActionStateMachine

void NPC::buildActionStateMachine(void)
{
    // Get some ID or handle for the state machine
    uint stateMachineID = stateMachineAllocID(); // 0x009c8f80

    // Set the name of the state machine
    stateMachineSetName("NPCActionST", stateMachineID); // 0x004ad9d0

    // Define base state for action selection
    stateMachineAddState(&DAT_00d695c0, -1); // 0x004adae0

    // Set priority and flags for initial idle state
    stateMachineSetStateFlags(3, 0x40000, 1); // 0x004ad0f0

    // Transition from "ChooseAction" with priority 4
    stateMachineAddTransition("ChooseAction", 4); // 0x004acc70

    // Add failure state (no parent)
    stateMachineAddState("ActionFailure", -1); // 0x004adae0

    // Set various state parameters
    stateMachineSetParam(0x26); // 0x004acf70

    stateMachineAddTransition("ChooseAction", 4);
    stateMachineAddState("PrevActionDone", -1);
    stateMachineSetParam(0x25);
    stateMachineSetParam(0x24);
    stateMachineAddTransition("ChooseAction", 4);

    // Get handle for ChooseAction state
    uint chooseActionHandle = stateMachineAddState("ChooseAction", -1); // 0x004adae0
    stateMachineSetParam(0x27); // 0x004acf70

    // Set flags for state (0x32, 0x27)
    stateMachineSetStateFlags(0x32); // 0x004acff0
    stateMachineSetStateFlags(0x27);

    // Transition to ExitCover with priority 0x18
    stateMachineAddTransition("ExitCover", 0x18); // 0x004acc70

    // Set a callback or function pointer
    setExitActionCallback(chooseActionHandle); // 0x0077efd0

    // Transition to ChooseActionIdle with priority 4
    stateMachineAddTransition("ChooseActionIdle", 4);

    // Set state flags (0x23, 0x33, 0x35)
    stateMachineSetStateFlag(0x23); // 0x004ad070
    stateMachineSetStateFlag(0x33);
    stateMachineSetStateFlag(0x35);

    // Get handle for ChooseActionIdle
    uint idleHandle = stateMachineAddState("ChooseActionIdle", -1);
    stateMachineSetStateFlags(10, 0x49, 1); // priority, flags, enabled
    stateMachineSetParam(0x29);
    stateMachineSetStateFlags(0x27);
    stateMachineSetStateFlags(0x2a);
    stateMachineAddTransition("ExitCover", 0x18);
    setExitActionCallback(idleHandle);
    stateMachineSetStateFlag(0x23);
    stateMachineSetStateFlag(0x33);
    stateMachineSetStateFlag(0x35);
    stateMachineSetStateFlags(0xb, 0x49, 1); // 0x004ad170

    // Add base state for patrol
    stateMachineAddState(&DAT_00d6937c, -1);
    stateMachineSetStateFlags(10, 0x49, 1);
    stateMachineSetParam(0x29);
    stateMachineSetStateFlags(0x2a);
    stateMachineSetStateFlags(0x28);
    stateMachineAddTransition("PrevActionDone", 0x14);
    stateMachineSetStateFlags(0xb, 0x49, 1);
    stateMachineSetStateFlag(0x3e);

    // Guard state
    stateMachineAddState(&DAT_00d69544, -1);
    stateMachineBindState("NPCPatrolST", 1); // 0x004acf10
    stateMachineSetStateFlags(0x28);

    // Failure transition for guard
    stateMachineSetFailureTransition("ActionFailure", 6, 0x40000, 1); // 0x004acd20
    stateMachineAddTransition("PrevActionDone", 0x14);
    stateMachineAddTransition("PrevActionDone", 1);

    // Guard state machine
    stateMachineAddState("Guard", -1);
    stateMachineBindState("NPCGuardST", 1);
    stateMachineSetStateFlags(0x28);
    stateMachineSetFailureTransition("ActionFailure", 6, 0x40000, 1);
    stateMachineAddTransition("PrevActionDone", 0x14);
    stateMachineAddTransition("PrevActionDone", 1);

    // Flee states
    stateMachineAddState(&DAT_00d69534, -1);
    stateMachineSetParam(0x37);
    stateMachineBindState("NPCFleeST", 1);
    stateMachineSetStateFlags(0x28);
    stateMachineSetFailureTransition("ActionFailure", 6, 0x40000, 1);
    stateMachineAddTransition("PrevActionDone", 0x14);
    stateMachineAddTransition("PrevActionDone", 1);

    // Draw gun
    stateMachineAddState("DrawGunAction", -1);
    stateMachineBindState("DrawGunST", 1);
    stateMachineAddTransition("PrevActionDone", 1);

    // Holster gun
    stateMachineAddState("HolsterGunAction", -1);
    stateMachineBindState("HolsterGunST", 1);
    stateMachineAddTransition("PrevActionDone", 1);

    // Reload
    stateMachineAddState("ReloadGunAction", -1);
    stateMachineSetStateFlags(0x20, 1, 1);
    stateMachineBindState("ReloadGunST", 1);
    stateMachineAddTransition("PrevActionDone", 1);

    // Stationary fire
    stateMachineAddState("FireGunStationaryAction", -1);
    stateMachineSetStateFlags(0x20, 0, 1);
    stateMachineBindState("ShootST", 1);
    stateMachineAddTransition("PrevActionDone", 1);

    // Strafe fire
    stateMachineAddState("StrafeFire", -1);
    stateMachineSetStateFlags(0x20, 0, 1);
    stateMachineBindState("RangedMovementST", 1);
    stateMachineSetStateFlags(0x28);
    stateMachineSetFailureTransition("ActionFailure", 6, 0x40000, 1);
    stateMachineAddTransition("PrevActionDone", 0x14);
    stateMachineAddTransition("PrevActionDone", 1);

    // Ranged chase
    stateMachineAddState("RangedChase", -1);
    stateMachineSetStateFlags(3, 0x20, 1);
    stateMachineBindState("NPCChaseST", 1);
    stateMachineAddTransition("PrevActionDone", 0x16);
    stateMachineAddConditionalTransition("PrevActionDone", 2, DAT_00e445ac, 1); // 0x004acd80
    stateMachineAddTransition("PrevActionDone", 0x13);
    stateMachineSetFailureTransition("ActionFailure", 6, 0x20, 1);
    stateMachineAddTransition("PrevActionDone", 1);
    stateMachineSetStateFlags(4, 0x20, 1);

    // Cover enter
    stateMachineAddState("EnterCover", -1);
    stateMachineSetStateFlags(0x20, 2, 1);
    stateMachineBindState("CoverDashST", 1);
    stateMachineSetFailureTransition("ActionFailure", 6, 0x40000, 1);
    stateMachineAddTransition("ActionFailure", 0x17);
    stateMachineAddTransition("PrevActionDone", 1);

    // Cover exit
    stateMachineAddState("ExitCover", -1);
    stateMachineSetParam(0x2b);
    stateMachineAddTransition("PrevActionDone", 4);

    // Cover peek
    stateMachineAddState("CoverPeek", -1);
    stateMachineSetStateFlags(0x20, 3, 1);
    stateMachineBindState("CoverPeekST", 1);
    stateMachineSetFailureTransition("ActionFailure", 6, 0x40000, 1);
    stateMachineAddTransition("ActionFailure", 0x17);
    stateMachineAddTransition("PrevActionDone", 1);

    // Cover peek fire
    stateMachineAddState("CoverPeekFire", -1);
    stateMachineBindState("CoverPeekFireST", 1);
    stateMachineSetFailureTransition("ActionFailure", 6, 0x40000, 1);
    stateMachineAddTransition("ActionFailure", 0x17);
    stateMachineAddTransition("PrevActionDone", 1);

    // Cover blind fire
    stateMachineAddState("CoverBlindFire", -1);
    stateMachineBindState("CoverBlindFireST", 1);
    stateMachineSetFailureTransition("ActionFailure", 6, 0x40000, 1);
    stateMachineAddTransition("ActionFailure", 0x17);
    stateMachineAddTransition("PrevActionDone", 1);

    // Change cover node
    stateMachineAddState("ChangeCoverNode", -1);
    stateMachineBindState("CoverDashST", 1);
    stateMachineSetFailureTransition("ActionFailure", 6, 0x40000, 1);
    stateMachineAddTransition("ActionFailure", 0x17);
    stateMachineAddTransition("PrevActionDone", 1);

    // Act threatening
    stateMachineAddState("ActThreatening", -1);
    stateMachineSetParam(0x19);
    stateMachineBindState("setHeadingToEntityTable", 1);
    stateMachineAddTransition("PrevActionDone", 0x19);
    stateMachineAddTransition("PrevActionDone", 1);

    // Cower
    stateMachineAddState("Cower", -1);
    stateMachineSetParam(0x36);
    stateMachineSetParam(0x1e);
    stateMachineAddConditionalTransition("PrevActionDone", 2, DAT_00d5eee4, 1);

    // Startle
    stateMachineAddState("Startle", -1);
    stateMachineSetParam(0x1b);
    stateMachineBindState("setHeadingToEntityTable", 1);
    stateMachineAddTransition("PrevActionDone", 7);
    stateMachineAddTransition("PrevActionDone", 1);

    // Follow
    stateMachineAddState("Follow", -1);
    stateMachineBindState("NPCFollowST", 1);
    stateMachineSetStateFlags(0x28);
    stateMachineSetFailureTransition("ActionFailure", 6, 0x40000, 1);
    stateMachineAddTransition("PrevActionDone", 0x14);
    stateMachineAddTransition("PrevActionDone", 1);

    // Surrender
    stateMachineAddState("Surrender", -1);
    stateMachineSetParam(0x2c);
    stateMachineBindState("setHeadingToEntityTable", 1);
    stateMachineAddTransition("PrevActionDone", 0x19);
    stateMachineAddTransition("PrevActionDone", 1);

    // Search
    stateMachineAddState("Search", -1);
    stateMachineBindState("NPCSearchST", 1);
    stateMachineSetStateFlags(0x28);
    stateMachineAddTransition("PrevActionDone", 0x14);
    stateMachineAddTransition("PrevActionDone", 0x13);
    stateMachineAddTransition("PrevActionDone", 1);

    // Building search
    stateMachineAddState("BuildingSearch", -1);
    stateMachineBindState("NPCSearchST", 1);
    stateMachineSetStateFlags(0x28);
    stateMachineSetFailureTransition("ActionFailure", 6, 0x40000, 1);
    stateMachineAddTransition("PrevActionDone", 0x14);
    stateMachineAddTransition("PrevActionDone", 0x13);
    stateMachineAddTransition("PrevActionDone", 1);

    // Random search
    stateMachineAddState("RandomSearch", -1);
    stateMachineBindState("RandomSearchST", 1);
    stateMachineSetStateFlags(0x28);
    stateMachineAddTransition("PrevActionDone", 0x14);
    stateMachineAddTransition("PrevActionDone", 0x13);
    stateMachineAddTransition("PrevActionDone", 1);

    // Equip melee weapon
    stateMachineAddState("EquipMeleeWeapon", -1);
    stateMachineSetParam(0x2d);
    stateMachineSetStateFlags(0x2e);
    stateMachineAddTransition("PrevActionDone", 7);

    // Conceal melee weapon
    stateMachineAddState("ConcealMeleeWeapon", -1);
    stateMachineSetParam(0x2f);
    stateMachineAddTransition("PrevActionDone", 7);

    // Melee attack
    stateMachineAddState("MeleeAttack", -1);
    stateMachineSetStateFlags(0x20, 0, 1);
    stateMachineBindState("NPCPunchST", 1);
    stateMachineAddTransition("PrevActionDone", 1);
    stateMachineSetStateFlag(0x22);

    // Evade
    stateMachineAddState("Evade", -1);
    stateMachineSetParam(0x30);
    stateMachineSetStateFlag(0x31);
    stateMachineAddTransition("PrevActionDone", 7);

    // Melee chase
    stateMachineAddState("MeleeChase", -1);
    stateMachineSetStateFlags(3, 0x20, 1);
    stateMachineBindState("NPCChaseST", 1);
    stateMachineSetStateFlags(0x28);
    stateMachineSetFailureTransition("ActionFailure", 6, 0x20, 1);
    stateMachineAddTransition("PrevActionDone", 0x14);
    stateMachineAddTransition("PrevActionDone", 0x15);
    stateMachineAddTransition("PrevActionDone", 1);
    stateMachineSetStateFlags(4, 0x20, 1);

    // Melee spectate
    stateMachineAddState("MeleeSpectate", -1);
    stateMachineBindState("NPCMeleeSupporterST", 1);
    stateMachineSetStateFlags(0x28);
    stateMachineAddTransition("PrevActionDone", 0x14);
    stateMachineAddTransition("PrevActionDone", 0x13);
    stateMachineAddTransition("PrevActionDone", 1);

    // Approach crime scene
    stateMachineAddState("ApproachCrimeScene", -1);
    stateMachineSetStateFlags(3, 0x20, 1);
    stateMachineBindState("FollowPathST", 1);
    stateMachineSetStateFlags(0x28);
    stateMachineAddTransition("PrevActionDone", 0x14);
    stateMachineAddTransition("PrevActionDone", 0x13);
    stateMachineSetFailureTransition("ActionFailure", 6, 0x20, 1);
    stateMachineAddTransition("PrevActionDone", 1);
    stateMachineSetStateFlags(0x21, 0x889fc1bb, 1);
    stateMachineSetStateFlags(4, 0x20, 1);

    // Approach takeover venue
    stateMachineAddState("ApproachTakeoverVenue", -1);
    stateMachineSetStateFlags(3, 0x20, 1);
    stateMachineBindState("CombatPathST", 1);
    stateMachineSetStateFlags(0x28);
    stateMachineSetFailureTransition("ActionFailure", 6, 0x20, 1);
    stateMachineAddTransition("PrevActionDone", 0x14);
    stateMachineAddTransition("PrevActionDone", 0x13);
    stateMachineAddTransition("PrevActionDone", 1);
    stateMachineSetStateFlags(4, 0x20, 1);

    // Witness intimidation
    stateMachineAddState("WitnessIntimidation", -1);
    stateMachineBindState("NPCIntimidateST", 1);
    stateMachineSetStateFlags(0x28);
    stateMachineSetFailureTransition("ActionFailure", 6, 0x40000, 1);
    stateMachineAddTransition("PrevActionDone", 0x14);
    stateMachineAddTransition("PrevActionDone", 0x13);
    stateMachineAddTransition("PrevActionDone", 1);

    // Owner intimidation
    stateMachineAddState("OwnerIntimidation", -1);
    stateMachineBindState("NPCIntimidateST", 1);
    stateMachineSetStateFlags(0x28);
    stateMachineSetFailureTransition("ActionFailure", 6, 0x40000, 1);
    stateMachineAddTransition("PrevActionDone", 0x14);
    stateMachineAddTransition("PrevActionDone", 0x13);
    stateMachineAddTransition("PrevActionDone", 1);

    // Stop witnessing
    stateMachineAddState("StopWitnessing", -1);
    stateMachineSetParam(0x38);
    stateMachineAddTransition("PrevActionDone", 4);

    // Break guard
    stateMachineAddState("BreakGuard", -1);
    stateMachineSetParam(0x39);
    stateMachineAddTransition("PrevActionDone", 4);

    // Reform guard
    stateMachineAddState("ReformGuard", -1);
    stateMachineSetParam(0x3a);
    stateMachineAddTransition("PrevActionDone", 4);

    // Find pedestrian graph
    stateMachineAddState("FindPedGraph", -1);
    stateMachineSetParam(0x3d);
    stateMachineAddTransition("ActionFailure", 0x1a);
    stateMachineAddTransition("PrevActionDone", 4);

    // Inform
    stateMachineAddState("Inform", -1);
    stateMachineBindState("NPCInformST", 1);
    stateMachineSetFailureTransition("ActionFailure", 6, 0x40000, 1);
    stateMachineAddTransition("PrevActionDone", 0x13);
    stateMachineAddTransition("PrevActionDone", 1);

    // Witness idle
    stateMachineAddState("WitnessIdle", -1);
    stateMachineSetStateFlags(10, 0x49, 1);
    stateMachineBindState("NPCWitnessIdleST", 1);
    stateMachineSetStateFlags(0x28);
    stateMachineAddTransition("PrevActionDone", 0x14);
    stateMachineAddTransition("PrevActionDone", 1);
    stateMachineSetStateFlags(0xb, 0x49, 1);

    // Crime scene search
    stateMachineAddState("CrimeSceneSearch", -1);
    stateMachineSetStateFlags(0x34);
    stateMachineBindState("NPCSearchST", 1);
    stateMachineSetStateFlags(0x28);
    stateMachineSetFailureTransition("ActionFailure", 6, 0x40000, 1);
    stateMachineAddTransition("PrevActionDone", 0x14);
    stateMachineAddTransition("PrevActionDone", 1);

    // Use interesting object
    stateMachineAddState("UseInterestingObject", -1);
    stateMachineSetParam(0x3f);
    stateMachineBindState("UseInterestingObjectST", 1);
    stateMachineSetStateFlags(0x3b);
    stateMachineSetFailureTransition("ioCollide", 6, 0x80, 1);
    stateMachineAddTransition("PrevActionDone", 1);
    stateMachineSetStateFlag(0x23);
    stateMachineSetStateFlags(4, 0x80, 1);

    // Object collision
    stateMachineAddState("ioCollide", -1);
    stateMachineBindState("NPCCollideST", 1);
    stateMachineAddTransition("PrevActionDone", 1);

    // Backup
    stateMachineAddState("Backup", -1);
    stateMachineBindState("NPCBackupST", 1);
    stateMachineSetStateFlags(0x28);
    stateMachineSetFailureTransition("ActionFailure", 6, 0x40000, 1);
    stateMachineAddTransition("PrevActionDone", 0x14);
    stateMachineAddTransition("PrevActionDone", 1);

    // Scared backup
    stateMachineAddState("ScaredBackup", -1);
    stateMachineSetParam(0x3c);
    stateMachineBindState("NPCBackupST", 1);
    stateMachineSetStateFlags(0x28);
    stateMachineSetFailureTransition("ActionFailure", 6, 0x40000, 1);
    stateMachineAddTransition("PrevActionDone", 0x14);
    stateMachineAddTransition("PrevActionDone", 1);

    // Backup from target
    stateMachineAddState("BackupFromTarget", -1);
    stateMachineSetParam(0x3c);
    stateMachineBindState("NPCBackupST", 1);
    stateMachineSetStateFlags(0x28);
    stateMachineSetFailureTransition("ActionFailure", 6, 0x40000, 1);
    stateMachineAddTransition("PrevActionDone", 0x14);
    stateMachineAddTransition("PrevActionDone", 1);

    // Crew command
    stateMachineAddState("CrewCommand", -1);
    stateMachineBindState("crewCommandStateTable", 1);
    stateMachineSetStateFlags(0x28);
    stateMachineSetFailureTransition("ActionFailure", 6, 0x40000, 1);
    stateMachineAddTransition("PrevActionDone", 0x14);
    stateMachineAddTransition("PrevActionDone", 1);

    // Combat flee
    stateMachineAddState("CombatFlee", -1);
    stateMachineSetParam(0x37);
    stateMachineBindState("combatFleeSM", 1);
    stateMachineSetStateFlags(0x28);
    stateMachineSetFailureTransition("ActionFailure", 6, 0x40000, 1);
    stateMachineAddTransition("PrevActionDone", 0x14);
    stateMachineAddTransition("PrevActionDone", 1);

    // Interior flee
    stateMachineAddState("InteriorFlee", -1);
    stateMachineSetParam(0x37);
    stateMachineSetStateFlags(0x21, 0xe30449ed, 1);
    stateMachineBindState("offPathFleeSM", 1);
    stateMachineSetStateFlags(0x28);
    stateMachineSetFailureTransition("ActionFailure", 6, 0x40000, 1);
    stateMachineAddTransition("PrevActionDone", 0x14);
    stateMachineAddTransition("PrevActionDone", 1);

    // Designer action
    stateMachineAddState("DesignerAction", -1);
    stateMachineBindState("NPCDesignerActionST", 1);
    stateMachineSetStateFlags(0x28);
    stateMachineAddTransition("PrevActionDone", 0x14);
    stateMachineAddTransition("PrevActionDone", 1);

    // Pickup weapon
    stateMachineAddState("PickupWeapon", -1);
    stateMachineBindState("GetToAndPickupWeaponST", 1);
    stateMachineSetStateFlags(0x28);
    stateMachineSetFailureTransition("ActionFailure", 6, 0x40000, 1);
    stateMachineAddTransition("PrevActionDone", 0x14);
    stateMachineAddTransition("PrevActionDone", 1);

    // Finalize the state machine, register it with name "NPCActionSM"
    stateMachineRegister(0x3601a991, &LAB_0077f910, "NPCActionSM"); // 0x004adc90
    stateMachineCleanup(); // 0x004ada40
    return;
}