// Xbox PDB: EARS::Modules::ArrestStateMachine::BuildArrestStateTable
// FUNC_NAME: PoliceArrestStateMachine::initializeStateTransitions
// Address: 0x00766ca0
// Role: Initializes the police arrest state machine by registering transitions, actions, and terminating states.
// Calls functions from the state machine system (EA EARS engine).
// The global _DAT_00d65840 is a pointer to the player's transform or position (likely Vector3).

void PoliceArrestStateMachine::initializeStateTransitions()
{
    // Get state machine ID for "policeArrestST"
    uint stateMachineId = getStateMachineId("policeArrestST");
    bool alreadyExists = isStateMachineCreated(stateMachineId);

    if (!alreadyExists)
    {
        // Create a new state machine instance with "policeArrestST" name and some runtime data
        void* runtimeData = getCurrentStateMachine(); // likely returns a pointer to a holder struct
        createStateMachine("policeArrestST", runtimeData);

        // Set sub-state "arrestInit" to default parameter (0xffffffff = -1)
        setStateParameter("arrestInit", -1);

        // Add transitions: from state "terminate" to action ID 0xf
        addTransition("terminate", 0xf);
        addTransition("terminate", 0xe);
        addTransition("terminate", 0xc);

        // Add transition from "moveToArrest" to action ID 4
        addTransition("moveToArrest", 4);
        setStateParameter("moveToArrest", -1);

        // Set the state table for "NPCChaseST" to index 1
        setStateTable("NPCChaseST", 1);

        addTransition("terminate", 0x13);
        addTransition("terminate", 0xe);
        addTransition("terminate", 0xc);
        addTransition("terminate", 0x12);

        addTransition("turnToArrestPlayer", 0x10);
        addTransition("ChaseFailed", 1);
        setStateParameter("turnToArrestPlayer", -1);

        setStateTable("turnToEntityTerminateTable", 1);

        addTransition("terminate", 0x12);
        addTransition("terminate", 0xe);
        addTransition("terminate", 0xc);

        addTransition("preArrestPlayer", 1);
        setStateParameter("preArrestPlayer", -1);

        addActionTrigger(0x12); // trigger action ID 0x12

        addTransition("arrestPlayerInVehicle", 0x11);
        addTransition("arrestPlayer", 4);
        setStateParameter("arrestPlayerInVehicle", -1);

        addActionTrigger(0xd);
        addActionTrigger(0x10);
        addActionTrigger(10);

        setStateTable("seekTargetTable", 1);

        addTransition("terminate", 0xd);

        // Teleport player to the position stored in global _DAT_00d65840
        addTeleportAction("teleportPlayer", 2, _DAT_00d65840, 1);

        setStateParameter("arrestPlayer", -1);

        addActionTrigger(0xe);
        addActionTrigger(0xd);
        addActionTrigger(10);

        addTransition("terminate", 0xd);

        addTeleportAction("teleportPlayer", 2, _DAT_00d65840, 1);

        setStateParameter("teleportPlayer", -1);

        addActionTrigger(0x11);
        addActionTrigger(0xb);

        addTransition("terminate", 0xe);
        addTransition("terminate", 0xb);

        setStateParameter("ChaseFailed", -1);

        addActionTrigger(0xf);
        addTransition("terminate", 4);
        setStateParameter("terminate", -1);

        addActionTrigger(0xc);
        addActionTrigger(2);

        // Register a transition rule with a hash of the state machine name (0xd65c2d1b)
        // and a callback at address LAB_00766bd0 (likely a transition code fragment)
        registerStateMachineTransition(0xd65c2d1b, &LAB_00766bd0, "ArrestStateMachine");

        finalizeStateMachine();
    }
    return;
}