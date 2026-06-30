// FUNC_NAME: WeaponBase::updateState
// Address: 0x00511f00
// Role: Update state machine for weapon projectiles (state 4 = homing/tracking, state 6 = impact/explosion)

void __thiscall WeaponBase::updateState(int extraParam) {
    // +0x30: stateTimer (short) – countdown or active duration
    if (*(short *)((int)this + 0x30) != 0) {
        // +0x70: state (byte) – current state of projectile
        uint state = (uint)*(byte *)((int)this + 0x70);
        if (state == 4) {
            // +0x5c: targetPtr (int*) – target entity or null
            // +0x40: maxRange (float) – maximum effective range
            if (*(int *)((int)this + 0x5c) != 0 && g_gameTime < *(float *)((int)this + 0x40)) {
                // +0x32: weaponType (short) – weapon identifier
                FUN_00512870((int)this, extraParam, *(short *)((int)this + 0x32), *(short *)((int)this + 0x30));
            }
        }
        else if (state == 6) {
            // +0x50: somePtr (int*) – probably related to impact target or effect
            if (*(int *)((int)this + 0x50) != 0 && g_gameTime < *(float *)((int)this + 0x40)) {
                FUN_005118f0(*(short *)((int)this + 0x32));
                return; // early return after impact handling
            }
        }
    }
}