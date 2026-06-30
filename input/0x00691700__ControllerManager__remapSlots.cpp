// FUNC_NAME: ControllerManager::remapSlots
void ControllerManager::remapSlots(int oldSlotIndex, int newSlotIndex)
{
    char byte565 = *(char *)(g_controllerStateBase + 0x565); // +0x565: secondary mapping type flag
    if (*(char *)(g_controllerStateBase + 0x564) != '\x12')  // +0x564: primary mapping type flag (0x12 = 18, possibly max slots)
    {
        // Read current player-to-physical mapping for both slots
        int oldMapping = g_playerToPhysicalMap[oldSlotIndex * 2];
        int newMapping = g_playerToPhysicalMap[newSlotIndex * 2];

        // Convert the mapping type flag (possibly to a slot code)
        FUN_00411070(*(char *)(g_controllerStateBase + 0x564));
        int currentSlot = FUN_004958a0(); // Get currently active controller slot?

        if (oldMapping != currentSlot)
        {
            if (newMapping == currentSlot)
            {
                // Swap mapping if the new slot matches the current active slot
                FUN_006912c0(oldSlotIndex, newSlotIndex);
            }
            else
            {
                // Replace all occurrences of newMapping with oldMapping in the mapping array
                int maxIndex = g_mappingArraySize;
                for (int i = maxIndex; i >= 0; i--)
                {
                    if (g_mappingArray[i] == newMapping)
                    {
                        g_mappingArray[i] = oldMapping;
                        break;
                    }
                }
            }
        }
    }

    if (byte565 != '\x12')
    {
        // Same logic for secondary mapping (e.g., physical-to-player)
        int oldMapping = g_physicalToPlayerMap[oldSlotIndex * 2];
        int newMapping = g_physicalToPlayerMap[newSlotIndex * 2];

        FUN_00411070(byte565);
        int currentSlot = FUN_004958a0();

        if (oldMapping != currentSlot)
        {
            if (newMapping == currentSlot)
            {
                FUN_00691330(oldSlotIndex, newSlotIndex);
                return;
            }

            int maxIndex = g_otherMappingArraySize;
            if (maxIndex >= 0)
            {
                for (int i = maxIndex; i >= 0; i--)
                {
                    if (g_otherMappingArray[i] == newMapping)
                    {
                        g_otherMappingArray[i] = oldMapping;
                        return;
                    }
                }
            }
        }
    }
}