// FUNC_NAME: PlayerWallCoverSM::transitionToState
int __thiscall PlayerWallCoverSM::transitionToState(int param_2)
{
    // +0x118: flags bitfield. Bits: 0-3 (state via >>7&0xf), 0x8000 (isTransitioning?), 0x60 (anim flags), 0x10 (some flag), 0x1 (bit0), 0x4 (bit2), etc.
    // +0x11c: pointer to animation data or state data
    // +0x150: additional flags
    // +0x130: cached hash
    // +0x144: some property from source
    // +0x148: source state index?
    // +0x84: parameter / timer
    // +0xb0: name/string buffer (32 chars?)
    // +0x12c: timer (300 decimal)
    // +0x64: offset 100 decimal (some resource)
    // DAT_01129948 = g_GameManager, +0x61 = isPlayingMinigame, +0x38 = currentPlayerStateMachine

    FUN_00843030(); // probably some pre-check

    if (*(char *)(DAT_01129948 + 0x61) == '\0') { // minigame not active
        char canTransition = FUN_00847100(); // query if we can change state

        if ((canTransition == '\0') || 
            ((param_2 == 0) && 
             ((uint state = (*(uint *)(this + 0x118) >> 7) & 0xf, state == 1 || state == 2))))
        {
            if (param_2 == 0) {
                // No target state: tick current state
                switch ((*(uint *)(this + 0x118) >> 7) & 0xf) {
                case 1: // entering cover
                    FUN_00847a50();
                case 2: // in cover
                    uint flags = *(uint *)(this + 0x118);
                    if ((flags & 0x8000) == 0 && (flags & 0x60) != 0) {
                        // set transitioning flag and clear anim flag 0x20
                        *(uint *)(this + 0x118) = (flags & 0xffffffdf) | 0x8040;
                    }
                    *(uint *)(this + 0x150) &= 0xfffffffe; // clear bit0
                    return 0;
                case 3: // exiting cover
                    FUN_00846220();
                    *(uint *)(this + 0x118) = (*(uint *)(this + 0x118) & 0xfffffa7f) | 0x200;
                case 0: // idle / no cover
                    *(int *)(DAT_01129948 + 0x38) = this; // set as active player state machine
                    if (((*(int *)(this + 0x11c) != 0) && (char ret = FUN_00599180(), ret != '\0')) ||
                        ((*(uint *)(this + 0x118) >> 1 & 1) == 0)) {
                        FUN_00843d00(); // maybe play sound or effect
                    }
                    FUN_00402050(this + 0x84, 0); // clear timer/counter
                default:
                    *(int *)(this + 0x148) = 0; // reset source state
                }
            } else {
                // Target state provided: copy from param_2 (another state machine?)
                if (param_2 != this) {
                    FUN_008464a0(param_2); // copy some data
                    *(int *)(this + 0x144) = *(int *)(param_2 + 0x144);
                    // Copy bit8 from param_2 into this
                    *(uint *)(this + 0x118) ^= ((*(uint *)(param_2 + 0x118) >> 3 & 0xff) * 8 ^ *(uint *)(this + 0x118)) & 8;
                }
                *(int *)(this + 0x148) = *(int *)(param_2 + 0x148);
            }

            // Update hash from animation name at this+0xb0
            int animData = *(int *)(this + 0x11c);
            if (animData != 0) {
                char local_60[64]; // likely for string copy
                FUN_0044b4e0(local_60, this + 0xb0); // copy name string
                int hash = FUN_00597370(local_60); // compute hash
                *(int *)(this + 0x130) = hash;
                FUN_004086d0(this + 100); // offset 0x64, play animation
            }

            // Timer check at +0x12c (300 decimal)
            if (*(int *)(this + 0x12c) == 0) {
                FUN_00847300(1, 0); // maybe start a transition timer
            }

            if ((*(char *)(this + 0x118) & 0x10) != 0) {
                FUN_00402050(&DAT_0112dcec, 0); // clear global flag
            }
            *(uint *)(this + 0x150) &= 0xfffffffe;
            return 1; // success
        }
        else {
            // Transition not allowed: set isTransitioning flag
            if ((*(uint *)(this + 0x118) & 0x8000) == 0) {
                FUN_00846790(1, 0);
                *(uint *)(this + 0x118) |= 0x8000;
                if (param_2 != 0) {
                    FUN_008464a0(param_2); // copy anyway
                }
            }
        }
    }
    return 0; // failure or minigame active
}