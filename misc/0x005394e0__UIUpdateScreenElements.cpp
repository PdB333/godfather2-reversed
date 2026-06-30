//FUNC_NAME: UIUpdateScreenElements
void __fastcall UIUpdateScreenElements(uint param1, uint param2)
{
    uint in_EAX; // param1 passed in ECX
    undefined1 *puVar1;
    float fVar2;
    undefined8 uVar3;
    undefined4 local_20; // part of a struct passed to addDrawCall
    undefined4 local_1c;
    float local_18;
    float local_14;

    // Store the parameters globally for later use
    g_uiParam1 = in_EAX;   // DAT_0121b7e4
    g_uiParam2 = param1;   // DAT_0121b820 (note: param1 is the second parameter in __fastcall)

    // Check if the UI manager singleton is initialized
    if (g_pUIManager == &g_uiManagerInstance) // DAT_012058e8 == &DAT_0121b740
    {
        // Case: current screen is the menu screen
        if (g_currentScreen == g_screenTypeMenu) // DAT_0121b754 == DAT_0121bbb0
        {
            // If a certain flag is set, call a reset/cleanup function
            if (g_bFlag1 != 0) // DAT_0121b9a0
            {
                someResetFunction(); // FUN_006063b0
            }

            // If another flag is set, compute scaling and add a draw call
            if (g_bFlag2 != 0) // DAT_0121b9a4
            {
                local_20 = 0;
                local_1c = 0;

                // Look up the resource entry from the global table (0x38 bytes per entry)
                if (g_uiParam1 < 0x1000)
                {
                    puVar1 = &g_resourceTable + g_uiParam1 * 0x38; // DAT_011a0f28
                }
                else
                {
                    puVar1 = (undefined1 *)0x0;
                }

                // Compute scale factors: screen width / resource width (offset +2) and height (offset +4)
                local_18 = g_screenWidth / (float)*(ushort *)(puVar1 + 2); // DAT_00e2cd54
                if (g_uiParam1 < 0x1000)
                {
                    puVar1 = &g_resourceTable + g_uiParam1 * 0x38;
                }
                else
                {
                    puVar1 = (undefined1 *)0x0;
                }
                local_14 = g_screenWidth / (float)*(ushort *)(puVar1 + 4);

                // Add a draw call with the computed rectangle and scaling
                addDrawCall(g_currentScreen, g_bFlag2, &local_20); // FUN_0060add0
                return;
            }
        }
        // Case: current screen is the gameplay screen
        else if (g_currentScreen == g_screenTypeGame) // DAT_0121b754 == DAT_0121bbb4
        {
            // Set some property on the screen with a pointer
            setElementProperty(g_currentScreen, g_pointer1); // FUN_0060b2f0 (2 args)

            // If another pointer is non-null, set property with an additional parameter
            if (g_pointer2 != 0) // DAT_0121b9bc
            {
                setElementProperty(g_currentScreen, g_pointer2, g_uiParam2); // FUN_0060b2f0 (3 args)
            }

            // Handle element with ID g_uiParam1
            if (g_pointer3 != 0) // DAT_0121b9c4
            {
                local_20 = 0;
                local_1c = 0;
                fVar2 = g_screenWidth;
                uVar3 = getResourceEntry(g_uiParam1); // FUN_00606370 returns 64-bit value
                // Low 32 bits are a pointer to the resource entry
                local_18 = fVar2 / (float)*(ushort *)((int)uVar3 + 2);
                local_14 = fVar2 / (float)*(ushort *)((int)uVar3 + 4);
                // High 32 bits are passed as an int (maybe an ID or index)
                addDrawCall(g_currentScreen, (int)((ulonglong)uVar3 >> 0x20), &local_20); // FUN_0060add0
            }

            // Handle element with ID g_uiParam2
            if (g_pointer4 != 0) // DAT_0121b9c8
            {
                local_20 = 0;
                local_1c = 0;
                fVar2 = g_screenWidth;
                uVar3 = getResourceEntry(g_uiParam2);
                local_18 = fVar2 / (float)*(ushort *)((int)uVar3 + 2);
                local_14 = fVar2 / (float)*(ushort *)((int)uVar3 + 4);
                addDrawCall(g_currentScreen, (int)((ulonglong)uVar3 >> 0x20), &local_20);
            }
        }
    }
    return;
}