// FUNC_NAME: PlayerSM::handleAction
// Function address: 0x007c34a0
// Role: Handles player state machine actions based on action ID (param_5).
// Switch cases correspond to action IDs 0x31-0x36 (49-54).
// Uses member offsets: +0x58 (pointer to another object, likely player data),
// +0x78 (current state/cover mode), +0x7c (some state or animation index),
// +0x84 (flags).

bool __thiscall PlayerSM::handleAction(int thisPtr, int param_2, int param_3, int param_4, int actionId, int param_6)
{
    bool result = true;
    // local_c and local_4 are uninitialized and passed to playSoundEvent - likely a struct or leftover from optimization
    int uninitLocal1;
    int uninitLocal2;

    switch (actionId - 0x31) {
    case 0: // actionId == 0x31
        // Play sound event (0x12 = 18, arg2=1, arg3=0, plus uninitialized struct)
        playSoundEvent(0x12, 1, 0, uninitLocal1, uninitLocal2);
        // Then call a state transition function (likely enters a specific state)
        PlayerSM::handleAction49();
        return true;

    case 1: // actionId == 0x32
        // Another state transition
        PlayerSM::handleAction50();
        return true;

    case 2: // actionId == 0x33
    {
        // Read player data at +0x58 then +0x74c for some animation/state info
        int playerData = *(int *)(thisPtr + 0x58); // pointer to player data
        int animState = *(int *)(playerData + 0x74c); // +0x74c: current animation state
        if (animState != 0 && animState != 0x48) { // 0x48 likely invalid index
            char animId = *(char *)(animState + 0x165); // +0x165: animation ID offset
            // If in cover state (thisPtr+0x78 == 3) and not animation 0x1a, or
            // in ground state (state==2) and not animation 0x1b, then activate
            int coverMode = *(int *)(thisPtr + 0x78); // +0x78: 2=ground, 3=cover?
            if (((animId != 0x1a) && (coverMode == 3)) ||
                ((animId != 0x1b) && (coverMode == 2))) {
                // Activate animation at index (animState - 0x48)
                setAnimationActive(animState - 0x48); // likely a bone/pose index
                // Set flag bit 1 (+0x84)
                *(unsigned int *)(thisPtr + 0x84) |= 2;
            }
            // Check another flag at +0x8e0 bit 10
            if ((*(unsigned int *)(playerData + 0x8e0) >> 10 & 1) != 0) {
                *(unsigned int *)(thisPtr + 0x84) |= 1; // set flag bit 0
                return true;
            }
        }
        break;
    }

    case 3: // actionId == 0x34
    {
        int animIndex = *(int *)(thisPtr + 0x7c); // +0x7c: animation index or state
        if (animIndex != 0 && animIndex != 0x48) {
            if (animIndex == 0) {
                setAnimationActive(0); // deactivate?
            } else {
                setAnimationActive(animIndex - 0x48);
            }
            return true;
        }
        break;
    }

    case 4: // actionId == 0x35
    {
        int playerData = *(int *)(thisPtr + 0x58);
        int animState = *(int *)(playerData + 0x74c);
        if (animState == 0 || animState == 0x48) { // no active animation
            int coverMode = *(int *)(thisPtr + 0x78);
            int type;
            if (coverMode == 3) {
                type = 8; // cover? spawn type
            } else {
                type = 7; // ground? spawn type
            }
            int obj = createObject(type); // object type 7 or 8
            if (obj != 0) {
                // Call virtual method at offset 600 (0x258) in vtable of playerData object
                (*(void (__thiscall **)(int))(**(int **)(thisPtr + 0x58) + 600))(obj);
                return true;
            }
        }
        break;
    }

    case 5: // actionId == 0x36
        // Do nothing, fall through to return
        break;

    default:
        // Delegate to base class handler
        result = baseClassHandleAction(param_2, param_3, param_4, actionId, param_6);
    }
    return result;
}

// Helper function declarations for callees (names assumed based on context)
void __thiscall playSoundEvent(int eventId, int arg2, int arg3, int outStruct1, int outStruct2);
void __thiscall PlayerSM::handleAction49();
void __thiscall PlayerSM::handleAction50();
void __thiscall setAnimationActive(int index); // assumes animation system
int  __thiscall createObject(int type); // returns pointer to new object
bool __thiscall baseClassHandleAction(int, int, int, int, int); // base class default handler

// Note: The actual callee addresses are:
// 0x0079fb90 - playSoundEvent (assumed)
// 0x007c2f50 - handleAction49 (first case)
// 0x007c3050 - handleAction50 (second case)
// 0x006906e0 - setAnimationActive (with offset -0x48)
// 0x00690820 - setAnimationActive (with offset +0x48) - seems to be the same function
// 0x00705ab0 - createObject (returns pointer, then vtable call)
// 0x007abec0 - baseClassHandleAction (default)