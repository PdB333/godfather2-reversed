// FUNC_NAME: PlayerSM::updateActions
// Function at 0x005e86e0: Updates player action states (e.g., entering/exiting cover, vehicle, etc.)
// Uses implicit this pointer (in_EAX) for a large PlayerSM object.
// Offsets: +0x484 (isInVehicle?), +0x1fc (isInCover?), +0x210 (action callback), +0x1c8 (action param1), +0x1cc (action param2), +0x27c (entityId), +0x278 (context), +0x284 (flagAction1), +0x283 (flagAction2), +0x20c (threshold), +0x208 (timer), +0x1F4 (some value)

void PlayerSM::updateActions() {
    // Enter/exit hooks (likely for profiling or state stack)
    FUN_005e89e0(); // enter
    FUN_005e8900(); // pre-update

    // Check if player is in a state that allows actions (e.g., in vehicle or cover)
    if (*(int*)(this + 0x484) != 0 || *(int*)(this + 0x1fc) != 0) {
        // If action callback is set
        if (*(int*)(this + 0x210) != 0) {
            // Virtual check: can perform action type 1?
            // DAT_01223510 points to a vtable (likely a manager singleton)
            char canDoAction1 = (**(code**)(*DAT_01223510 + 0x94))(*(undefined4*)(this + 0x1c8), (int*)(this + 0x1F4));
            if (canDoAction1 != 0) {
                // If action1 not already done
                if (*(char*)(this + 0x284) == 0) {
                    int value = *(int*)(this + 0x1F4);
                    // Condition: value <= threshold (0x20c) and value > 0, OR value > 99 and (global timer - this->timer) > 499
                    if ((*(int*)(this + 0x20c) <= value && 0 < value) ||
                        (99 < value && (499 < *(int*)(DAT_01223518 + 8) - *(int*)(this + 0x208)))) {
                        // Execute action1 callback
                        (**(code**)(this + 0x210))(*(undefined4*)(this + 0x27c), 1, *(undefined4*)(this + 0x278));
                        // Set flag and notify system
                        *(char*)(this + 0x284) = 1;
                        FUN_005e25a0(DAT_0122350c, *(undefined4*)(this + 0x27c), 1);
                    }
                }
                // Check action2
                if (*(char*)(this + 0x283) == 0) {
                    // Virtual check: can perform action type 2?
                    char canDoAction2 = (**(code**)(*DAT_01223510 + 0x90))(*(undefined4*)(this + 0x1cc));
                    if (canDoAction2 != 0) {
                        // If action1 not done yet, do it now (same as above)
                        if (*(char*)(this + 0x284) == 0) {
                            (**(code**)(this + 0x210))(*(undefined4*)(this + 0x27c), 1, *(undefined4*)(this + 0x278));
                            *(char*)(this + 0x284) = 1;
                            FUN_005e25a0(DAT_0122350c, *(undefined4*)(this + 0x27c), 1);
                        }
                        // Execute action2 callback
                        (**(code**)(this + 0x210))(*(undefined4*)(this + 0x27c), 2, *(undefined4*)(this + 0x278));
                        *(char*)(this + 0x283) = 1;
                        FUN_005e25a0(DAT_0122350c, *(undefined4*)(this + 0x27c), 2);
                    }
                }
            }
        }
        // Post-action updates
        FUN_005e8e30(); // e.g., update timers
        FUN_005e8860(); // e.g., update physics
    }

    // Exit hook
    FUN_005e89e0();
    return;
}