// FUNC_NAME: PlayerSM::switchState
// Address: 0x007f9030
// Handles state transitions for player state machine (states 0-4).
// States: 0=OnGround, 1=InAir, 2=Climbing, 3=Hanging, 4=Cover (approximate)
// param_3: if true, forces immediate transition (skips certain checks/enables)
void __thiscall PlayerSM::switchState(int* this, char newState, char forceImmediate)
{
    char oldState;

    oldState = *(char*)(this + 0x6e3); // +0x6e3 current state
    *(char*)(this + 0x6e3) = newState; // set new state

    // Check a flag at +0x8eb bit 0 (e.g., bLocked)
    if ((*(byte*)((int)this + 0x8eb) & 1) != 0) {
        // Call virtual function at vtable+0x28 (likely some cancel/exit function)
        (**(code**)(this[0x16] + 0x28))(0x20); // param 0x20 might be a reason
    }

    // Clear bit 24 at +0x23a (flag field)
    this[0x23a] = this[0x23a] & 0xfeffffff;

    if (oldState == newState) {
        return; // no transition
    }

    // Check forbidden transitions (2<->3) (climbing<->hanging)
    if (oldState == 0x03 && newState == 0x02) return;
    if (oldState == 0x02 && newState == 0x03) return;

    // Additional check: is something active? (e.g., a cutscene or script lock)
    char isActive = FUN_00481640(); // function at 0x481640
    if (isActive != 0 && (int*)this[0x17d] != 0) {
        isActive = (**(code**)(*(int*)this[0x17d] + 0x38))(); // +0x38 virtual on another object
        if (isActive != 0) return; // if still active, do nothing
    }

    // Transition from climbing/hanging (2/3) to ground/cover (0/4)
    if ((oldState == 0x03 || oldState == 0x02) && (newState == 0x00 || newState == 0x04)) {
        FUN_007f4690(); // exit climbing state
        if (newState == 0x00) {
            FUN_0054e390(0); // set ground mode
            if (forceImmediate != 0) {
                FUN_007f6420(1); // force immediate transition
                (**(code**)(*this + 0x2f4))(); // virtual: finalize transition
            }
            // else -> fall through to finalize
        } else {
            // newState == 0x04 (cover)
            FUN_0054e390(1); // set cover mode
            if (forceImmediate != 0) {
                FUN_007f63e0(1); // force immediate
            }
        }
        goto finalizeVirtual;
    }

    // Transition from ground/cover (0/4) to climbing/hanging (2/3)
    if ((oldState == 0x00 || oldState == 0x04) && (newState == 0x02 || newState == 0x03)) {
        if (forceImmediate != 0) {
            FUN_007f6420(1); // force immediate
        }
        FUN_007f4620(); // enter climbing state
        return; // done (no finalize virtual? but later may have)
    }

    // Transition from air (1) to any other state
    if (oldState == 0x01) {
        FUN_007f4740(); // exit air state
        if (newState == 0x00 || newState == 0x04) {
            // go to ground/cover
            if (newState == 0x00) {
                FUN_0054e390(0);
                if (forceImmediate != 0) {
                    FUN_007f6420(1);
                    (**(code**)(*this + 0x2f4))();
                }
                return;
            }
            // else newState == 4: fall through to finalize
            goto finalizeWithSet;
        }
        if (newState == 0x02 || newState == 0x03) {
            FUN_007f4620(); // enter climbing
            return;
        }
        // newState == 1 -> already returned earlier
        return;
    }

    // Transition from ground/cover (0/4) to air (1)
    if ((oldState == 0x00 || oldState == 0x04) && newState == 0x01) {
        if (forceImmediate != 0) {
            FUN_007f6420(1);
        }
        FUN_007f46d0(); // enter air state
        return;
    }

    // Transition from climbing/hanging (2/3) to air (1)
    if ((oldState == 0x03 || oldState == 0x02) && newState == 0x01) {
        FUN_007f4690(); // exit climbing
        FUN_007f46d0(); // enter air
        return;
    }

    // Handle transitions between ground (0) and cover (4) – symmetric
    if (oldState == 0x00) {
        if (newState == 0x04) {
            // ground -> cover
            FUN_0054e390(1);
            if (forceImmediate != 0) {
                FUN_007f63e0(1);
            }
            goto finalizeVirtual;
        }
        return; // only 0->4 allowed otherwise return
    }
    if (oldState == 0x04) {
        if (newState == 0x00) {
            // cover -> ground
            FUN_0054e390(0);
            if (forceImmediate != 0) {
                FUN_007f6420(1);
                (**(code**)(*this + 0x2f4))();
            }
            return;
        }
        return;
    }

    // Unhandled transitions: fall through to finalizeVirtual only if newState==4 and oldState==0? Already covered.
    return;

finalizeWithSet:
    // Called for 0->4 and 4->0 (cover/ground switch)
    FUN_0054e390(1); // mode 1 for cover
    if (forceImmediate != 0) {
        FUN_007f63e0(1);
    }
    goto finalizeVirtual;

finalizeVirtual:
    // Common finalize: call virtual at vtable+0x2f4
    (**(code**)(*this + 0x2f4))();
    return;
}