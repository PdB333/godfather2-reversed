// FUNC_NAME: PlayerStateMachine::handleAction
// Function at 0x0073bb30: Handles various actions based on an action ID. 
// This is the main event handler for the player state machine, dispatching to sub-handlers 
// for state transitions, effects, movement, combat, etc.

char __thiscall PlayerStateMachine::handleAction(
    int *this, undefined4 arg2, undefined4 arg3, undefined4 arg4, 
    int *actionID, undefined4 arg6
) {
    // Local helpers / managers obtained from singletons
    int *pManager;        // from FUN_0073b460
    int *pOwnerObject;    // this[0x17] (likely m_pOwner)
    int *pTimer;          // this[0x23] (m_pTimer or m_pathData)
    uint flags;           // this[0x1d] (m_flags)
    char retVal = 1;      // default success return

    switch ((int)actionID - 0x23) {
        case 0: // actionID == 0x23 - e.g., start movement
            pManager = getSingletonManager(); // FUN_0073b460
            if (pManager != NULL) {
                this[0x20] = (int)((float)this[0x20] + someGlobalFloat); // apply speed delta
                playAnimation(this[0x17], &this[0x20], this[0x21]); // FUN_00939760
                return 1;
            }
            break;
        case 1: // actionID == 0x24 - clear state flags
            this[0xe] &= 0xffffbfdf;
            return 1;
        case 2: // actionID == 0x25 - release/reset something
            if (this[0x2b] != 0) {
                releaseEffect((int *)(this + 0x2b)); // FUN_004daf90
                this[0x2b] = 0;
                return 1;
            }
            break;
        case 3: // actionID == 0x26 - spawn VFX
            pOwnerObject = (int *)*this; // this->vtable
            retVal = 0x3f; // special return for VFX handling
            int *vfx = createVFX(1, 0, 0, 1.0f, 1.0f); // FUN_007347e0
            (*(code **)(*vfx + 0x2c))(vfx); // call vfx->play()
            return retVal;
        case 4: // actionID == 0x27 - more VFX with owner
            pManager = getSingletonManager();
            if ((pManager != NULL) && (*(int *)(pManager + 0x14) != 0)) {
                retVal = 0x3f;
                int *vfxHandle = *(int **)(pManager + 0x14);
                (*(code **)(*this + 0x2c))(vfxHandle, 1, 1, 1, 1.0f, 1.0f); // play on owner
                resetAnimation(this[0x17]); // FUN_009396c0
                return retVal;
            }
            break;
        case 5: // actionID == 0x28 - clear something
            clearSomeEffect(); // FUN_0073b480
            return 1;
        case 6: // actionID == 0x29 - play sound/effect on object
            pManager = getSingletonManager();
            if ((pManager != NULL) && (*(int *)(pManager + 0x2c) != 0)) {
                (*(code **)(*this + 0x2c))(*(int *)(pManager + 0x2c), 1, 1, 1, 1.0f, 1.0f);
            }
            if (getComponentFromOwner(this[0x17]) != NULL) { // FUN_006bc8b0
                *(uint *)(this[0x17] + 0x48) |= 2; // set a flag on component
                return 1;
            }
            break;
        case 7: // actionID == 0x2a - VFX on specific offset
            pManager = getSingletonManager();
            if ((pManager != NULL) && (*(int *)(pManager + 0x30) != 0)) {
                retVal = 0x3f;
                (*(code **)(*this + 0x2c))(*(int *)(pManager + 0x30), 1, 1, 1, 1.0f, 1.0f);
                return retVal;
            }
            break;
        case 8: // actionID == 0x2b - check animation completion
            if (((uint)this[0x17][0x238] >> 10 & 1) != 0) {
                (**(code **)(*(int *)this[0x17] + 0x260))(); // call owner's animation done callback
                return 1;
            }
            break;
        case 9: // actionID == 0x2c - default handler
        default:
            retVal = defaultEventHandler(arg2, arg3, arg4, actionID, arg6); // FUN_0073e610
            break;
        case 10: // actionID == 0x2d - handle state (go to label below)
            pManager = getSingletonManager();
            if (pManager == NULL) {
                return 1;
            }
            flags = this[0x1d];
            goto commonStateHandler;
            break;
        case 0xb: // actionID == 0x2e - start combat
            pManager = getSingletonManager();
            if ((pManager != NULL) && ((this[0x1d] & 0x80000U) == 0)) {
                this[0x1d] |= 0x280000;
                lockTarget(this[0x17]); // FUN_00789860
                return 1;
            }
            break;
        case 0xc: // actionID == 0x2f - conditional combat start
            pManager = getSingletonManager();
            if ((pManager != NULL) && ((flags = this[0x1d], (flags & 0x4000) != 0)) && 
                ((flags & 0x80000U) == 0)) {
                this[0x1d] = flags | 0x280000;
                lockTarget(this[0x17]); // FUN_00789860
                return 1;
            }
            break;
        case 0xd: // actionID == 0x30 - start timer
            startTimer((int *)(this + 0x23)); // FUN_0073b210
            return 1;
        case 0xe: // actionID == 0x31 - stop timer
            stopTimer((int *)(this + 0x23)); // FUN_0073b2e0
            return 1;
        case 0xf: // actionID == 0x32 - activate ragdoll
            if (getComponentFromOwner(this[0x17]) != NULL) { // FUN_006bc8b0
                activateRagdoll(); // FUN_009b1410
            }
            *(uint *)(this[0x17] + 0x1f58) |= 0x10000000; // set flag on owner
            return 1;
        case 0x10: // actionID == 0x33 - play health sound
            if ((this[0x1d] & 0x10000U) == 0) {
                playSound(99); // FUN_007f63e0
                this[0x1d] |= 0x10000;
                return 1;
            }
            break;
        case 0x11: // actionID == 0x34 - send message from offset 0x40
            pManager = getSingletonManager();
            if ((pManager != NULL) && (*(int *)(pManager + 0x40) != 0)) {
                int msg = beginMessage(0, 0); // FUN_006fbc40
                sendMessage(*(int *)(pManager + 0x40), 0x75, msg, 0); // FUN_007f96a0
                endMessage(); // FUN_006fbc70
                return 1;
            }
            break;
        case 0x12: // actionID == 0x35 - same from offset 0x44
            pManager = getSingletonManager();
            if ((pManager != NULL) && (*(int *)(pManager + 0x44) != 0)) {
                int msg = beginMessage(0, 0);
                sendMessage(*(int *)(pManager + 0x44), 0x75, msg, 0);
                endMessage();
                return 1;
            }
            break;
        case 0x13: // actionID == 0x36 - from offset 0x48 plus extra call
            pManager = getSingletonManager();
            if ((pManager != NULL) && (*(int *)(pManager + 0x48) != 0)) {
                int msg = beginMessage(0, 0);
                sendMessage(*(int *)(pManager + 0x48), 0x75, msg, 0);
                endMessage();
            }
            int *pExtraHandler = getExtraHandler(); // FUN_0073b120
            if (pExtraHandler != NULL) {
                int component = getComponentFromOwner(this[0x17]); // FUN_006bc8b0
                (**(code **)(*pExtraHandler + 0x28))(0x6685eec4, 0, -1, component);
                return (char)((uint)someGlobal >> 0x18); // weird return
            }
            break;
        case 0x14: // actionID == 0x37 - set animation with param
            pManager = getSingletonManager();
            if (pManager != NULL) {
                setAnimationParam(this[0x17], *(undefined4 *)(pManager + 0x10)); // FUN_00939620
                return 1;
            }
            break;
        case 0x15: // actionID == 0x38 - set flag
            this[0x1d] |= 0x40;
            return 1;
        case 0x16: // actionID == 0x39 - (not present in decomp)
            break;
        case 0x17: // actionID == 0x3a - proximity check
            {
                int owner = this[0x17];
                this[0x1d] &= 0xfffffbff;
                int obj1 = getSomeObject(); // FUN_00471610
                int obj2 = getSomeObject(); // FUN_00471610
                double dist = getDistanceBetween(obj1 + 0x30, obj2 + 0x30); // FUN_0045c470
                if (((dist >= someThreshold) || // _DAT_00d93628
                     (FUN_006c0050(obj1 + 0x30, 1, 0) != 0)) && 
                    (FUN_007a8c50(1, owner) != 0)) {
                    this[0x1d] |= 0x400; // set proximity flag
                    return 1;
                }
            }
            break;
        case 0x18: // actionID == 0x3b - check if in vehicle
            if (FUN_006bea40(this[0x17]) != 0) {
                performVehicleAction(1); // FUN_009ae900
                this[0x1d] |= 0x1000;
                return 1;
            }
            break;
        case 0x19: // actionID == 0x3c - exit vehicle
            pManager = getSingletonManager();
            if (pManager != NULL) {
                exitVehicle(); // FUN_007898c0
                return 1;
            }
            break;
        case 0x1a: // actionID == 0x3d - set flag 0x2000
            this[0x1d] |= 0x2000;
            return 1;
        case 0x1b: // actionID == 0x3e - interact with object
            pManager = getSingletonManager();
            if (pManager != NULL) {
                interactWithObject(this[0x17]); // FUN_007897e0
                return 1;
            }
            break;
        case 0x1c: // actionID == 0x3f - attack start/stop
            {
                int *owner = (int *)this[0x17];
                pManager = getSingletonManager();
                if ((pManager != NULL) && ((*(byte *)(pManager + 0x34) & 0x20) != 0)) {
                    (**(code **)(*owner + 0x164))(); // start attack
                    return 1;
                }
                (**(code **)(*owner + 0x168))(); // stop attack
                return 1;
            }
        case 0x1d: // actionID == 0x40 - something with owner
            if (this[0x29] == 0) {
                FUN_007a8c50(1, this[0x17]);
            }
            // Note: original has two calls, but second is unconditional.
            // Possibly a bug: should be else? We'll keep as decompiled.
            FUN_007a8c50(1, this[0x17]);
            return 1;
        case 0x1e: // actionID == 0x41 - path follow/move
            {
                int *owner = (int *)this[0x17];
                pTimer = (int *)(this + 0x23);
                // local_14 = &actionID  (reused as param)
                // local_8, local_4, local_10, local_c are set up for pathfinding
                int local_14 = (int)&actionID;
                int local_8 = 0;
                int local_4 = -1;
                int local_10 = 1;
                int local_c = someGlobal; // DAT_00d5d7b8
                int *pathParams[6] = { (int *)owner, pTimer, pTimer, 0, (int *)&local_14, (int *)this[0x24] };
                // Actually the call is FUN_005f6e80(pTimer, pTimer, 0, &local_14, this[0x24]) 
                // with first param as param_1 = pTimer? Let's match original.
                if (FUN_005f6e80(pTimer, pTimer, 0, &local_14, this[0x24]) == 0) {
                    pathSucceeded(); // FUN_009b1250
                    (**(code **)(*owner + 0x1c))(pTimer); // call owner's movement callback
                    this[0x1d] |= 0x400; // proximity flag
                }
                this[0x1d] |= 0x800000; // path active flag
                return 1;
            }
        case 0x1f: // actionID == 0x42 - increment counter
            if (((this[0x1d] & 0x10000U) == 0) && (1 < (uint)this[0x2d])) {
                playSound(99); // FUN_007f63e0
                this[0x1d] |= 0x10000;
            }
            this[0x2d] = this[0x2d] + 1;
            return 1;
        case 0x20: // actionID == 0x43 - show prompt (shared logic with case 10)
            pManager = getSingletonManager();
            if (pManager == NULL) {
                return 1;
            }
            flags = this[0x1d];
            if ((flags & 0x4000) == 0) {
                return 1;
            }
commonStateHandler:
            if ((flags & 0x100000) == 0) {
                this[0x1d] = flags | 0x300000;
                showPrompt(); // FUN_00789e60
                return 1;
            }
            break;
        case 0x21: // actionID == 0x44 - send message if not already set
            if ((this[0x1d] & 0x400U) == 0) {
                int msg = beginMessage(0, 0); // FUN_006fbc40
                sendMessage(0x8cfe0a2a, 0xb0, msg, 0); // FUN_007f96a0
                endMessage(); // FUN_006fbc70
                return 1;
            }
            break;
        case 0x22: // actionID == 0x45 - set flag 0x200000 if 0x400000 set
            flags = this[0x1d];
            if (((flags & 0x200000) == 0) && ((flags & 0x400000) != 0)) {
                this[0x1d] = flags | 0x200000;
                return 1;
            }
            break;
        case 0x23: // actionID == 0x46 - reset something
            if (getComponentFromOwner(this[0x17]) != NULL) { // FUN_006bc8b0
                resetComponent(0); // FUN_009b1440
                return 1;
            }
            break;
    }
    return retVal;
}