// Xbox PDB: EARS::Modules::RangedMovementSM::BuildStateMachine
// FUNC_NAME: RangedMovementSM::buildMachine
#include <string>

// Forward declarations of state machine helper types (simplified)
class StateMachineManager;
class StateMachine;

// Hypothetical helper functions (these would be defined elsewhere)
extern StateMachineManager* getStateMachineManager(); // FUN_009c8f80
extern StateMachine* createStateMachine(const char* name, StateMachineManager* mgr); // FUN_004ad9d0
extern void setInitialState(StateMachine* sm, const char* stateName, int id); // FUN_004adae0
extern void setStateCapacity(StateMachine* sm, int capacity); // FUN_004acf70
extern void addState(StateMachine* sm, const char* name, int id); // FUN_004acc70
extern void addStateInternal(StateMachine* sm, int id); // FUN_004acff0 (no name)
extern void setTransition(StateMachine* sm, const char* from, const char* to, int eventId); // FUN_004acf10 (approx)
extern void setStateFlags(StateMachine* sm, int id); // FUN_004ad070
extern void addTransitionWithEvent(StateMachine* sm, int eventId, int mask, int flag); // FUN_004ad0f0
extern void addTransitionWithCondition(StateMachine* sm, const char* conditionName, int eventId, int mask, int flag); // FUN_004acd20
extern void registerStateMachine(StateMachine* sm, const char* name, void* label); // FUN_004adc90
extern void finishStateMachineBuild(StateMachine* sm); // FUN_004ada40

