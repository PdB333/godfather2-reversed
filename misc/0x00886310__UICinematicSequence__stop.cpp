// FUNC_NAME: UICinematicSequence::stop

void __fastcall UICinematicSequence::stop(int thisPtr)
{
    int* piVar1;
    uint* puVar2;
    float fVar3;
    int iVar4;
    int iVar5;
    int* piVar6;
    float10 fVar7;
    float10 fVar8;
    undefined4 local_2c0;
    float local_2bc;
    undefined4 local_2b8;
    undefined4 local_2b4;
    undefined4 local_2b0;
    float local_2ac;
    undefined4 local_2a8;
    undefined4 local_2a4;
    undefined1 local_29c[20];
    undefined** local_288;
    undefined1 local_284;
    undefined1* local_280;
    int local_27c;
    undefined4 local_278;
    undefined1 local_274[260];
    undefined1 local_170[284];
    undefined4 local_54;

    // Check if the sequence is already stopped (bit 4 of flags at +0x70)
    if ((*(uint*)(thisPtr + 0x70) >> 4 & 1) == 0) {
        // Check if sequence is active (bit 0) and has a valid UI element at +0x50 not equal to 0x48
        if ((((*(byte*)(thisPtr + 0x70) & 1) != 0) &&
             (*(int*)(thisPtr + 0x50) != 0)) &&
            (*(int*)(thisPtr + 0x50) != 0x48)) {
            iVar5 = *(int*)(thisPtr + 0x58);  // Pointer to sequence data at +0x58

            // Get two random values for interpolation
            fVar7 = (float10)FUN_007f7d50(0, 0);
            fVar8 = (float10)FUN_007f7d50(0, 1);
            fVar3 = (float)fVar8;
            local_2bc = (float)fVar7 - fVar3;  // Start offset
            local_2ac = DAT_00d5fae0 + fVar3;  // End offset

            // Setup a quaternion or vector for camera shake/transition
            local_2c0 = 0;
            local_2b8 = 0;
            local_2b4 = _DAT_00d5780c;  // Some constant
            local_2b0 = 0;
            local_2a8 = 0;
            local_2a4 = _DAT_00d5780c;

            // Allocate temporary buffers (likely for debug text)
            FUN_00471610();
            FUN_00471610();

            // Compute interpolation factor
            FUN_00a65bb0(&local_2c0, &local_2b0, fVar3);

            // Push/pop UI constraints and begin drawing
            FUN_00549bf0();
            FUN_00549cf0(local_170);

            // Play a sound effect (event ID 0x40922)
            FUN_00540bc0(0x40922, *(undefined4*)(iVar5 + 0x830), 0, 0);

            // Get a handle for a UI component
            local_54 = FUN_00540cc0(local_29c);

            // Setup a debug output structure
            local_280 = local_274;
            local_288 = &PTR_LAB_00e3572c;  // Format string pointer
            local_278 = 0x80000010;          // Flags
            local_27c = 0;
            local_284 = 0;

            // Allocate memory for a message buffer
            iVar4 = FUN_00471610();
            FUN_00549d40(iVar4 + 0x30);   // Initialize buffer with format

            // Output debug message
            FUN_00549ea0(&local_288, 0);

            // If message was constructed, display it
            if (local_27c != 0) {
                if (*(int*)(thisPtr + 0x50) == 0) {
                    iVar4 = 0;
                } else {
                    iVar4 = *(int*)(thisPtr + 0x50) - 0x48;  // Offset for text display
                }
                FUN_007d4820(iVar5, iVar4);   // Set text on UI element
            }

            // Finish UI drawing
            FUN_004afb20();
            FUN_00549cb0();
        }

        // Clear the "stopping" flag (bit 27 of flags at +0x1b94 in sequence data)
        puVar2 = (uint*)(*(int*)(thisPtr + 0x58) + 0x1b94);
        *puVar2 = *puVar2 & 0xf7ffffff;

        // Release a global lock or mutex
        FUN_007f89d0(&DAT_00d77000);
        FUN_005512c0(0);  // Stop a timer or process

        piVar1 = (int*)(thisPtr + 0x50);  // Pointer to UI element handle (+0x50)
        // If the UI element exists and is not a null handle (0x48), call its cleanup virtual method
        if ((*(int*)(thisPtr + 0x50) != 0) && (*(int*)(thisPtr + 0x50) != 0x48)) {
            if (*piVar1 == 0) {
                piVar6 = (int*)0x0;
            } else {
                piVar6 = (int*)(*piVar1 - 0x48);
            }
            // Call virtual function at vtable+0x268 (likely a destructor or release)
            (**(code**)(*piVar6 + 0x268))(*(undefined4*)(thisPtr + 0x58));
        }

        // If bit 1 is set, disable fading (set volume/time scale to 1.0)
        if ((*(uint*)(thisPtr + 0x70) >> 1 & 1) != 0) {
            if (*(int*)(thisPtr + 0x58) != 0) {
                FUN_00460300(0x3f800000);  // Set alpha/volume to 1.0
            }
            if ((*piVar1 != 0) && (*piVar1 != 0x48)) {
                FUN_00460300(0x3f800000);
            }
        }

        // If the sequence is not active (bit 0 clear) but UI element exists, handle dialog skipping
        if ((((*(byte*)(thisPtr + 0x70) & 1) == 0) &&
             (*piVar1 != 0)) &&
            (*piVar1 != 0x48)) {
            if (*piVar1 == 0) {
                iVar5 = 0;
            } else {
                iVar5 = *piVar1 - 0x48;
            }
            // Check if skip flag (bit 0 of byte at +0xc8a) is set
            if ((*(byte*)(iVar5 + 0xc8a) & 1) != 0) {
                // Disable skip button and clear held skip state
                FUN_00766470(0x8000);
                if (*piVar1 == 0) {
                    iVar5 = 0;
                } else {
                    iVar5 = *piVar1 - 0x48;
                }
                if (*(int*)(iVar5 + 0xe54) != 0) {
                    FUN_004daf90((undefined4*)(iVar5 + 0xe54));  // Free held skip data
                    *(undefined4*)(iVar5 + 0xe54) = 0;
                }
                FUN_00766440(0x10000);  // Enable skip button again?
            }
        }

        // Mark the sequence as stopped (set bit 5)
        *(uint*)(thisPtr + 0x70) = *(uint*)(thisPtr + 0x70) | 0x20;

        // If sequence is not active, clean up additional flags
        if ((*(byte*)(thisPtr + 0x70) & 1) == 0) {
            // Clear bit 13 of a flag at +0x1f58 in sequence data
            puVar2 = (uint*)(*(int*)(thisPtr + 0x58) + 0x1f58);
            *puVar2 = *puVar2 & 0xffffdfff;

            // Get a global manager and set a flag to indicate sequence is done
            iVar5 = FUN_007351c0();
            if (iVar5 != 0) {
                *(uint*)(iVar5 + 0x5c) = *(uint*)(iVar5 + 0x5c) | 0x800000;
            }
        }

        // Free the UI element handle if it exists
        if (*piVar1 != 0) {
            FUN_004daf90(piVar1);
            *piVar1 = 0;
        }
    }
    return;
}