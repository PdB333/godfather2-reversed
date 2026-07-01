// FUNC_NAME: PlayerF2FSM::processStateEvent
// Address: 0x0092c1d0
// Handles state transitions: checks current target (this+0x50), sets animation/alpha flags,
// and registers timer callbacks for sequence advancement.

void __thiscall PlayerF2FSM::processStateEvent(void)
{
    int someHandle;   // uVar1 - returned by getSingleton()
    int targetPtr;    // iVar2 - pointer to target object (player/entity)
    void* timerCb;    // puVar3 - timer callback address

    someHandle = getSingleton(); // FUN_0090a5a0 - e.g., GameManager::get()

    if (*(int*)(this + 0x50) == 0) {
        // No active target stored in this object
        getSingleton(); // redundant? second call, result discarded
        targetPtr = getTargetObject();   // FUN_00791300
    } else {
        targetPtr = getAltTargetObject(); // FUN_0079f9d0
    }

    if (*(int*)(this + 0x50) == 0) {
        if (targetPtr == 0) {
            // No target acquired, attempt to find one
            prepareSomething();        // FUN_007915b0
            targetPtr = checkSomething(someHandle); // FUN_008c12a0
            if (targetPtr == 0) {
                return;                // still no target – exit
            }
            processAfterCheck();       // FUN_008c81d0
            *(bool*)(this + 0x184) = true;                // flag: target available
            addTimer(this + 0x14, &LAB_005bfc10, 0);     // schedule common callback
            timerCb = &LAB_0092bc20;   // specific callback for this path
        } else {
            // Target exists, check a bit at offset 0x1f58
            if ((*(uint*)(targetPtr + 0x1f58) >> 0x19 & 1) == 0) goto LAB_0092c2c3;
            *(bool*)(this + 0x185) = true;                // flag: animation/state
            playSoundAnimation();                         // thunk_FUN_00735f80 – play audio/animation
            setAlpha(1.0f);                               // FUN_004706f0 – set visibility/opacity
            addTimer(this + 0x14, &LAB_005bfc10, 0);     // same common callback
            timerCb = &LAB_0092bc90;   // different callback for this path
        }
        addTimer(this + 0x14, timerCb, 0);               // schedule the path‑specific callback
        addTimer(this + 0x14, &LAB_005bfbe0, 0);         // schedule another callback (cleanup?)
    } else {
LAB_0092c2c3:
        if (targetPtr != 0) {
            cleanupTarget(targetPtr);                     // FUN_009bcb30 – release/destroy target
            releaseResource(*(int*)(this + 0x54));        // FUN_009bbc50 – free associated resource
            // Virtual dispatch via a global object (DAT_01130000) vtable+0x28
            (*(void (__thiscall**)(void))(*DAT_01130000 + 0x28))();
            return;
        }
    }
}