// FUNC_NAME: BuildingManager::updateBuildingTypeSelection
void __fastcall BuildingManager::updateBuildingTypeSelection(void* this) {
    // Call helper update functions (likely UI, logic, input)
    updateBuildingTypeSelectionPre();
    updateBuildingTypeSelectionLogic();
    updateBuildingTypeSelectionInput();

    // Log the update event
    FUN_005a04a0("UpdateBuildingTypeSelection", 0, &DAT_00d8bc74, 0);

    // Check if building type selection is active (byte at +0xA4)
    if (*(char*)((int)this + 0xA4) == '\0') {
        // Not active: check if we have both type and location selected,
        // and if there is an empty slot available
        if (*(char*)((int)this + 0x48) != '\0' &&          // +0x48: hasSelectedType
            *(char*)((int)this + 0x4C) != '\0' &&          // +0x4C: hasSelectedLocation
            *(uint*)((int)this + 0x78) < *(uint*)((int)this + 0x5C) && // +0x78: currentSlotIndex < +0x5C: totalSlots
            *(int*)(*(int*)((int)this + 0x58) + *(uint*)((int)this + 0x78) * 4) == 0) // +0x58: slotArray[currentSlotIndex] == 0 (empty)
        {
            // Trigger event (e.g., play sound, start placement)
            triggerEvent(6, 1);
            // Advance to next selection step (e.g., place building)
            advanceBuildingSelection();
            return;
        }
    } else {
        // Active: reset the flag
        *(char*)((int)this + 0xA4) = 0;

        // If state is 2 (e.g., cancel/back), handle it
        if (*(int*)((int)this + 0x98) == 2) { // +0x98: selectionState
            cancelBuildingSelection();
        }

        // Check same condition as above (without the active flag)
        if (*(char*)((int)this + 0x48) != '\0' &&
            *(char*)((int)this + 0x4C) != '\0' &&
            *(uint*)((int)this + 0x78) < *(uint*)((int)this + 0x5C) &&
            *(int*)(*(int*)((int)this + 0x58) + *(uint*)((int)this + 0x78) * 4) == 0)
        {
            advanceBuildingSelection();
            return;
        }
    }
    return;
}