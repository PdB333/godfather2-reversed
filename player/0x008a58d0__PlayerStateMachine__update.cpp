// FUNC_NAME: PlayerStateMachine::update
void __thiscall PlayerStateMachine::update(int this, undefined4 deltaTime)
{
    uint stateFlags = *(uint *)(this + 0x37c); // +0x37c: state flags bitfield
    char isPaused = FUN_008a3b40();            // check if game is paused / state locked

    if ((stateFlags & 1) != 0) {
        if ((isPaused == 0) || (DAT_01129930 == 0)) {
            // not paused (or pause overridden)
            if ((stateFlags >> 8 & 1) == 0) {          // bit 8 clear?
                if ((stateFlags >> 4 & 1) == 0) {      // bit 4 clear?
                    // transition to mode 2 (idle / ground)
                    DAT_00e5672c = 0x1b;
                    *(uint *)(this + 0x37c) &= 0xfffffff7; // clear bit 3
                    FUN_008a4ae0(2);                       // enterState(2)
                    *(uint *)(this + 0x37c) &= 0xfffffffd; // clear bit 1
                }
                else {
                    // bit 4 set
                    if ((*(int *)(DAT_0112b9b4 + 0x40) == 0) && 
                        (*(int *)(DAT_012234b8 + 0xc) != 0)) {
                        // allow transition to state 3 if specific timer expired
                        if ((*(int *)(this + 0x3b4) == -1) &&          // +0x3b4: cooldown timer
                            ((stateFlags >> 0xd & 1) == 0)) {          // bit 13 clear
                            *(uint *)(this + 0x37c) &= 0xfffffff7;
                            FUN_008a4ae0(3);                           // enterState(3)
                            *(uint *)(this + 0x37c) &= 0xfffffffd;
                        }
                    }
                    else {
                        FUN_008a5440();                                // default handling (e.g. fallback)
                    }
                }
            }
        }
        else {
            FUN_00970560();                                            // handle paused state
        }
    }

    FUN_004bf3f0(deltaTime);                                          // update per-frame logic (time step)

    if (DAT_0112ebb0 != (undefined4 *)0x0) {
        if (*(int *)(this + 0x36c) != 0) {                            // +0x36c: some counter/flag
            FUN_00454310(0);                                           // reset related state
        }
        if (DAT_0112ebb0 != (undefined4 *)0x0) {
            // call virtual function on global management object (vtable at *DAT_0112ebb0)
            (**(code **)*DAT_0112ebb0)();
        }
    }
    return;
}