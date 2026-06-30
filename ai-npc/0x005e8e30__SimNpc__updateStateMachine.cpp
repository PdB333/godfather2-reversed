// FUNC_NAME: SimNpc::updateStateMachine
void __thiscall SimNpc::updateStateMachine(void) {
    char conditionResult;
    void* pTarget; // eax
    uint state; // uVar2
    void* obj; // iVar3

    state = *(uint*)(this + 0x484); // m_state (AI state)
    if (4 < state) {
        return;
    }
    do {
        switch(state) {
        case 2: // State 2: likely "attack" or "interact"
            // Check via global manager if we can proceed
            conditionResult = (**(code (**)(void))(*g_pGlobalManager + 0x8c))(*(undefined4*)(this + 0x1d0)); // m_subObj
            if (conditionResult != '\0') {
                return; // If condition met, exit
            }
            obj = (void*)getSomeObject(); // FUN_005e97d0 – get a target or tool
            updateMovement(); // FUN_005e9730 – update position/animation
            if (obj == NULL) {
                return;
            }
            if (*(char*)((int)obj + 0x68) == '\0') {
                return;
            }
            performAction(obj, this + 0x210, *(undefined4*)(this + 0x20c)); // FUN_005e9380
            return;
        case 3: // State 3: do nothing? (e.g., stun, wait)
            return;
        case 4: // State 4: specific check
            if (*(char*)(this + 0x285) == '\0') { // m_flag2
                updateMovement(); // FUN_005e9730
            }
            // Fall through to case 1
        case 1: // State 1: idle or patrol
            conditionResult = (char)checkCondition(); // FUN_005e8f20
            if (conditionResult == '\0') {
                return;
            }
            updateMovement(); // FUN_005e9730
            return;
        }
        // If state is not handled by switch (i.e., state 0 or default)
        if (*(int*)(this + 0x1fc) == 0) { // m_flag1
            return;
        }
        updateStateInternal(this); // FUN_005e9610 – internal state transition
        state = *(uint*)(this + 0x484); // re-read state
        if (state == 0) {
            return;
        }
        if (4 < state) {
            return;
        }
    } while( true );
}