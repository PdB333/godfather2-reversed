// FUNC_NAME: SomeGameClass::handleStateChange

// Function at 0x006ae040 likely handles state transitions for a game object (e.g., UI, manager, or entity).
// param_2 appears to be an integer state code:
//   0 -> global init, 4 -> full setup (creates a temporary linked node and registers listeners),
//   3 -> set a flag (bit 2 at +0x2b4), 2 -> clear that flag and unregister a listener.
// After the switch, notifies a delegate at +0x130 if present.

void __thiscall SomeGameClass::handleStateChange(int param_2)
{
    int local_1c;
    undefined4 local_18, local_14, local_10, local_c;
    undefined1 local_8;
    undefined4 local_4;
    undefined4 *local_30;
    undefined ***local_2c;
    undefined1 local_28;
    undefined **local_24;
    undefined4 local_20;

    if (param_2 == 0) {
        // Global initialization
        someGlobalInit();
    }
    else {
        someGlobalSetup();
        if (param_2 == 4) {
            // Full initialization/startup

            // Setup a temporary node on stack (likely for a linked list registration)
            local_24 = (undefined **)&PTR_FUN_00d5dbbc; // some function pointer table? maybe vtable
            local_20 = 0x1970c04; // unknown constant
            if (this == 0) {
                local_1c = 0;
            }
            else {
                local_1c = (int)this + 0x48; // +0x48: pointer to a sub-object or node
            }

            local_18 = 0;
            if (local_1c != 0) {
                local_18 = *(undefined4 *)(local_1c + 4); // save next pointer
                *(int **)(local_1c + 4) = &local_1c;      // self-loop? sentinel for empty list?
            }

            // Initialize some variables
            local_c = 0;
            local_10 = 0;
            local_14 = 0;
            local_2c = &local_24;
            local_8 = 0;
            local_4 = DAT_01205228; // global data (e.g., a pointer)
            local_30 = &DAT_0112ad8c; // global data
            local_28 = 0;

            // Register first listener using local_30
            registerListener(&local_30, 0);

            // Fetch a pointer from this + 0x26c and use it as listener
            local_30 = *(undefined4 *)((int)this + 0x26c); // +0x26c: some member
            local_2c = 0;
            local_28 = 0;
            registerListener(&local_30, 0);

            // Set a value at this + 0x18c
            *(undefined4 *)((int)this + 0x18c) = DAT_00d5780c;

            // Set bit 2 at offset +0x2b4 (active flag)
            *(unsigned char *)((int)this + 0x2b4) |= 2;

            // Clean up the temporary node if it was set
            if (local_1c != 0) {
                unregisterListenerStruct((int *)&local_1c); // likely removes the node from list
            }
        }
        else if (param_2 == 3) {
            // Set active flag
            *(unsigned char *)((int)this + 0x2b4) |= 2;
        }
        else if (param_2 == 2) {
            // Clear active flag
            *(unsigned char *)((int)this + 0x2b4) &= 0xfd;

            // Unregister listener stored at +0x274
            local_30 = *(undefined4 *)((int)this + 0x274); // +0x274: another listener pointer
            local_2c = 0;
            local_28 = 0;
            registerListener(&local_30, 0); // TODO: might be unregisterListener?
        }
    }

    // Notify an external delegate if present (vtable call at +0x44)
    if (*(int **)((int)this + 0x130) != (int *)0) {
        (*(code **)(**(int **)((int)this + 0x130) + 0x44))(0xf86f4484, param_2);
    }
}