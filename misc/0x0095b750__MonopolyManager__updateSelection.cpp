// FUNC_NAME: MonopolyManager::updateSelection
void __fastcall MonopolyManager::updateSelection(void* thisPtr)
{
    uint selectedIndex;
    int propertyId;
    int propertyState;

    // Call base update (e.g., update input)
    updateInput();  // FUN_00957df0

    // Start profile scope for this update
    profileScope("UpdateMonopolySelection", 0, &someGlobalProfileData, 0);  // FUN_005a04a0

    // Check if a selection is pending
    if (*(char*)((uint)thisPtr + 0xC4) != '\0')
    {
        selectedIndex = *(uint*)((uint)thisPtr + 0xC0);
        *(char*)((uint)thisPtr + 0xC4) = 0;  // Clear pending flag

        // Validate selected index against number of properties
        if (selectedIndex != 0xFFFFFFFF && selectedIndex < *(uint*)((uint)thisPtr + 0x68))
        {
            // Get property ID from array of property pointers at +0x64
            propertyId = getPropertyIdFromIndex(*(int*)(*(int*)((uint)thisPtr + 100) + selectedIndex * 4));  // FUN_006b0ee0
        }
        else
        {
            propertyId = 0;
        }

        // Check property state (0 = not available, 1 = owned?, 2 = buyable)
        propertyState = getPropertyState(propertyId);  // FUN_0095a800

        if (propertyState == 2)
        {
            // Play confirmation sound
            playConfirmSound();  // FUN_005c1ad0

            // Close the selection menu
            closeSelectionMenu(0);  // FUN_0095b320

            // Store selected property ID in global game manager (at index 0x1B)
            gGameManager->selectedPropertyId = propertyId;  // DAT_011305b4[0x1b] = propertyId

            // Call vtable method at offset 0x28 on the game manager
            // (likely a callback to process the purchase)
            (*(void(__thiscall**)(void*))(*(uint*)gGameManager + 0x28))(gGameManager);
        }
    }

    // Post-update cleanup
    endUpdate();  // FUN_00957350
}