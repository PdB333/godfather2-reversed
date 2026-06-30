// FUNC_NAME: PlayerStateMachine::updateAction
void __thiscall PlayerStateMachine::updateAction(void)
{
    int counter;   // Variable for value at this+0x500
    undefined4 actionType; // Parameter for function calls
    char result;   // Result from virtual calls

    // Call helper functions (likely entering/exiting debug states or updating components)
    FUN_005e89e0(); // possibly updateDebug
    FUN_005e8900(); // possibly updateInput

    // Check if the state machine is active or has pending action
    if (*(int *)(this + 0x484) != 0 || *(int *)(this + 0x1fc) != 0)
    {
        // If we have a callback function pointer
        if (*(int *)(this + 0x210) != 0)
        {
            // Check global condition via a virtual function on some manager
            // GlobalManager at address DAT_01223510, vtable entry +0x94
            // Parameters: some pointer (this+0x1c8) and value at this+0x500
            result = (**(code (__thiscall **)(int, int *))(*(int *)DAT_01223510 + 0x94))
                     (*(int *)(this + 0x1c8), (int *)(this + 0x500));

            if (result != '\0')
            {
                // First action: if not yet performed
                if (*(char *)(this + 0x284) == '\0')
                {
                    counter = *(int *)(this + 0x500);
                    // Condition: either counter <= threshold and positive,
                    // or counter > 99 and time since start exceeds some limit
                    if (((*(int *)(this + 0x20c) <= counter) && (0 < counter)) ||
                        ((99 < counter && (499 < *(int *)(DAT_01223518 + 8) - *(int *)(this + 0x208)))))
                    {
                        // Trigger action type 1 via callback
                        (**(code (__thiscall **)(int, int, int))(this + 0x210))
                         (*(int *)(this + 0x27c), 1, *(int *)(this + 0x278));

                        // Set flag that first action was performed
                        *(char *)(this + 0x284) = 1;

                        // Notify global system about action type 1
                        FUN_005e25a0(DAT_0122350c, *(int *)(this + 0x27c), 1);
                    }
                }

                // Second action: if not yet performed
                if (*(char *)(this + 0x283) == '\0')
                {
                    // Check another global virtual condition, vtable entry +0x90
                    result = (**(code (__thiscall **)(int))(*(int *)DAT_01223510 + 0x90))
                             (*(int *)(this + 0x1cc));

                    if (result != '\0')
                    {
                        // First action might still be pending? Recheck and execute
                        if (*(char *)(this + 0x284) == '\0')
                        {
                            (**(code (__thiscall **)(int, int, int))(this + 0x210))
                             (*(int *)(this + 0x27c), 1, *(int *)(this + 0x278));

                            *(char *)(this + 0x284) = 1;
                            FUN_005e25a0(DAT_0122350c, *(int *)(this + 0x27c), 1);
                        }

                        // Trigger action type 2
                        (**(code (__thiscall **)(int, int, int))(this + 0x210))
                         (*(int *)(this + 0x27c), 2, *(int *)(this + 0x278));

                        // Set flag that second action was performed
                        *(char *)(this + 0x283) = 1;

                        // Notify global system about action type 2
                        FUN_005e25a0(DAT_0122350c, *(int *)(this + 0x27c), 2);
                    }
                }
            }
        }

        // Additional post-update calls
        FUN_005e8e30(); // possibly finalizeAction
        FUN_005e8860(); // possibly updateAnimations
    }

    // Final update call
    FUN_005e89e0(); // possibly updateDebug (again)
}