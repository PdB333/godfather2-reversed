// FUNC_NAME: InputManager::resolveBindingDisplay
void InputManager::resolveBindingDisplay(int contextIndex, int bindingIndex, int entryIndex)
{
    int iVar1; // Global data pointer
    char cVar2; // Button/device character
    undefined4 *puVar3; // Pointer to binding entry array
    undefined4 *puVar4; // Device mapping handle
    int iVar5; // Key code
    undefined4 uVar6; // Language ID
    char *local_30; // Localized string pointer
    undefined4 local_2c; // Unused (reserved)
    undefined4 local_28; // Unused (reserved)
    code *local_24; // Deallocator function pointer
    char displayBuffer[32]; // Output display string (32 bytes)

    // Get global data pointer
    iVar1 = DAT_012233b4;

    // Calculate pointer to the binding's display entry array.
    // The global table PTR_DAT_00e564f8 is indexed by contextIndex*2 (maybe high/low parts?).
    // Each binding is 100 bytes (bindingIndex * 100) into that struct.
    puVar3 = (undefined4 *)((&PTR_DAT_00e564f8)[contextIndex * 2] + bindingIndex * 100);

    // Clear the display buffer
    memset(displayBuffer, 0, 32);

    // Get the device mapping handle from the first field of the binding struct
    puVar4 = (undefined4 *)FUN_004c3b10(*puVar3);
    if (puVar4 != (undefined4 *)0x0) {
        // Get device button character (gamepad) or device type
        cVar2 = FUN_0049a870(*puVar4, puVar4[1], entryIndex);

        // Get key code for keyboard/mouse
        iVar5 = FUN_00496610(puVar4[2], puVar4[3], entryIndex);

        if ((cVar2 == '\0') || (cVar2 == -1)) {
            // No gamepad button assigned or unknown device -> use keyboard/mouse path
            if ((iVar5 == 0xff) || (iVar5 == 0xfe)) {
                // Unassigned or invalid key code: clear display
                puVar3[entryIndex * 12 + 11] = 0;        // type = 0 (none)
                puVar3[entryIndex * 12 + 12] = 0xffffffff; // index = -1
            }
            else {
                // Get the UI control string for the key code
                char *pcVar7 = (char *)0x0;
                switch(iVar5) {
                case 0:
                    pcVar7 = "$ui_ctrl_mb1";      // Mouse button 1
                    break;
                case 1:
                    pcVar7 = "$ui_ctrl_mb2";      // Mouse button 2
                    break;
                case 2:
                    pcVar7 = "$ui_ctrl_mb3";      // Mouse button 3
                    break;
                case 3:
                    pcVar7 = "$ui_ctrl_scrl_up";  // Scroll up
                    break;
                case 4:
                    pcVar7 = "$ui_ctrl_scrl_down"; // Scroll down
                    break;
                }
                _strcpy_s(displayBuffer, 0x20, pcVar7);
                puVar3[entryIndex * 12 + 11] = 2;          // type = 2 (keyboard/mouse)
                puVar3[entryIndex * 12 + 12] = entryIndex; // index = entry index
            }
        }
        else {
            // Gamepad button assigned (cVar2 is button index)
            // Get language ID from global structure (offset 0x565)
            uVar6 = FUN_00411070(*(undefined1 *)(iVar1 + 0x565));

            // Initialize deallocator variables for localized string
            local_30 = (char *)0x0;
            local_2c = 0;
            local_28 = 0;
            local_24 = (code *)0x0;

            // Get localized string for this button and language
            FUN_0069cc50(cVar2, uVar6, &local_30);

            char *pcVar7 = local_30;
            if (local_30 == (char *)0x0) {
                pcVar7 = &DAT_0120546e; // fallback string (empty or error)
            }
            _strcpy_s(displayBuffer, 0x20, pcVar7);

            puVar3[entryIndex * 12 + 11] = 1;          // type = 1 (gamepad)
            puVar3[entryIndex * 12 + 12] = entryIndex; // index = entry index

            // Free the allocated localized string if any
            if (local_30 != (char *)0x0) {
                (*local_24)(local_30);
            }
        }
    }

    // Copy the resolved display string into the binding's display entry at offset +2 words (8 bytes)
    _strcpy_s((char *)(puVar3 + entryIndex * 12 + 2), 0x20, displayBuffer);

    return;
}