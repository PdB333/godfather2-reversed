// FUNC_NAME: ResolutionManager::updateResolutionState

void __thiscall ResolutionManager::updateResolutionState(int *this) {
    // +0x14: flag indicating resolution list needs clearing (stored as int, used as bool)
    if ((char)this[0x14] != 0) {
        // +0x58: resolution mode (2nd flag) = 1  ;  +0x54: additional condition flag = 0
        if ((this[0x16] == 1) && (this[0x15] == 0)) {
            // Clear resolution list and reset internal data
            FUN_005a04a0("ClearResolutionList", 0, &DAT_00d90fa8, 0);

            int local_c = DAT_01130310;
            int local_8 = 0;
            char local_4 = 0;
            FUN_00408a00(&local_c, 0); // likely resets an array or state
        }
        // Clear the resolution-needed flag
        *(char *)(this + 0x14) = 0;
        return;
    }

    // +0x10d: another flag (usually controls update path)
    if (*(char *)((int)this + 0x10d) == 0) {
        // +0x43: yet another flag
        if (*(char *)((int)this + 0x43) == 0) {
            // Call virtual function from vtable (offset 0x2c)
            (*(void (__thiscall **)(int *))(*(int *)this + 0x2c))(this);
            return;
        }
    } else if (this[0x16] == 1) {
        FUN_00986d10(); // secondary update
    }

    FUN_00988680(); // final cleanup or state check
    return;
}