void buildRangedMovementStateMachine(void)
{
    StateMachineManager* mgr = getStateMachineManager();
    StateMachine* sm = createStateMachine("RangedMovementST", mgr);

    // Initial state setup (possibly overwritten later)
    setInitialState(sm, "initialAim", -1);
    setStateCapacity(sm, 0xc);

    // Define states and transitions
    addState(sm, "terminate", 0x1a);
    addState(sm, "terminate", 10);
    addState(sm, "findBackupPos", 0xf);
    addState(sm, "findMoveCloserPos", 0x10);
    addState(sm, "findBetterPos", 0x11);
    addState(sm, "reload", 0x14);
    addState(sm, "aim", 4); // DAT_00d64a84 is probably "aim"
    setInitialState(sm, "aim", -1);

    // Second block of states (maybe a different sub-machine)
    addState(sm, "terminate", 0x1a);
    addState(sm, "terminate", 10);
    addState(sm, "findBackupPos", 0xf);
    addState(sm, "findMoveCloserPos", 0x10);
    addState(sm, "findBetterPos", 0x11);
    addState(sm, "shoot", 0xb);
    addState(sm, "gotoShootLocStrafe", 0x15);
    addState(sm, "gotoLastVisiblePos", 0x16);
    addState(sm, "aimCantSee", 0x18);
    addState(sm, "reload", 0x14);
    addState(sm, "findBetterPos", 0x19);
    addState(sm, "aimAnim", 4);
    setInitialState(sm, "aimAnim", -1);
    setStateCapacity(sm, 10);
    addStateInternal(sm, 0x13); // some internal state
    setTransition(sm, "seekTargetTable", 1); // possibly set initial transition

    // Add states again (likely duplicate definitions for different contexts)
    addState(sm, "terminate", 0x1a);
    addState(sm, "terminate", 10);
    addState(sm, "findBackupPos", 0xf);
    addState(sm, "findMoveCloserPos", 0x10);
    addState(sm, "findBetterPos", 0x11);
    addState(sm, "shoot", 0xb);
    addState(sm, "gotoShootLocStrafe", 0x15);
    addState(sm, "gotoLastVisiblePos", 0x16);
    addState(sm, "aimCantSee", 0x18);
    addState(sm, "reload", 0x14);
    addState(sm, "findBetterPos", 0x19);
    setStateFlags(sm, 0x14); // reload flags?
    setStateFlags(sm, 0xb);  // shoot flags?
    setInitialState(sm, "aimCantSee", -1);
    setStateCapacity(sm, 10);
    addStateInternal(sm, 0x13);

    // More states
    addState(sm, "terminate", 0x1a);
    addState(sm, "terminate", 10);
    addState(sm, "findBackupPos", 0xf);
    addState(sm, "findMoveCloserPos", 0x10);
    addState(sm, "shoot", 0xb);
    addState(sm, "findBetterPos", 0x11);
    addState(sm, "gotoShootLocStrafe", 0x15);
    addState(sm, "gotoSomePlace", 0x16);
    setStateFlags(sm, 0x14);
    setStateFlags(sm, 0xb);
    setInitialState(sm, "gotoSomePlace", -1);
    addState(sm, "gotoLastVisiblePos", 0x17);
    addState(sm, "findBetterPos", 4);
    setInitialState(sm, "shoot", -1);
    setStateCapacity(sm, 0x19);
    setTransition(sm, "ShootST", 1);
    addState(sm, "reloadOrAim", 1);
    setInitialState(sm, "reloadOrAim", -1);
    addState(sm, "reload", 0x14);
    addState(sm, "aim", 4);
    setInitialState(sm, "reload", -1);
    setTransition(sm, "ReloadGunST", 1);
    addState(sm, "terminate", 0x1a);
    addState(sm, "aim", 1);
    setInitialState(sm, "findBetterPos", -1);
    setStateCapacity(sm, 0xe);
    setStateCapacity(sm, 0xd);
    addState(sm, "terminate", 0x1a);
    addState(sm, "terminate", 10);
    addState(sm, "reloadOrAim", 0xc);
    addState(sm, "strafe", 0xd);
    addState(sm, "findBetterPosAnim", 4);
    setStateFlags(sm, 0xf);
    setInitialState(sm, "findBetterPosAnim", -1);
    setStateCapacity(sm, 10);
    setStateCapacity(sm, 0xe);
    setStateCapacity(sm, 8);
    addStateInternal(sm, 8);
    addStateInternal(sm, 0xd);
    addState(sm, "terminate", 0x1a);
    addState(sm, "terminate", 10);
    addState(sm, "reloadOrAim", 0xc);
    addState(sm, "strafe", 0xd);
    setStateFlags(sm, 0xf);
    setStateFlags(sm, 0xb);
    setInitialState(sm, "strafe", -1);
    setStateCapacity(sm, 0x10);
    setTransition(sm, "NPCStrafeST", 1);
    setTransition(sm, "ContinualBurstFireST", 1);
    addState(sm, "terminate", 0x1a);
    addState(sm, "terminate", 10);
    addState(sm, "reload", 0x14);
    addState(sm, "findBackupPos", 0xf);
    addState(sm, "findMoveCloserPos", 0x10);
    addState(sm, "strafeEnd", 0x1b);
    setInitialState(sm, "strafeEnd", -1);
    setTransition(sm, "ContinualBurstFireST", 1);
    addState(sm, "terminate", 0x1a);
    addState(sm, "terminate", 10);
    addState(sm, "findBackupPos", 0xf);
    addState(sm, "findMoveCloserPos", 0x10);
    addState(sm, "findBetterPos", 0x11);
    addState(sm, "reloadOrAim", 4);
    setInitialState(sm, "gotoShootLocStrafe", -1);
    addTransitionWithEvent(sm, 5, 0x4000, 1);
    setTransition(sm, "NPCStrafeST", 1);
    setTransition(sm, "ContinualBurstFireST", 1);
    addState(sm, "reloadWhileGoingToShootLocStrafe", 0x14);
    addState(sm, "shoot", 0xb);
    addTransitionWithCondition(sm, "pathingError", 6, 0x4000, 1);
    addState(sm, "reachedWithoutCanShoot", 0x1b);
    setInitialState(sm, "reachedWithoutCanShoot", -1);
    setStateCapacity(sm, 0x1a);
    addState(sm, "reloadOrAim", 4);
    setInitialState(sm, "reloadWhileGoingToShootLocStrafe", -1);
    setTransition(sm, "ReloadGunST", 1);
    addState(sm, "terminate", 0x1a);
    addState(sm, "gotoShootLocStrafe", 1);
    setInitialState(sm, "pathingError", -1);
    setStateCapacity(sm, 0x1a);
    addState(sm, "reloadOrAim", 4);
    setInitialState(sm, "gotoLastVisiblePos", -1);
    setStateCapacity(sm, 0x15);
    setTransition(sm, "NPCStrafeST", 1);
    setTransition(sm, "ContinualBurstFireST", 1);
    addState(sm, "reload", 0x14);
    addState(sm, "shoot", 0xb);
    addState(sm, "reloadOrAim", 0x1b);
    setInitialState(sm, "findBackupPos", -1);
    setStateCapacity(sm, 0x11);
    addState(sm, "backup", 4);
    setInitialState(sm, "backup", -1);
    setTransition(sm, "NPCStrafeST", 1);
    setTransition(sm, "ContinualBurstFireST", 1);
    addState(sm, "terminate", 0x1a);
    addState(sm, "reload", 0x14);
    addState(sm, "terminate", 10);
    addState(sm, "findMoveCloserPos", 0x10);
    addState(sm, "reloadOrAim", 0x12);
    addState(sm, "reloadOrAim", 0x1b);
    setInitialState(sm, "findMoveCloserPos", -1);
    setStateCapacity(sm, 0x12);
    addState(sm, "reloadOrAim", 0x1c);
    addState(sm, "moveCloser", 4);
    setInitialState(sm, "strafeOutOfRange", -1);
    setStateCapacity(sm, 0x18);
    addState(sm, "reloadOrAim", 4);
    setInitialState(sm, "moveCloser", -1);
    setTransition(sm, "NPCStrafeST", 1);
    setTransition(sm, "ContinualBurstFireST", 1);
    addState(sm, "terminate", 0x1a);
    addState(sm, "reload", 0x14);
    addState(sm, "terminate", 10);
    addState(sm, "findBackupPos", 0xf);
    addState(sm, "reloadOrAim", 0x13);
    addState(sm, "reloadOrAim", 0x1b);
    setInitialState(sm, "terminate", -1);
    setStateCapacity(sm, 2);

    // Register the state machine with the engine
    registerStateMachine(sm, "RangedMovementSM", (void*)0x00750c30); // label address
    finishStateMachineBuild(sm);
    return;
}