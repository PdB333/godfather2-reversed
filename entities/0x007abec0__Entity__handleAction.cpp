// FUNC_NAME: Entity::handleAction
// Function address: 0x007abec0
// Role: Dispatches action messages based on action ID (param_5 - 0x12)
// This is likely a member of a base Entity class that handles player/AI control actions.
// It accesses this+0x58 (m_pCharacter), this+0x5C (m_pInterface), this+0x60 (m_pOther),
// this+0x70 (m_bFlag), this+0x30 (m_fDistance) and several global constants.

enum ActionID : int {
    ACTION_UNKNOWN_0x12 = 0x12,
    ACTION_UNKNOWN_0x13,
    ACTION_UNKNOWN_0x14,
    // ... etc up to 0x2f
};

bool __thiscall Entity::handleAction(void* param_2, void* param_3, void* param_4, int actionId, void* param_6)
{
    switch(actionId - 0x12) {
    case 0: { // action 0x12
        bool bToggle = FUN_006252f0(); // likely getInputState or random
        FUN_0079e9c0(bToggle); // set some visible state (e.g., lockOn)
        return true;
    }
    case 1: { // action 0x13
        bool bToggle = FUN_006252f0();
        if (*(int*)(this + 0x58) != 0) { // m_pCharacter valid
            if (bToggle) {
                FUN_007f74e0(); // enable something (e.g., show weapon)
            } else {
                FUN_007f74f0(); // disable something
            }
            return true;
        }
        break;
    }
    case 2: { // action 0x14
        bool bToggle = FUN_006252f0();
        if (*(int*)(this + 0x58) != 0) {
            if (bToggle) {
                FUN_007f7500(); // alternate toggle on
            } else {
                FUN_007f7510(); // alternate toggle off
            }
            return true;
        }
        break;
    }
    case 3: { // action 0x15
        if (*(int*)(this + 0x58) != 0) {
            FUN_007fcd60(); // play sound or animation
            return true;
        }
        break;
    }
    case 4: { // action 0x16
        bool bParam = FUN_006252f0();
        if (*(int*)(this + 0x58) != 0) {
            FUN_008054f0(bParam, 1); // set something with integer param
            return true;
        }
        break;
    }
    case 5: { // action 0x17
        bool bParam = FUN_006252f0();
        if (*(int*)(this + 0x58) != 0) {
            FUN_008054f0(bParam, 0);
            return true;
        }
        break;
    }
    case 6: { // action 0x18
        FUN_007abe00(); // trigger action (e.g., start animation)
        return true;
    }
    case 7: { // action 0x19
        *(byte*)(this + 0x70) = 0; // clear flag
        return true;
    }
    case 8: { // action 0x1a
        // Check if global distance threshold is below m_fDistance and flag is clear
        if (*DAT_00d577a0 < *(float*)(this + 0x30) && *(byte*)(this + 0x70) == 0) {
            FUN_007abe00();
            *(byte*)(this + 0x70) = 1; // set flag
            return true;
        }
        break;
    }
    case 9: { // action 0x1b
        // Set a color value in the object at this+0x60
        *(int*)(*(int*)(this + 0x60) + 0xC) = DAT_01205224; // some constant (e.g., color)
        return true;
    }
    case 10: { // action 0x1c
        *(int*)(*(int*)(this + 0x60) + 0xC) = 0; // clear color
        return true;
    }
    case 11: { // action 0x1d
        bool bToggle = FUN_006252f0();
        if (*(int*)(this + 0x58) != 0) {
            if (bToggle) {
                FUN_005512c0(0); // set focus state 0
            } else {
                FUN_005512c0(1); // set focus state 1
            }
            return true;
        }
        break;
    }
    case 12: { // action 0x1e
        bool bToggle = FUN_006252f0();
        if (bToggle) {
            FUN_007ab470(2); // start something with param 2
        } else {
            FUN_007ab4d0(2); // stop something with param 2
        }
        return true;
    }
    case 13: { // action 0x1f
        int* vtable = **(int***)(this + 0x5C); // get vtable at this+0x5C
        bool bParam = FUN_006252f0();
        // call virtual function at offset 4
        ((void (__thiscall*)(void*, bool))*vtable + 1)(*(void*)(this + 0x5C), bParam);
        return true;
    }
    case 14: { // action 0x20
        int* obj = *(int**)(this + 0x5C); // get object pointer
        goto call_virtual_from_ptr;
    }
    case 15: { // action 0x21
        int* vtable = **(int***)(this + 0x60);
        bool bParam = FUN_006252f0();
        ((void (__thiscall*)(void*, bool))*vtable + 1)(*(void*)(this + 0x60), bParam);
        return true;
    }
    case 16: { // action 0x22
        int* obj = *(int**)(this + 0x60);
        goto call_virtual_from_ptr;
    }
    case 17: { // action 0x23
        if (*(int*)(this + 0x58) != 0) {
            int vtable2 = *(int*)(*(int*)(this + 0x58) + 0x26a0); // nested pointer
            bool bParam = FUN_006252f0();
            ((void (__thiscall*)(void*, bool))*vtable2 + 4)(*(void*)(this + 0x58) + 0x26a0, bParam);
            return true;
        }
        break;
    }
    case 18: { // action 0x24
        int* obj = (int*)(*(int*)(this + 0x58) + 0x26a0);
call_virtual_from_ptr:
        int* vtable = (int*)*obj;
        bool bParam = FUN_006252f0();
        // call first virtual function of the pointed object
        ((void (__thiscall*)(void*, bool))*vtable)(obj, bParam);
        return true;
    }
    default: {
        // Fallback to parent handler
        return FUN_004ac700(param_2, param_3, param_4, actionId, param_6);
    }
    case 0x14: { // action 0x26
        FUN_007f7e40(); // pause/resume something
        return true;
    }
    case 0x15: { // action 0x27
        FUN_007f6420(0x31); // set timer with id 49
        return true;
    }
    case 0x16: { // action 0x28
        FUN_007f63e0(0x31); // clear timer with id 49
        return true;
    }
    case 0x17: { // action 0x29
        // Find current "player" or entity via FUN_007ab710
        int* pTarget = FUN_007ab710();
        if (pTarget) {
            *(byte*)(pTarget + 0x1029) = 0; // clear flag on target
            *(byte*)(*(int*)(this + 0x58) + 0x1029) = 0; // clear flag on m_pCharacter
            FUN_007f9fa0(); // reset/sync something
            return true;
        }
        break;
    }
    case 0x18: { // action 0x2a
        int* pTarget = FUN_007ab710();
        if (pTarget) {
            *(byte*)(pTarget + 0x1029) = 1; // set flag on target
            return true;
        }
        break;
    }
    case 0x19: { // action 0x2b
        int* pTarget = FUN_007ab710();
        if (pTarget && DAT_00e44980 < *(float*)(this + 0x30)) {
            *(byte*)(pTarget + 0x1029) = 0;
            *(byte*)(*(int*)(this + 0x58) + 0x1029) = 0;
            return true;
        }
        break;
    }
    case 0x1a: { // action 0x2c
        bool bToggle = FUN_006252f0();
        if (bToggle) {
            FUN_007f4490(1, 1, DAT_00d5ef90); // enable with params
            return true;
        }
        // else fall through to set second param false
        FUN_007f4490(1, 0, DAT_00d5ef90);
        return true;
    }
    case 0x1b: { // action 0x2d
        bool bToggle = FUN_006252f0();
        if (bToggle) {
            FUN_007f4490(0, 1, DAT_00d5ef90);
            return true;
        }
        FUN_007f4490(0, 0, DAT_00d5ef90);
        return true;
    }
    case 0x1c: { // action 0x2e
        if (*(int*)(this + 0x58) != 0) {
            int iVar2 = *(int*)(*(int*)(this + 0x58) + 0xff0);
            if (iVar2 != 0 && iVar2 != 0x48) {
                float fVar = (float)FUN_006252e0(); // get random or time
                if (*(byte*)(*(int*)(this + 0x58) + 0x1029) != 0) {
                    FUN_007f4490(1, 0, fVar);
                    return true;
                } else {
                    FUN_007f4490(1, 0, fVar); // identical call? likely bug
                    return true;
                }
            }
        }
        break;
    }
    case 0x1d: { // action 0x2f
        if (*(int*)(this + 0x58) != 0) {
            int iVar2 = *(int*)(*(int*)(this + 0x58) + 0xff0);
            if (iVar2 != 0 && iVar2 != 0x48) {
                if (*(byte*)(*(int*)(this + 0x58) + 0x1029) == 0) {
                    FUN_007f4490(0, 0, DAT_00d5ef90);
                    return true;
                } else {
                    FUN_007f4490(0, 0, DAT_00d5ef90); // identical call? again
                    return true;
                }
            }
        }
    }
    } // end switch
    return true; // default return if no case matched
}