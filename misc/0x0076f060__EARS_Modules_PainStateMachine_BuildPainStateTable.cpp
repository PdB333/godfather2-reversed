// Xbox PDB: EARS_Modules_PainStateMachine_BuildPainStateTable
// FUNC_NAME: PainStateMachine::initialize
void PainStateMachine::initialize(void)
{
    // Attempt to retrieve the "painStateTable" resource
    void* painStateTable = findStateTable("painStateTable");
    int isExisting = isStateTableValid(painStateTable);
    if (isExisting != 0) {
        return; // Already initialised
    }

    // Create a new state machine context for pain states
    void* machineCtx = createNewStateMachine();
    registerStateTable("painStateTable", machineCtx);

    // ---- painInit (initial state, default transition to 0xFFFFFFFF) ----
    setInitialState("painInit", 0xFFFFFFFF);
    addState(0x11); // standing hit? (offset 0x11)
    addState(0x1B); // crouch hit? (0x1B)
    addTransitionWithFlags(5, 1, 1); // entry from painInit to standing with condition

    // Transitions from painInit to various states
    addDirectState("death_init_recoverable", 0x16); // from painInit to death_init_recoverable
    addDirectState("death_init", 0x0E);
    addDirectState("crouching", 0x17);
    addTimedTransition("ground_hit", 0x0C, 3, 1); // from ground_hit after delay
    addTimedTransition("crawl_hit", 0x0C, 2, 1);
    addTimedTransition("kneel_hit", 0x0C, 1, 1);
    addTimedTransition("standing", 0x0C, 0, 1);
    addDirectState("terminate", 4);
    setInitialState("death_init_recoverable", 0xFFFFFFFF);

    // ---- death_init_recoverable sub-states ----
    addState(0x1A);
    addState(0x22);
    addSimpleState(8);       // non‑string state ID
    addStateWithPriority(0x16);
    addStateWithPriority(0x1B);
    addTimedTransition("terminate", 10, 0x40, 1);
    addDirectState("terminate", 7);
    setInitialState("death_init", 0xFFFFFFFF);

    // ---- death_init sub-states ----
    addState(0x1D);
    addDirectState("stumble_death", 0x0F);
    addDirectState("death", 4);
    setInitialState("stumble_death", 0xFFFFFFFF);

    // ---- stumble_death sub-state (stumbleStateTable) ----
    addState(0x1C);
    pushStateTable("stumbleStateTable", 1);
    addSimpleState(0x1F);
    addSimpleState(0x1E);
    addSimpleState(8);
    addDirectState("stumble_fall", 0x13);
    addDirectState("death", 1);
    setInitialState("stumble_fall", 0xFFFFFFFF);

    // ---- fallingStateTable ----
    pushStateTable("fallingStateTable", 1);
    addSimpleState(0x1F);
    addSimpleState(0x1E);
    addSimpleState(8);
    addDirectState("death", 1);
    setInitialState("death", 0xFFFFFFFF);

    // ---- death (main death tree) ----
    addState(0x1A);
    addState(0x15);
    addSimpleState(0x1F);
    addSimpleState(0x1E);
    addSimpleState(8);
    addSimpleState(0x18); // helpless state?
    addStateWithPriority(0x16);
    addStateWithPriority(0x1B);
    addDirectState("tommyGunDeathHitReacts", 0x11);
    addTimedTransition("terminate", 10, 0x40, 1);
    addDirectState("terminate", 0x18);
    setInitialState("tommyGunDeathHitReacts", 0xFFFFFFFF);

    // ---- tommyGunDeathHitReacts ----
    addState(0x11);
    addState(0x13);
    addState(0x0C);
    addDirectState("tommyGunDeathHitReacts", 0x11);
    addDirectState("death", 0x12);
    addDirectState("death", 0x18);
    setInitialState("standing", 0xFFFFFFFF);
    addDirectState("death", 0x0E);
    addTimedTransition("kneecapHit", 10, 0x80, 1);
    addDirectState("stumbleHit", 0x10);
    addDirectState("standH2HHit", 0x15);
    addDirectState("standHit", 4);
    setInitialState("crouching", 0xFFFFFFFF);

    // ---- crouching sub-state ----
    addTimedTransition("kneecapHit", 10, 0x80, 1);
    addDirectState("crouchHit", 4);
    setInitialState("crouchHit", 0xFFFFFFFF);

    // ---- crouchHit ----
    addState(0x0D);
    addSimpleState(8);
    addSimpleState(0x14);
    addSimpleState(0x18);
    addDirectState("death", 0x0E);
    addDirectState("terminate", 7);
    setInitialState("stumbleHit", 0xFFFFFFFF);

    // ---- stumbleHit ----
    addState(0x1C);
    pushStateTable("stumbleStateTable", 1);
    addSimpleState(8);
    addDirectState("stumble_fall", 0x13);
    addDirectState("terminate", 1);
    addDirectState("forceFall", 0x14);
    setInitialState("forceFall", 0xFFFFFFFF);

    // ---- forceFall ----
    addState(0x20);
    addDirectState("terminate", 4);
    setInitialState("standHit", 0xFFFFFFFF);

    // ---- standHit ----
    addState(0x13);
    addState(0x0B);
    addSimpleState(8);
    addSimpleState(0x14);
    addSimpleState(0x19);
    addTimedTransition("painInit", 6, 1, 1);
    addDirectState("death", 0x0E);
    addDirectState("terminate", 0x0D);
    addDirectState("terminate", 0x18);
    setInitialState("standH2HHit", 0xFFFFFFFF);

    // ---- standH2HHit ----
    addState(0x13);
    addState(0x0B);
    pushStateTable("trackToPositionAndDirectionStateTable", 1);
    addSimpleState(8);
    addSimpleState(0x14);
    addTimedTransition("painInit", 6, 1, 1);
    addDirectState("death", 0x0E);
    addDirectState("terminate", 0x0D);
    addDirectState("standH2HHitTrans", 1);
    setInitialState("standH2HHitTrans", 0xFFFFFFFF);

    // ---- standH2HHitTrans ----
    addState(0x13);
    addState(0x21);
    addSimpleState(8);
    addSimpleState(0x14);
    addTimedTransition("painInit", 6, 1, 1);
    addDirectState("death", 0x0E);
    addDirectState("terminate", 0x0D);
    addDirectState("terminate", 0x18);
    setInitialState("kneecapHit", 0xFFFFFFFF);

    // ---- kneecapHit ----
    addSimpleState(8);
    addState(0x17);
    addSimpleState(0x14);
    addSimpleState(0x18);
    addDirectState("death", 0x0E);
    addDirectState("terminate", 7);
    setInitialState("kneel_hit", 0xFFFFFFFF);

    // ---- kneel_hit ----
    addState(0x13);
    addState(0x0E);
    addSimpleState(8);
    addDirectState("death", 0x0E);
    addTimedTransition("kneelToGround", 10, 4, 1);
    addTimedTransition("painInit", 6, 1, 1);
    addDirectState("terminate", 0x0D);
    addDirectState("terminate", 7);
    setInitialState("kneelToGround", 0xFFFFFFFF);

    // ---- kneelToGround ----
    addState(0x0F);
    addSimpleState(8);
    addSimpleState(0x18);
    addDirectState("death", 0x0E);
    addDirectState("terminate", 7);
    setInitialState("crawl_hit", 0xFFFFFFFF);

    // ---- crawl_hit ----
    addState(0x13);
    addState(0x10);
    addSimpleState(8);
    addDirectState("death", 0x0E);
    addTimedTransition("painInit", 6, 1, 1);
    addDirectState("terminate", 0x0D);
    addDirectState("terminate", 7);
    setInitialState("ground_hit", 0xFFFFFFFF);

    // ---- ground_hit ----
    addState(0x13);
    addState(0x10);
    addSimpleState(8);
    addDirectState("death", 0x0E);
    addDirectState("terminate", 0x0D);
    addDirectState("terminate", 7);
    setInitialState("terminate", 0xFFFFFFFF);

    // ---- terminate (final) ----
    addState(0x12);
    addState(0x13);
    addState(2);
    registerPainMachine("PainStateMachine", &__PainStateMachine_callback, "PainStateMachine");
    finalizeStateMachine();
}

// The following are declarations for the underlying helper functions.
// They are defined elsewhere (e.g. in state machine manager).

void* findStateTable(const char* name);
int isStateTableValid(void* table);
void* createNewStateMachine(void);
void registerStateTable(const char* name, void* machine);

void setInitialState(const char* stateName, int initialStateID);
void addState(int stateID);
void addSimpleState(int stateID);
void addStateWithPriority(int stateID);
void addTransitionWithFlags(int from, int to, int flags);
void addDirectState(const char* from, int to);
void addTimedTransition(const char* from, int to, int delay, int flags);
void pushStateTable(const char* tableName, int arg);
void registerPainMachine(const char* name, void* callback, const char* debugName);
void finalizeStateMachine(void);