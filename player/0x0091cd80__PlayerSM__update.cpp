// FUNC_NAME: PlayerSM::update
void __thiscall PlayerSM::update(int *this, char isInitialCall, undefined4 param_3)
{
    int state;
    char flag;

    // Check if the game platform is PC (8 = PC, possibly from a global)
    if (*(int *)(DAT_012234b8 + 0x10) == 8) {
        // If this is an initial call (e.g., first frame), perform one-time setup
        if (isInitialCall != '\0') {
            // Call a function to handle initial state entry (e.g., play animation)
            FUN_0091ac00(param_3);
            // Call the virtual onEnterState() method (vtable at +0xC)
            (**(code **)(*this + 0xc))();
        }

        // Check if this state has already been initialized (byte at +0xBD)
        if (*(char *)((int)this + 0xbd) == '\0') {
            // Get the current state ID from offset 0x2e (0xB8)
            state = this[0x2e];

            // Handle specific state IDs (10, 11, 12 → probably ground, air, cover)
            if (((state == 10) || (state == 0xb)) || (state == 0xc)) {
                FUN_0091c860();               // State 10/11/12 update
                *(undefined1 *)((int)this + 0xbd) = 1; // Mark initialized
                return;
            }

            // State 0x19 (25) – possibly ragdoll or falling
            if (state == 0x19) {
                FUN_0091c8f0();               // State 0x19 update
                *(undefined1 *)((int)this + 0xbd) = 1;
                return;
            }

            // Check if a combat/detection state is active
            flag = FUN_00917030();
            if (flag != '\0') {
                FUN_0091c9a0();               // Combat state update
                *(undefined1 *)((int)this + 0xbd) = 1;
                return;
            }

            // Check for another condition (e.g., entering a vehicle)
            flag = FUN_00917060();
            if (flag != '\0') {
                FUN_0091cb40();               // Vehicle/interaction state update
            }

            // Mark this state as initialized
            *(undefined1 *)((int)this + 0xbd) = 1;
        }
    }
    return;
}