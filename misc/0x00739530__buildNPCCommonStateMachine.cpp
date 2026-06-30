// FUNC_NAME: buildNPCCommonStateMachine
// Address: 0x00739530
// This function builds the CommonNPC state machine tables (ST) and the main state machine (SM).
// It registers states, transitions, substate machines, and default states for NPC AI.
// Called once during initialization.

void buildNPCCommonStateMachine(void)
{
    // Attempt to find the "CommonNPCST" state table; if it doesn't exist, build it.
    StateMachine* stateTable = StateMachine::findOrCreateStateMachine("CommonNPCST");
    if (stateTable == nullptr)
    {
        // Create and register the main state machine
        stateTable = StateMachine::create();
        StateMachine::setName(stateTable, "CommonNPCST");

        // Add a global transition (maybe to a default state ID -1, meaning no transition)
        StateMachine::addGlobalTransition(stateTable, DAT_00d63420, 0xffffffff); // DAT_00d63420 likely "global" or empty

        // Set default state with priority 5, condition 0x1c30f4d, enable
        StateMachine::setDefaultState(stateTable, 5, 0x1c30f4d, 1);

        // Add a state with ID 0x32
        StateMachine::addState(stateTable, 0x32);

        // Add transitions from various triggers to states
        StateMachine::addTransition(stateTable, "vehicleExit", 0x16);
        StateMachine::addTransition(stateTable, "vehicleBase", 0x1a);
        StateMachine::addTransition(stateTable, "tension", 4);

        // Remove/clear transition "tension" (ID -1 means clear all)
        StateMachine::removeTransition(stateTable, "tension", 0xffffffff);

        // Set default state for a sub-machine "TensionST"
        StateMachine::setSubMachineDefault(stateTable, "TensionST", 1);

        StateMachine::addTransition(stateTable, "painBranch", 0x21);
        StateMachine::addTransition(stateTable, "interrupt", 10);
        StateMachine::addTransition(stateTable, "GuardEnterVehicle", 0x17);
        StateMachine::removeTransition(stateTable, "interrupt", 0xffffffff);
        StateMachine::addState(stateTable, 0x2d);
        StateMachine::addTransitionWithCondition(stateTable, "selectCrewCommand", 6, 0x800000, 1);
        StateMachine::addTransitionWithCondition(stateTable, "crewRevive", 6, 0x10000, 1);
        StateMachine::addTransitionWithCondition(stateTable, DAT_00d633a4, 6, 0x400000, 1); // DAT_00d633a4 likely "backup" or similar
        StateMachine::addTransitionWithCondition(stateTable, "scriptedSequence", 6, 0x100, 1);
        StateMachine::addTransitionWithCondition(stateTable, "paired", 6, 4, 1);
        StateMachine::addTransitionWithCondition(stateTable, "falling", 6, 0x400, 1);
        StateMachine::addTransitionWithCondition(stateTable, "block", 6, 0x20000, 1);
        StateMachine::addTransitionWithCondition(stateTable, DAT_00d63370, 6, 1, 1); // DAT_00d63370 likely "idle" or "default"
        StateMachine::addTransitionWithCondition(stateTable, "vehicleDodge", 6, 0x200, 1);
        StateMachine::addTransitionWithCondition(stateTable, "paired", 6, 8, 1);
        StateMachine::addTransitionWithCondition(stateTable, "finishInterrupt", 6, 0x2000000, 1);
        StateMachine::addTransitionWithCondition(stateTable, "finishInterrupt", 6, 0x40, 1);
        StateMachine::addTransition(stateTable, "finishInterrupt", 4);
        StateMachine::addSubState(stateTable, 0x12); // probably add a substate group
        StateMachine::removeTransition(stateTable, "finishInterrupt", 0xffffffff);
        StateMachine::addTransition(stateTable, "painBranch", 0x21);
        StateMachine::addTransition(stateTable, "tension", 4);
        StateMachine::addSubState(stateTable, 0x2e);
        StateMachine::removeTransition(stateTable, DAT_00d633a4, 0xffffffff);
        StateMachine::setSubMachineDefault(stateTable, "npcSitObjectStateTable", 1);
        StateMachine::addTransition(stateTable, "finishInterrupt", 1);
        StateMachine::removeTransition(stateTable, "scriptedSequence", 0xffffffff);
        StateMachine::addState(stateTable, 0x15);
        StateMachine::addState(stateTable, 0x29);
        StateMachine::setSubMachineDefault(stateTable, "scriptedSequenceTable", 1);
        StateMachine::setDefaultState(stateTable, 5, 0x1c30f4d, 1);
        StateMachine::addTransition(stateTable, "painBranch", 0x21);
        StateMachine::addTransition(stateTable, "interrupt", 10);
        StateMachine::addTransition(stateTable, "finishInterrupt", 1);
        StateMachine::removeTransition(stateTable, "paired", 0xffffffff);
        StateMachine::addState(stateTable, 0x16);
        StateMachine::addState(stateTable, 0x18);
        StateMachine::setDefaultState(stateTable, 4, 0xd, 1);
        StateMachine::setSubMachineDefault(stateTable, "grabReactStateTable", 1);
        StateMachine::setSubMachineDefault(stateTable, "NPCF2FStateTable", 1);
        StateMachine::setDefaultState(stateTable, 3, 0xd, 1);
        StateMachine::addTransitionWithCondition(stateTable, "scriptedSequence", 6, 0x100, 1);
        StateMachine::addTransition(stateTable, DAT_00d63370, 0x11);
        StateMachine::addTransitionWithCondition(stateTable, "falling", 6, 0x400, 1);
        StateMachine::addTransitionWithCondition(stateTable, "stumble", 6, 0x800, 1);
        StateMachine::addTransition(stateTable, DAT_00e41d10, 0x10); // DAT_00e41d10 likely "death" or "knockdown"
        StateMachine::addTransition(stateTable, "recover", 1);
        StateMachine::removeTransition(stateTable, "vehicleDodge", 0xffffffff);
        StateMachine::setDefaultState(stateTable, 4, 0x200, 1);
        StateMachine::setDefaultState(stateTable, 0x1c, 0, 1);
        StateMachine::addState(stateTable, 0x1d);
        StateMachine::setDefaultState(stateTable, 0x1c, 1, 1);
        StateMachine::setSubMachineDefault(stateTable, "vehicleDodgeStateTable", 1);
        StateMachine::setDefaultState(stateTable, 3, 0x200, 1);
        StateMachine::addTransition(stateTable, "painBranch", 0x21);
        StateMachine::addTransitionWithCondition(stateTable, DAT_00d63370, 6, 1, 1);
        StateMachine::addTransition(stateTable, "recover", 1);
        StateMachine::removeTransition(stateTable, "falling", 0xffffffff);
        StateMachine::setDefaultState(stateTable, 4, 0x400, 1);
        StateMachine::setSubMachineDefault(stateTable, "fallingStateTable", 0);
        StateMachine::setDefaultState(stateTable, 3, 0x400, 1);
        StateMachine::addTransition(stateTable, DAT_00e41d10, 0x10);
        StateMachine::addTransition(stateTable, "recover", 1);
        StateMachine::removeTransition(stateTable, "stumble", 0xffffffff);
        StateMachine::setSubMachineDefault(stateTable, "stumbleStateTable", 1);
        StateMachine::addStateWithExitAction(stateTable, 8);
        StateMachine::addSubState(stateTable, 0x1a);
        StateMachine::addTransitionWithCondition(stateTable, "paired", 6, 4, 1);
        StateMachine::addTransitionWithCondition(stateTable, DAT_00d63370, 6, 1, 1);
        StateMachine::addTransitionWithCondition(stateTable, "falling", 6, 0x400, 1);
        StateMachine::addTransition(stateTable, "recover", 1);
        StateMachine::removeTransition(stateTable, "painBranch", 0xffffffff);
        StateMachine::addTransitionWithCondition(stateTable, "ladderRagdollDeath", 6, 0x1000000, 1);
        StateMachine::addTransition(stateTable, DAT_00d63370, 4);
        StateMachine::removeTransition(stateTable, "ladderRagdollDeath", 0xffffffff);
        StateMachine::addState(stateTable, 0x2f);
        StateMachine::addState(stateTable, 0x13);
        StateMachine::addStateWithExitAction(stateTable, 0x14);
        StateMachine::removeTransition(stateTable, DAT_00d63370, 0xffffffff);
        StateMachine::setDefaultState(stateTable, 4, 1, 1);
        StateMachine::setSubMachineDefault(stateTable, "painStateTable", 1);
        StateMachine::addState(stateTable, 0x16);
        StateMachine::addSubState(stateTable, 0x17);
        StateMachine::setDefaultState(stateTable, 3, 1, 1);
        StateMachine::addTransitionWithCondition(stateTable, "scriptedSequence", 0xf, 0x100, 1);
        StateMachine::addTransitionWithCondition(stateTable, "paired", 0xf, 4, 1);
        StateMachine::addTransitionWithCondition(stateTable, "paired", 0xf, 8, 1);
        StateMachine::addTransitionWithCondition(stateTable, "block", 0xf, 0x20000, 1);
        StateMachine::addTransition(stateTable, "deathOrRecover", 1);
        StateMachine::removeTransition(stateTable, "crewRevive", 0xffffffff);
        StateMachine::setSubMachineDefault(stateTable, "NPCReviveST", 1);
        StateMachine::addTransition(stateTable, "painBranch", 0x21);
        StateMachine::addTransition(stateTable, "finishInterrupt", 1);
        StateMachine::removeTransition(stateTable, "crewCommandRevive", 0xffffffff);
        StateMachine::setSubMachineDefault(stateTable, "NPCReviveST", 1);
        StateMachine::addTransition(stateTable, "painBranch", 0x21);
        StateMachine::addTransition(stateTable, "selectCrewCommand", 1);
        StateMachine::removeTransition(stateTable, "deathOrRecover", 0xffffffff);
        StateMachine::addTransition(stateTable, DAT_00e41d10, 0xc);
        StateMachine::addTransition(stateTable, "recover", 4);
        StateMachine::removeTransition(stateTable, "recover", 0xffffffff);
        StateMachine::setSubMachineDefault(stateTable, "recoverStateTable", 1);
        StateMachine::addTransition(stateTable, "painBranch", 0x21);
        StateMachine::addTransitionWithCondition(stateTable, DAT_00d63370, 6, 1, 1);
        StateMachine::addTransitionWithCondition(stateTable, "paired", 6, 4, 1);
        StateMachine::addTransitionWithCondition(stateTable, "scriptedSequence", 6, 0x100, 1);
        StateMachine::addTransitionWithCondition(stateTable, "paired", 6, 8, 1);
        StateMachine::addTransition(stateTable, "finishInterrupt", 1);
        StateMachine::removeTransition(stateTable, DAT_00e41d10, 0xffffffff);
        StateMachine::setSubMachineDefault(stateTable, "NPCDeathST", 1);
        StateMachine::addTransition(stateTable, "finishInterrupt", 1);
        StateMachine::removeTransition(stateTable, "forceCrewCommand", 0xffffffff);
        StateMachine::setDefaultState(stateTable, 0x20, 0, 1);
        StateMachine::addState(stateTable, 0x29);
        StateMachine::setSubMachineDefault(stateTable, "crewCommandStateTable", 1);
        StateMachine::addTransition(stateTable, "painBranch", 0x21);
        StateMachine::addTransitionWithCondition(stateTable, "crewCommandRevive", 6, 0x10000, 1);
        StateMachine::addTransitionWithCondition(stateTable, "scriptedSequence", 0xf, 0x100, 1);
        StateMachine::addTransitionWithCondition(stateTable, "selectCrewCommand", 6, 0x800000, 1);
        StateMachine::addTransition(stateTable, "GuardEnterVehicle", 0x17);
        StateMachine::addTransition(stateTable, "tension", 0x23);
        StateMachine::addTransition(stateTable, "tension", 1);
        StateMachine::addTransition(stateTable, "crewCommandBackup", 0x1d);
        StateMachine::removeTransition(stateTable, "suggestCrewCommand", 0xffffffff);
        StateMachine::setDefaultState(stateTable, 0x20, 0, 1);
        StateMachine::addState(stateTable, 0x29);
        StateMachine::setSubMachineDefault(stateTable, "crewCommandStateTable", 1);
        StateMachine::addTransition(stateTable, "painBranch", 0x21);
        StateMachine::addTransitionWithCondition(stateTable, "crewCommandRevive", 6, 0x10000, 1);
        StateMachine::addTransitionWithCondition(stateTable, "selectCrewCommand", 6, 0x800000, 1);
        StateMachine::addTransition(stateTable, "interruptedCrewCommandChatter", 10);
        StateMachine::addTransition(stateTable, "GuardEnterVehicle", 0x17);
        StateMachine::addTransition(stateTable, "tension", 0x23);
        StateMachine::addTransition(stateTable, "tension", 1);
        StateMachine::addTransition(stateTable, "crewCommandBackup", 0x1d);
        StateMachine::removeTransition(stateTable, "interruptedCrewCommandChatter", 0xffffffff);
        StateMachine::setDefaultState(stateTable, 0x20, 6, 1);
        StateMachine::addTransition(stateTable, "interrupt", 4);
        StateMachine::removeTransition(stateTable, "selectCrewCommand", 0xffffffff);
        StateMachine::addState(stateTable, 0x30);
        StateMachine::addTransition(stateTable, "ForceCrewReturn", 0x12);
        StateMachine::addTransition(stateTable, "forceCrewCommand", 0x13);
        StateMachine::addTransition(stateTable, "CrewReturn", 0x14);
        StateMachine::addTransition(stateTable, "suggestCrewCommand", 0x15);
        StateMachine::removeTransition(stateTable, "ForceCrewReturn", 0xffffffff);
        StateMachine::setDefaultState(stateTable, 0x20, 5, 1);
        StateMachine::addState(stateTable, 0x24);
        StateMachine::addState(stateTable, 0x28);
        StateMachine::setSubMachineDefault(stateTable, "NPCFollowST", 1);
        StateMachine::addTransition(stateTable, "painBranch", 0x21);
        StateMachine::addTransition(stateTable, "crewCommandBackup", 0x1d);
        StateMachine::addTransitionWithCondition(stateTable, "crewCommandRevive", 6, 0x10000, 1);
        StateMachine::addTransitionWithCondition(stateTable, "selectCrewCommand", 6, 0x800000, 1);
        StateMachine::addTransition(stateTable, "tension", 0x1c);
        StateMachine::addTransition(stateTable, "GuardEnterVehicle", 0x17);
        StateMachine::addTransition(stateTable, "tension", 1);
        StateMachine::removeTransition(stateTable, "CrewReturn", 0xffffffff);
        StateMachine::setDefaultState(stateTable, 0x20, 5, 1);
        StateMachine::addState(stateTable, 0x24);
        StateMachine::addState(stateTable, 0x27);
        StateMachine::setSubMachineDefault(stateTable, "NPCFollowST", 1);
        StateMachine::addTransitionWithCondition(stateTable, "crewCommandRevive", 6, 0x10000, 1);
        StateMachine::addTransition(stateTable, "painBranch", 0x21);
        StateMachine::addTransition(stateTable, "crewCommandBackup", 0x1d);
        StateMachine::addTransitionWithCondition(stateTable, "selectCrewCommand", 6, 0x800000, 1);
        StateMachine::addTransition(stateTable, "tension", 0x1c);
        StateMachine::addTransition(stateTable, "GuardEnterVehicle", 0x17);
        StateMachine::addTransition(stateTable, "tension", 1);
        StateMachine::removeTransition(stateTable, "crewCommandBackup", 0xffffffff);
        StateMachine::setSubMachineDefault(stateTable, "NPCBackupST", 1);
        StateMachine::addTransition(stateTable, "selectCrewCommand", 1);
        StateMachine::removeTransition(stateTable, "Backup", 0xffffffff);
        StateMachine::setSubMachineDefault(stateTable, "NPCBackupST", 1);
        StateMachine::addTransition(stateTable, "tension", 1);
        StateMachine::removeTransition(stateTable, "GuardEnterVehicle", 0xffffffff);
        StateMachine::addState(stateTable, 0x23);
        StateMachine::addState(stateTable, 0x24);
        StateMachine::addState(stateTable, 0x27);
        StateMachine::setSubMachineDefault(stateTable, "GetToAndIntoVehicleST", 1);
        StateMachine::addTransition(stateTable, "painBranch", 0x21);
        StateMachine::addTransition(stateTable, "vehicleExit", 0x18);
        StateMachine::addTransition(stateTable, "tension", 0x19);
        StateMachine::addTransition(stateTable, "vehicleBase", 0x1a);
        StateMachine::addTransition(stateTable, "interrupt", 10);
        StateMachine::addTransition(stateTable, "Backup", 0x1d);
        StateMachine::addTransition(stateTable, "tension", 1);
        StateMachine::removeTransition(stateTable, "vehicleExit", 0xffffffff);
        StateMachine::addState(stateTable, 0x26);
        StateMachine::setSubMachineDefault(stateTable, "vehicleExitStateTable", 1);
        StateMachine::addTransitionWithCondition(stateTable, "interrupt", 5, 0x100, 1);
        StateMachine::addTransition(stateTable, "tension", 1);
        StateMachine::removeTransition(stateTable, "vehicleBase", 0xffffffff);
        StateMachine::setDefaultState(stateTable, 4, 1, 1);
        StateMachine::setSubMachineDefault(stateTable, "NPCVehicleST", 1);
        StateMachine::addTransition(stateTable, "vehicleExit", 0x18);
        StateMachine::addTransition(stateTable, "vehicleExit", 0x16);
        StateMachine::addTransition(stateTable, "tension", 1);
        StateMachine::setDefaultState(stateTable, 3, 1, 1);
        StateMachine::removeTransition(stateTable, "block", 0xffffffff);
        StateMachine::addState(stateTable, 0x2b);
        StateMachine::addTransition(stateTable, "painBranch", 0x21);
        StateMachine::addTransitionWithCondition(stateTable, DAT_00d63370, 6, 1, 1);
        StateMachine::addTransitionWithCondition(stateTable, "paired", 6, 4, 1);
        StateMachine::addTransitionWithPriority(stateTable, "preCounterAttack", 0x1e, DAT_00d5842c, 1);
        StateMachine::addTransitionWithPriority(stateTable, "finishInterrupt", 2, DAT_00d5842c, 1);
        StateMachine::addSubState(stateTable, 0x2c);
        StateMachine::removeTransition(stateTable, "preCounterAttack", 0xffffffff);
        StateMachine::addState(stateTable, 0x2a);
        StateMachine::addTransition(stateTable, "counterAttack", 4);
        StateMachine::removeTransition(stateTable, "counterAttack", 0xffffffff);
        StateMachine::setDefaultState(stateTable, 4, 1, 1);
        StateMachine::setSubMachineDefault(stateTable, "NPCPunchST", 1);
        StateMachine::addSubState(stateTable, 0x22);
        StateMachine::addTransition(stateTable, "counterAttack", 0x1f);
        StateMachine::addTransition(stateTable, "painBranch", 0x21);
        StateMachine::addTransition(stateTable, "recover", 0x20);
        StateMachine::addTransitionWithCondition(stateTable, "scriptedSequence", 0xf, 0x100, 1);
        StateMachine::addTransitionWithCondition(stateTable, "paired", 0xf, 4, 1);
        StateMachine::setDefaultState(stateTable, 3, 1, 1);
        StateMachine::registerMachine(stateTable, 0x1a2bb90, &LAB_007393f0, "CommonNPCSM");
        StateMachine::finalize(stateTable);
    }
}