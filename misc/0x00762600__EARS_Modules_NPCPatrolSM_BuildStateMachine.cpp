// Xbox PDB: EARS::Modules::NPCPatrolSM::BuildStateMachine
// FUNC_NAME: NPCPatrolSM::initStateMachine
void NPCPatrolSM::initStateMachine(void)
{
    uint stateId;

    // Allocate a unique ID for the patrol state machine
    stateId = getUniqueStateId();

    // Create the top-level state
    createState("NPCPatrolST", stateId);
    addStateTransition("NPCPatrolST", -1);

    // Set initial state to state ID 3 with flags 0x20 and 1
    setInitialState(3, 0x20, 1);

    // Add actions for various states
    addAction(0xb);
    addStringAction("initPatrol", 0x12);
    addStringAction(STR_idle, 0xb);
    addStateTransition(STR_idle, -1);

    addAction(10);
    addAction(0xb);
    addAction(8);
    addTransitionCondition(8);
    addTransitionCondition(0xe);
    addStringAction("testOnGraph", 0xc);
    addStateTransition("testOnGraph", -1);

    addStringAction("initPatrol", 0x12);
    addStringAction("pathToGraph", 1);
    addStateTransition("pathToGraph", -1);

    // Add "FollowPathST" as an initial state
    addStateMachineState("FollowPathST", 1);
    addAction(0xc);
    addTransitionCondition(0xe);
    addStringAction(STR_idle, 0xf);
    addStringAction(STR_patrol, 0x13);
    addStringAction("initPatrol", 0xd);
    addStateTransition("initPatrol", -1);

    addAction(0xd);
    addTransitionCondition(0xe);
    addStringAction("patrolGraph", 0xe);
    addStateTransition("patrolGraph", -1);

    addTransitionCondition(0xe);
    addStateMachineState("OnGraphPathingST", 1);

    addStringAction(STR_patrol, 0x13);
    addStringAction(STR_idle, 0x10);

    // Set the update function for state 0x7a086ec7 to the patrol update routine
    setStateUpdateFunction(0x7a086ec7, &NPCPatrolSM::patrolUpdate, "NPCPatrolSM");

    // Finalize the state machine
    finalizeStateMachine();
}